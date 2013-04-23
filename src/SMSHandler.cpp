/*
========================================================================
 Name        : SMSHandler.cpp
 Author		 : Nokia Corporation
 Modified    : Laurent Bindschaedler
 Copyright   : Copyright (c) Nokia Corporation 2009
 Description : Implementation of SMS handler
========================================================================
*/
// INCLUDE FILES
#include <eikenv.h>
#include <coemain.h>
#include <e32std.h>
#include <msvids.h>
#include <msvstd.h>
#include <smsclnt.h>
#include <smut.h>
#include <mtclreg.h>
#include <txtrich.h>
#include <smscmds.h>
#include <mtmuibas.h>
#include <mtmdef.h>
#include <stringloader.h>
#include "SmsHandler.h"
#include "smutset.h"
#include "smuthdr.h"
#include "gsmuelem.h"

#include "ConfigSettingItemListView.h"
#include "ConfigSettingItemList.h"
 
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CSmsHandler::CSmsHandler()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSmsHandler::CSmsHandler()
: CActive( CActive::EPriorityStandard )
    {
    CActiveScheduler::Add( this );
    iNextUnread = 0;            // index of next unread message in iSelection
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSmsHandler::ConstructL()
    {
    // Session to message server is opened asynchronously.
    iSession = CMsvSession::OpenAsyncL( *this );
 
    // Entry selection for all received messages.
    iSelection = new ( ELeave ) CMsvEntrySelection();
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSmsHandler* CSmsHandler::NewL( )
    {
    CSmsHandler* self = NewLC( );
    CleanupStack::Pop( self );
    return self;
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSmsHandler* CSmsHandler::NewLC()
    {
    CSmsHandler* self = new ( ELeave ) CSmsHandler();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }
 
// ----------------------------------------------------------
// CSmsHandler::~CSmsHandler()
// Destructor.
// ----------------------------------------------------------
//
CSmsHandler::~CSmsHandler()
    {
    Cancel();           // cancel any outstanding request
 
    delete iOperation;
    delete iMtmUiRegistry;
    delete iSelection;
	delete iSmsMtm;
    delete iMtmRegistry;
    delete iSession;    // session must be deleted last
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::DoCancel()
// Cancels a request.
// -----------------------------------------------------------------------------
//
void CSmsHandler::DoCancel()
    {
    if ( iOperation )
        {
        iOperation->Cancel();
        }
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::RunL()
// Handles request completion events.
// -----------------------------------------------------------------------------
//
void CSmsHandler::RunL()
    {
    User::LeaveIfError( iStatus != KErrNone );
 
    // Determine the current operations progress.
    // ProgressL returns an 8 bit descriptor.
    TBufC8<KMsvProgressBufferLength> progress( iOperation->ProgressL() );
    _LIT8( KCompare, "KErrNone" );
    User::LeaveIfError( !progress.Compare( KCompare ) );
 
    // The pointer to the current CMsvOperation object is no longer needed.
    delete iOperation;
    iOperation = NULL;
 
    // Determine which request has finished.
    switch ( iState )
        {
        case EWaitingForMoving:
            // Once a message is moved to Outbox it is scheduled for sending.
            ScheduleL();
            break;
 
        case EWaitingForScheduling:
            {
            TMsvEntry entry( iSmsMtm->Entry().Entry() );
            TInt state( entry.SendingState() );
 
            if ( state == KMsvSendStateWaiting || state == KMsvSendStateScheduled)
                {
                }
 
            break;
            }
 
        default:
            break;
        }
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::HandleSessionEventL()
// Handles notifications of events from the Message Server.
// -----------------------------------------------------------------------------
//
void CSmsHandler::HandleSessionEventL( TMsvSessionEvent aEvent,
                                      TAny* aArg1, TAny* aArg2, TAny* /*aArg3*/)
	{
	switch ( aEvent )
		{
        // Session to server established
		case EMsvServerReady:
            {
            TMsvId serviceId( KUidMsgTypeSMS.iUid ); // SMS service id
 
            // Determine if the event was succesful.
            // ServiceProgress inserts TBuf8 value in progress.
            TBuf8<KBfrLength> progress;
			iSession->ServiceProgress( serviceId, progress );
			_LIT8( KCompare, "KErrNone" );
 
			if ( progress.Compare( KCompare ) )
				{
                // Check that MtmRegistry has not already been accessed.
                if ( !iMtmRegistry )
                    {
                    AccessMtmL();
                    }
                }
            break;
            }
 
        // A new entry has been created on the message server.
        case EMsvEntriesCreated:
            {
            // Entry id is obtained from the session event arguments.
            TMsvId* entryId = STATIC_CAST( TMsvId*, aArg2 );
 
            // We are interested in messages that are created in Inbox.
            if ( *entryId != KMsvGlobalInBoxIndexEntryId )
                {
                break;
                }
 
            // We take the created entries into a selection
            CMsvEntrySelection* newEntries =
                STATIC_CAST( CMsvEntrySelection*, aArg1 );
 
            // Process each created entry.
            for ( TInt i( 0 ); i < newEntries->Count(); i++ )
                {
                // We are interested in SMS messages.
                if ( ( iSession->GetEntryL( newEntries->At( i ) ) )
                    ->Entry().iMtm == KUidMsgTypeSMS )
                    {
                    // Add the entry to the selection of all received messages.
                    iSelection->AppendL( newEntries->At( i ), 1 );
 
                    // Set received messages visible.
                    MessageReceivedL( newEntries->At( i ) );
                    }
                }
 
            break;
            }
        case EMsvCloseSession:
        case EMsvServerTerminated:
        case EMsvGeneralError:
        case EMsvServerFailedToStart:
            {
//            iSmsAppUi->ServerDown( aEvent );    // close application
            break;
            }
 
        // All other events are ignored.
        default:
            break;
        }
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::AccessMtmL()
// Access the MTM Registry and create a SMS specific Client MTM instance.
// -----------------------------------------------------------------------------
//
void CSmsHandler::AccessMtmL()
	{
    // Create an MTM Registry object.
    iMtmRegistry = CClientMtmRegistry::NewL( *iSession );
 
    // Create an SMS Client MTM object.
    iSmsMtm = STATIC_CAST( CSmsClientMtm*, iMtmRegistry->NewMtmL( KUidMsgTypeSMS ) );
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::SendL()
// Starts the process of creating and sending an SMS message.
// -----------------------------------------------------------------------------
//
TBool CSmsHandler::SendL( const TDesC& aRecipientNumber,
                            const TDesC& aMessageText )
    {
    iRecipientNumber = aRecipientNumber;
    iMessageText = aMessageText;
 
    if ( CreateMsgL() )
        {
        return ETrue;
        }
 
    return EFalse;
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::CreateMsgL()
// Create an SMS message.
// -----------------------------------------------------------------------------
//
TBool CSmsHandler::CreateMsgL()
    {
    // Current entry is the Draft folder.
    iSmsMtm->SwitchCurrentEntryL( KMsvDraftEntryId );
 
    // Create a new SMS message entry as a child of the current context.
    iSmsMtm->CreateMessageL( KUidMsgTypeSMS.iUid );
 
    CMsvEntry& serverEntry = iSmsMtm->Entry();
    TMsvEntry entry( serverEntry.Entry() );
 
    CRichText& body = iSmsMtm->Body();   // the body of the message
    body.Reset();
    // Insert the message text gotten as input from user.
    body.InsertL( 0, iMessageText );
 
    // Message will be sent immediately.
    entry.SetSendingState( KMsvSendStateWaiting );
 
//Added for 3rd edition
//    entry.iDate.HomeTime(); // insert current time //This was causing problem:SMS stays into Outbox only.
	entry.iDate.UniversalTime(); // insert current time //Solution for HomeTime()
//Code Ends-
    // Set the SMS message settings for the message.
    CSmsHeader& header = iSmsMtm->SmsHeader();
    CSmsSettings* settings = CSmsSettings::NewL();
    CleanupStack::PushL( settings );
 
    settings->CopyL( iSmsMtm->ServiceSettings() );    // restore settings
    settings->SetDelivery( ESmsDeliveryImmediately ); // to be delivered immediately
    settings->SetCharacterSet(TSmsDataCodingScheme::ESmsAlphabetUCS2); // set to unicode
	//settings->SetDeliveryReport(ETrue);
    header.SetSmsSettingsL( *settings );              // new settings
 
	// Let's check if there is a service center address.
	if ( header.Message().ServiceCenterAddress().Length() == 0 )
		{
		// No, there isn't. We assume there is at least one service center
        // number set and use the default service center number.
		CSmsSettings* serviceSettings = &( iSmsMtm->ServiceSettings() );
 
        // Check if number of service center addresses in the list is null.
 
//Changed for 3rd Edition specially
//        if ( !serviceSettings->NumSCAddresses() )
		if ( !serviceSettings->ServiceCenterCount() )
            {
			return EFalse;     // quit creating the message
            }
 
		else
			{
//Changed for 3rd Edition specially
//          CSmsNumber* smsCenter = &( serviceSettings->SCAddress( serviceSettings->DefaultSC() ) );
				CSmsNumber* smsCenter= CSmsNumber::NewL();
				CleanupStack::PushL(smsCenter);
				smsCenter->SetAddressL((serviceSettings->GetServiceCenter( serviceSettings->DefaultServiceCenter())).Address());
				header.Message().SetServiceCenterAddressL( smsCenter->Address() );
				CleanupStack::PopAndDestroy(smsCenter);
		    }
        }
 
	CleanupStack::PopAndDestroy( settings );
 
    // Recipient number is displayed also as the recipient alias.
    entry.iDetails.Set( iRecipientNumber );
    // Add addressee.
    iSmsMtm->AddAddresseeL( iRecipientNumber, entry.iDetails );
 
    // Validate message.
    if ( !ValidateL() )
        {
        return EFalse;
        }
 
    entry.SetVisible( ETrue );          // set message as visible
    entry.SetInPreparation( EFalse );   // set together with the visibility flag
    serverEntry.ChangeL( entry );       // commit changes		
    iSmsMtm->SaveMessageL();            // save message
 
    TMsvSelectionOrdering selection;
	CMsvEntry* parentEntry = CMsvEntry::NewL( iSmsMtm->Session(), KMsvDraftEntryId, selection );
    CleanupStack::PushL( parentEntry );
    
    // Move message to Outbox
    iOperation = parentEntry->MoveL( entry.Id(), KMsvGlobalOutBoxIndexEntryId, iStatus );
 
    CleanupStack::PopAndDestroy( parentEntry );
 
    iState = EWaitingForMoving;
    SetActive();
 
    return ETrue;
  }
 
// -----------------------------------------------------------------------------
// CSmsHandler::ValidateL()
// Validate an SMS message.
// -----------------------------------------------------------------------------
//
TBool CSmsHandler::ValidateL()
    {
    // Empty part list to hold the result.
    TMsvPartList result( KMsvMessagePartNone );
 
    // Validate message body.
    result = iSmsMtm->ValidateMessage( KMsvMessagePartBody );
 
    if ( result != KMsvMessagePartNone )
        {
        return EFalse;
        }
 
    // Validate recipient.
    result = iSmsMtm->ValidateMessage( KMsvMessagePartRecipient );
 
    if ( result != KMsvMessagePartNone )
        {
        return EFalse;
        }
 
    return ETrue;
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::ScheduleL()
// Schedule an SMS message for sending.
// -----------------------------------------------------------------------------
//
void CSmsHandler::ScheduleL()
    {
    CMsvEntrySelection* selection = new ( ELeave ) CMsvEntrySelection;
    CleanupStack::PushL( selection );
    selection->AppendL( iSmsMtm->Entry().EntryId() ); // add message to selection
 
    // Add entry to task scheduler.
    TBuf8<1> dummyParams;   // dummy parameters needed for InvokeAsyncFunctionL
    iOperation = iSmsMtm->InvokeAsyncFunctionL( ESmsMtmCommandScheduleCopy,
                          *selection, dummyParams, iStatus );
 
    CleanupStack::PopAndDestroy( selection );
 
    iState = EWaitingForScheduling;
    SetActive();
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::MessageReceivedL()
// Handles a received SMS message.
// -----------------------------------------------------------------------------
//
void CSmsHandler::MessageReceivedL( TMsvId aEntryId )
    {
    CMsvEntry* serverEntry = iSession->GetEntryL( aEntryId );   // current entry
    CleanupStack::PushL( serverEntry );
    TMsvEntry entry = serverEntry->Entry(); // currently handled message entry
 
    entry.SetNew( ETrue );
    entry.SetUnread( ETrue );
    entry.SetVisible( ETrue );
 
    serverEntry->ChangeL( entry );  // commit changes
    //iSmsAppUi->MessageReceived();   // let UI know we have received a message
 
    CleanupStack::PopAndDestroy( serverEntry );
    }
 
// -----------------------------------------------------------------------------
// CSmsHandler::ViewL()
// Dispalys a received SMS message.
// -----------------------------------------------------------------------------
//
void CSmsHandler::ViewL()
    {
    // There is an own registry for UI MTM's.
    iMtmUiRegistry = CMtmUiRegistry::NewL( *iSession );
 
    // We are interested in the next unread message.
    TMsvId entryId( iSelection->At( iNextUnread ) );
    CMsvEntry* serverEntry = iSession->GetEntryL( entryId );
    CleanupStack::PushL( serverEntry );
 
    // Create new MTM.
   	CBaseMtm* clientMtm = iMtmRegistry->NewMtmL( serverEntry->Entry().iMtm );
	CleanupStack::PushL( clientMtm );
	clientMtm->SwitchCurrentEntryL( serverEntry->EntryId() );
 
    // Check if there are more unreads messages.
    iNextUnread++;
    if ( iNextUnread < iSelection->Count() )
        {
  //      iSmsAppUi->MessageReceived();   // still messages to read
        }
    else
        {
//        iSmsAppUi->NoMoreUnread();      // no more messages to read
        }
 
    TMsvEntry entry( serverEntry->Entry() );
    entry.SetNew( EFalse );         // message is no longer new
    entry.SetUnread( EFalse );      // message is no longer unread
    serverEntry->ChangeL( entry );  // commit changes
 
	CBaseMtmUi* ui = iMtmUiRegistry->NewMtmUiL( *clientMtm ); // UI MTM for SMS
 	CleanupStack::PushL( ui );
 
    // Display the SMS using the UI MTM.
    iOperation = ui->ViewL( iStatus );
 
    CleanupStack::PopAndDestroy( 3 ); // ui, clientMtm, serverEntry
    SetActive();
    }

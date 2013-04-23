/*
========================================================================
 Name        : ReadMessageContainer.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of read message container
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <barsread.h>
#include <stringloader.h>
#include <gdi.h>
#include <eikgted.h>
#include <eikenv.h>
#include <aknviewappui.h>
#include <eikappui.h>
#include <txtfrmat.h>
#include <eikrted.h>
#include <txtrich.h>
#include <gulcolor.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]
#include <AknQueryDialog.h>
// [[[ begin generated region: do not modify [Generated User Includes]
#include "ReadMessageContainer.h"
#include "ReadMessageContainerView.h"
#include "SecureSMS.hrh"
#include "ConfigSettingItemList.hrh"
// ]]] end generated region [Generated User Includes]
#include "ConfigSettingItemListView.h"
#include "ConfigSettingItemList.h"
#include "ContactsHandler.h"

#define MAX_SENDER_LENGTH 50
#define MAX_DATE_LENGTH 20

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CReadMessageContainer::CReadMessageContainer()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iMessage = NULL;
	iSender = NULL;
	iDate = NULL;
	// ]]] end generated region [Generated Contents]
	
	}
/** 
 * Destroy child controls.
 */
CReadMessageContainer::~CReadMessageContainer()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iMessage;
	iMessage = NULL;
	delete iSender;
	iSender = NULL;
	delete iDate;
	iDate = NULL;
	// ]]] end generated region [Generated Contents]
	
	delete iPassword;
	iPassword=NULL;
	
	delete iSmsMtm;
	iSmsMtm = NULL;
	delete iMtmRegistry;
	iMtmRegistry = NULL;
	delete iSession;
	iSession = NULL;
	}
				
/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CReadMessageContainer
 */
CReadMessageContainer* CReadMessageContainer::NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver,
		TInt aMessageId )
	{
	CReadMessageContainer* self = CReadMessageContainer::NewLC( 
			aRect, 
			aParent, 
			aCommandObserver,
			aMessageId );
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CReadMessageContainer
 */
CReadMessageContainer* CReadMessageContainer::NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver,
		TInt aMessageId )
	{
	CReadMessageContainer* self = new ( ELeave ) CReadMessageContainer();
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aParent, aCommandObserver, aMessageId );
	return self;
	}
			
/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */ 
void CReadMessageContainer::ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver,
		TInt aMessageId )
	{
	if ( aParent == NULL )
	    {
		CreateWindowL();
	    }
	else
	    {
	    SetContainerWindowL( *aParent );
	    }
	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;
	
	iMessageId = aMessageId;
	
	iSession = CMsvSession::OpenSyncL(*this);
	iMtmRegistry = CClientMtmRegistry::NewL(*iSession);
	iSmsMtm = iMtmRegistry->NewMtmL(KUidMsgTypeSMS);
	
	if(iMessageId < 0)
		iMessageId = GetNumMessages() - 1;
	
	InitializeControlsL();
	SetRect( aRect );
	ActivateL();

	Fill();
	
	}
			
/**
* Return the number of controls in the container (override)
* @return count
*/
TInt CReadMessageContainer::CountComponentControls() const
	{
	return ( int ) ELastControl;
	}
				
/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CReadMessageContainer::ComponentControl( TInt aIndex ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
		case EMessage:
			return iMessage;
		case ESender:
			return iSender;
		case EDate:
			return iDate;
		}
	// ]]] end generated region [Generated Contents]
	
	// handle any user controls here...
	
	return NULL;
	}
				
/**
 *	Handle resizing of the container. This implementation will lay out
 *  full-sized controls like list boxes for any screen size, and will layout
 *  labels, editors, etc. to the size they were given in the UI designer.
 *  This code will need to be modified to adjust arbitrary controls to
 *  any screen size.
 */				
void CReadMessageContainer::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	// [[[ begin generated region: do not modify [Generated Contents]
			
	// ]]] end generated region [Generated Contents]
	
	}
				
// [[[ begin generated function: do not modify
/**
 * Layout components as specified in the UI Designer
 */
void CReadMessageContainer::LayoutControls()
	{
	TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
	TInt height = rect.Height();
	TInt width = rect.Width();
	TInt heightFraction = (int) (1.0 / 8.0 * height);
	iMessage->SetExtent( TPoint( 0, 2 * heightFraction ), TSize( width, height - 2 * heightFraction ) );
	iSender->SetExtent( TPoint( 0, 0 ), TSize( width, heightFraction ) );
	iDate->SetExtent( TPoint( 0, heightFraction ), TSize( width, heightFraction ) );
	}
// ]]] end generated function

/**
 *	Handle key events.
 */				
TKeyResponse CReadMessageContainer::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	
	// ]]] end generated region [Generated Contents]
	if (aKeyEvent.iCode == EKeyRightArrow)
		{
		--iMessageId;
		if(iMessageId < 0)
			iMessageId = GetNumMessages() - 1;
		Fill();
		return EKeyWasConsumed;
		}
	else if (aKeyEvent.iCode == EKeyLeftArrow)
		{
		++iMessageId;
		iMessageId %= GetNumMessages();
		Fill();
		return EKeyWasConsumed;
		}
	if ( iFocusControl != NULL
		&& iFocusControl->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
		{
		return EKeyWasConsumed;
		}
	return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
	}
				
// [[[ begin generated function: do not modify
/**
 *	Initialize each control upon creation.
 */				
void CReadMessageContainer::InitializeControlsL()
	{
	iMessage = new ( ELeave ) CEikRichTextEditor;
	iMessage->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_READ_MESSAGE_CONTAINER_MESSAGE );
		iMessage->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
		{
		HBufC* text = StringLoader::LoadLC( R_READ_MESSAGE_CONTAINER_MESSAGE_2 );
		iMessage->SetTextL( text );
		CleanupStack::PopAndDestroy( text );
		}
	iSender = new (ELeave) CEikRichTextEditor;
	iSender->SetContainerWindowL(*this);
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC(reader,
				R_READ_MESSAGE_CONTAINER_SENDER );
		iSender->ConstructFromResourceL(reader);
		CleanupStack::PopAndDestroy(); // reader internal state
		}
		{
		HBufC* text = StringLoader::LoadLC(R_READ_MESSAGE_CONTAINER_SENDER_2);
		iSender->SetTextL(text);
		CleanupStack::PopAndDestroy(text);
		}
	iDate = new (ELeave) CEikRichTextEditor;
	iDate->SetContainerWindowL(*this);
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC(reader,
				R_READ_MESSAGE_CONTAINER_DATE );
		iDate->ConstructFromResourceL(reader);
		CleanupStack::PopAndDestroy(); // reader internal state
		}
		{
		HBufC* text = StringLoader::LoadLC(R_READ_MESSAGE_CONTAINER_DATE_2);
		iDate->SetTextL(text);
		CleanupStack::PopAndDestroy(text);
		}
	
	iMessage->SetFocus( ETrue );
	iFocusControl = iMessage;
	
	}
// ]]] end generated function

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CReadMessageContainer::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( EReadMessageContainerViewId ) )->ClientRect() );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
				
/**
 *	Draw container contents.
 */				
void CReadMessageContainer::Draw( const TRect& aRect ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	
	// ]]] end generated region [Generated Contents]
	
	}
				
void CReadMessageContainer::SetMessageFormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	TFontSpec fontSpec = AknLayoutUtils::FontFromId(
			EAknLogicalFontSecondaryFont)->FontSpecInTwips();

	TCharFormatMask charFormatMask;
	TCharFormat charFormat;
	charFormatMask.SetAttrib(EAttColor);
	charFormat.iFontPresentation.iTextColor = TLogicalRgb(iEikonEnv->Color(
			(TLogicalColor) EEikColorButtonText));
	charFormat.iFontSpec = fontSpec;
	
	CRichText* richText = iMessage->RichText();
	richText->ApplyCharFormatL( 
			charFormat, 
			charFormatMask, 
			0, 
			richText->DocumentLength() );
	
	// ]]] end generated region [Generated GlobalText formatting]
	
	}
void CReadMessageContainer::SetSenderFormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	TCharFormatMask charFormatMask;
	TCharFormat charFormat;
	charFormatMask.SetAttrib(EAttColor);
	charFormat.iFontPresentation.iTextColor = TLogicalRgb(iEikonEnv->Color(
			(TLogicalColor) EEikColorButtonText));
	charFormatMask.SetAttrib(EAttFontHeight);
	charFormat.iFontSpec.iHeight = 150;
	charFormatMask.SetAttrib(EAttFontStrokeWeight);
	charFormat.iFontSpec.iFontStyle.SetStrokeWeight(EStrokeWeightBold);

	CRichText* richText = iSender->RichText();
	richText->ApplyCharFormatL(charFormat, charFormatMask, 0,
			richText->DocumentLength());
	// ]]] end generated region [Generated GlobalText formatting]
	}

void CReadMessageContainer::SetDateFormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	TCharFormatMask charFormatMask;
	TCharFormat charFormat;
	charFormatMask.SetAttrib(EAttColor);
	charFormat.iFontPresentation.iTextColor = TLogicalRgb(iEikonEnv->Color(
			(TLogicalColor) EEikColorButtonText));
	charFormatMask.SetAttrib(EAttFontHeight);
	charFormat.iFontSpec.iHeight = 100;
	//charFormatMask.SetAttrib(EAttFontPosture);
	//charFormat.iFontSpec.iFontStyle.SetPosture(EPostureItalic);

	CRichText* richText = iDate->RichText();
	richText->ApplyCharFormatL(charFormat, charFormatMask, 0,
			richText->DocumentLength());
	// ]]] end generated region [Generated GlobalText formatting]
	}

TBool CReadMessageContainer::CheckIfFolderExistsL()
	{
	CMsvEntry * entry = iSession->GetEntryL(KMsvMyFoldersEntryIdValue);
	CleanupStack::PushL(entry);
	CMsvEntrySelection * entries = entry->ChildrenWithTypeL(KUidMsvFolderEntry);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(entries);
	TInt nCount = entries->Count();
	TInt found = 0;
	for (TInt i = 1; i < nCount; i++)
		{
		TMsvId entryID = entries->At(i);
		entry = iSession->GetEntryL(entryID);
		CleanupStack::PushL(entry);
		TMsvEntry msvEntry = entry->Entry();

		TPtrC descr = msvEntry.iDetails;
		if (descr.Compare(KGMEFolderName) == 0)
			{
			found = 1;
			iNewFolderId = entryID;
			}
		CleanupStack::PopAndDestroy(entry);
		}
	CleanupStack::PopAndDestroy(entries);

	return found;
	}

TBool CReadMessageContainer::CreateFolderL()
	{
	TMsvId msvServId;
	CMsvEntry *entry1 = NULL;
	CMsvEntry *rootEntry = NULL;
	CMsvEntry *entryRootService = NULL;

	TInt newFldrID = 0;

	//Get the entry (whatever is passed in)                                                    
	entry1 = iSmsMtm->Session().GetEntryL(KMsvMyFoldersEntryIdValue);
	CleanupStack::PushL(entry1);

	if (entry1)
		{
		msvServId = entry1->OwningService();

		entryRootService = iSmsMtm->Session().GetEntryL(msvServId);
		CleanupStack::PushL(entryRootService);

		rootEntry = iSmsMtm->Session().GetEntryL(msvServId);
		CleanupStack::PushL(rootEntry);

		rootEntry->SetEntryL(KMsvMyFoldersEntryIdValue); // set to parent                      

		TMsvEntry newServiceEntry;
		TTime ttime;
		ttime.HomeTime();
		newServiceEntry.iDate = ttime;
		newServiceEntry.iSize = 0;
		newServiceEntry.iType = KUidMsvFolderEntry;
		newServiceEntry.iMtm = KUidMsvLocalServiceMtm;
		newServiceEntry.iServiceId = msvServId;
		newServiceEntry.iDetails.Set(KGMEFolderName);
		newServiceEntry.iDescription.Set(KNullDesC);
		newServiceEntry.SetVisible(ETrue);

		rootEntry->CreateL(newServiceEntry);
		newFldrID = newServiceEntry.Id();
		iNewFolderId = newFldrID;
		CleanupStack::PopAndDestroy(rootEntry);
		CleanupStack::PopAndDestroy(entryRootService);
		}
	CleanupStack::PopAndDestroy(entry1);
	return ETrue;
	}

void CReadMessageContainer::SetMessage()
	{
	if(!CheckIfFolderExistsL())
		CreateFolderL();
	TInt pos = iMessageId;
	CMsvEntry * entry = iSession->GetEntryL(iNewFolderId);
	CleanupStack::PushL(entry);
	CMsvEntrySelection* messages = entry->ChildrenWithMtmL(KUidMsgTypeSMS);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(messages);

	iSmsMtm->SwitchCurrentEntryL(messages->At(pos));
	entry = iSession->GetEntryL((*messages)[pos]);
	CleanupStack::PushL(entry);
	CMsvStore* inboxStore = entry->ReadStoreL();
	CleanupStack::PushL(inboxStore);
	if (inboxStore->HasBodyTextL())
		{
		// Set Sender and Date
		TMsvEntry entry1 = entry->Entry();
		entry1.SetUnread(EFalse);
		iSmsMtm->Entry().ChangeL(entry1);
		HBufC* sender = HBufC::New(MAX_SENDER_LENGTH);
		CleanupStack::PushL(sender);
		TBufC<MAX_SENDER_LENGTH> aText(entry1.iDetails);
		sender->Des().Append(aText);
		iSender->SetCursorPosL(0, EFalse);
		iSender->ClearSelectionL();
		iSender->SetTextL(sender);
		CleanupStack::PopAndDestroy(sender);
		TTime ttime = entry1.iDate;
		TBuf<MAX_DATE_LENGTH> date;
		date.Format(_L("%04d-%02d-%02d %02d:%02d"), ttime.DateTime().Year(), ttime.DateTime().Month() + 1,
				ttime.DateTime().Day() + 1, (ttime.DateTime().Hour() + 2) % 24,
				ttime.DateTime().Minute());
		iDate->SetCursorPosL(0, EFalse);
		iDate->ClearSelectionL();
		iDate->SetTextL(&date);
		
		// Set Message
		CRichText& richText = iSmsMtm->Body();
		inboxStore->RestoreBodyTextL(richText);
		const TInt length = richText.DocumentLength();
		HBufC* item = HBufC::New(length);
		item->Des().Copy(richText.Read(0, length));
		CleanupStack::PushL(item);
		richText.Reset();
		TDesC& text = CGMEMessage::ExtractBodyLC(*item);
		TDesC& decrypted = CSecurityModule::DecryptLC(text, *iPassword);
		iMessage->SetCursorPosL(0,EFalse);
		iMessage->ClearSelectionL();
		iMessage->SetTextL(&decrypted);
		CleanupStack::PopAndDestroy(2);
		CleanupStack::PopAndDestroy(item);
		}
	CleanupStack::PopAndDestroy(inboxStore);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PopAndDestroy(messages);
	}

TBool CReadMessageContainer::ShowPasswordDialogL(TDes& aPassword)
{
    TBuf<KMaxPasswordLength> password;
    
    CAknTextQueryDialog* dlg = 
    new(ELeave) CAknTextQueryDialog(password, CAknQueryDialog::ENoTone );
    
    if(!dlg->ExecuteLD(R_DIALOG_PASSWORD_QUERY))
        {
        return EFalse;
        }
    else
        {
        aPassword.Copy(password);
        return ETrue;
        }
}

void CReadMessageContainer::Fill()
	{
	// Clear iSender, iDate and iMessage
	_LIT(KEmpty," ");
	iSender->SetCursorPosL(0, EFalse);
	iSender->ClearSelectionL();
	iSender->SetTextL(&KEmpty);
	iDate->SetCursorPosL(0, EFalse);
	iDate->ClearSelectionL();
	iDate->SetTextL(&KEmpty);
	iMessage->SetCursorPosL(0, EFalse);
	iMessage->ClearSelectionL();
	iMessage->SetTextL(&KEmpty);
	iSender->HandleTextChangedL();
	iDate->HandleTextChangedL();
	iMessage->HandleTextChangedL();
		
	if (iPassword)
		{
		delete iPassword;
		iPassword = NULL;
		}

	TConfigSettingItemListSettings* settings = TConfigSettingItemListSettings::NewL();
	CConfigSettingItemList * configSettingItemList = new (ELeave) CConfigSettingItemList(*settings, NULL);
	CleanupStack::PushL(settings);
	CleanupStack::PushL(configSettingItemList);
	configSettingItemList->LoadSettingValuesL();
	TBool store = settings->ContactsPasswords();
	CleanupStack::PopAndDestroy(configSettingItemList);
	CleanupStack::PopAndDestroy(settings);
	
	TDesC& phone = GetSenderPhoneLC();
	TDesC& key = CContactsHandler::ReadKeyLC(phone);
	HBufC* key2 = key.Alloc();
	CleanupStack::PopAndDestroy(2);
	if (store && key2->Length() > 0)
		{
		iPassword = key2;
		}
	else
		{
		iPassword = HBufC::NewL(KMaxPasswordLength);
		TPtr passwordPtr = iPassword->Des();
		ShowPasswordDialogL(passwordPtr);
		if(store)
			CContactsHandler::WriteKeyL(phone, passwordPtr);
		}

	SetMessage();
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	SetMessageFormattingL();
	SetSenderFormattingL();
	SetDateFormattingL();
	// ]]] end generated region [Post-ActivateL initializations]

	iSender->HandleTextChangedL();
	iDate->HandleTextChangedL();
	iMessage->HandleTextChangedL();
	
	}

TInt CReadMessageContainer::GetNumMessages()
	{
	if (!CheckIfFolderExistsL())
		CreateFolderL();
	CMsvEntry * entry = iSession->GetEntryL(iNewFolderId);
	CleanupStack::PushL(entry);
	CMsvEntrySelection* messages = entry->ChildrenWithMtmL(KUidMsgTypeSMS);
	CleanupStack::PopAndDestroy(entry);
	TInt nCount = messages->Count();
	delete messages;
	
	return nCount;
	}

TDesC& CReadMessageContainer::GetSenderPhoneLC()
	{
	if(!CheckIfFolderExistsL())
		CreateFolderL();
	TInt pos = iMessageId;
	CMsvEntry * entry = iSession->GetEntryL(iNewFolderId);
	CleanupStack::PushL(entry);
	CMsvEntrySelection* messages = entry->ChildrenWithMtmL(KUidMsgTypeSMS);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(messages);

	iSmsMtm->SwitchCurrentEntryL(messages->At(pos));
	entry = iSession->GetEntryL((*messages)[pos]);
	CleanupStack::PushL(entry);
	CMsvStore* inboxStore = entry->ReadStoreL();
	CleanupStack::PushL(inboxStore);
	
	HBufC* phone = HBufC::NewLC(MAX_SENDER_LENGTH);
	if (inboxStore->HasBodyTextL())
		{
		TMsvEntry entry1 = entry->Entry();
		phone->Des().Append(entry1.iDetails);
		}
	
	CleanupStack::Pop(phone);
	CleanupStack::PopAndDestroy(inboxStore);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PopAndDestroy(messages);
	CleanupStack::PushL(phone);
	
	return *phone;
	}

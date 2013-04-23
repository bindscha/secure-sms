/*
========================================================================
 Name        : SendMessageContainerView.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of send message view
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <gdi.h>
#include <eikgted.h>
#include <eikenv.h>
#include <eiklabel.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <aknquerydialog.h>
#include <eikseced.h>
#include <aknnotewrappers.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]
#include "ConfigSettingItemListView.h"
#include "ConfigSettingItemList.h"
// [[[ begin generated region: do not modify [Generated User Includes]

#include "SecureSMS.hrh"
#include "SendMessageContainerView.h"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
#include "SendMessageContainer.h"
// ]]] end generated region [Generated User Includes]

#include "ContactsHandler.h"

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CSendMessageContainerView::CSendMessageContainerView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iSendMessageContainer = NULL;
	// ]]] end generated region [Generated Contents]
	iSender = NULL;
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CSendMessageContainerView::~CSendMessageContainerView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iSendMessageContainer;
	iSendMessageContainer = NULL;
	// ]]] end generated region [Generated Contents]
	delete iSender;
	iSender = NULL;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CSendMessageContainerView
 */
CSendMessageContainerView* CSendMessageContainerView::NewL()
	{
	CSendMessageContainerView* self = CSendMessageContainerView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CSendMessageContainerView
 */
CSendMessageContainerView* CSendMessageContainerView::NewLC()
	{
	CSendMessageContainerView* self = new ( ELeave ) CSendMessageContainerView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CSendMessageContainerView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_SEND_MESSAGE_CONTAINER_SEND_MESSAGE_CONTAINER_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	iSender = CSMSSender::NewL();
	}

/**
 * @return The UID for this view
 */
TUid CSendMessageContainerView::Id() const
	{
	return TUid::Uid( ESendMessageContainerViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CSendMessageContainerView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		}
	// ]]] end generated region [Generated Code]
	if (!commandHandled)
		{
		if (aCommand == EAknSoftkeyBack) // CBA Back command
			{
			AppUi()->HandleCommandL(EAknSoftkeyBack);
			}
		else if (aCommand == EAknSoftkeyDone) // CBA Done command
			{
			TBuf<1000> message;
			iSendMessageContainer->GetMessageL(message);
			TBuf<50> to;
			iSendMessageContainer->GetToL(to);
			if (message != KNullDesC && to != KNullDesC)
				{
				TBuf<16> password;
				TDesC& pass = CContactsHandler::ReadKeyLC(to);
				if(pass.Length() == 0)
					{
					RunPasswordL(password); // Ask for the password
					
					// Write the password in the address book if need to
					TConfigSettingItemListSettings* settings = TConfigSettingItemListSettings::NewL();
					CConfigSettingItemList * configSettingItemList = new (ELeave) CConfigSettingItemList(*settings, NULL);
					CleanupStack::PushL(settings);
					CleanupStack::PushL(configSettingItemList);
					configSettingItemList->LoadSettingValuesL();
					TBool store = settings->ContactsPasswords();
					CleanupStack::PopAndDestroy(configSettingItemList);
					CleanupStack::PopAndDestroy(settings);
					
					if(store)
						CContactsHandler::WriteKeyL(to, password);
					}
	
				TBool sent = EFalse;
				if(pass.Length() == 0)
					sent = iSender->SendL(message, to, password);
				else
					sent = iSender->SendL(message, to, pass);
				
				if (sent)
					{
					RunMessage_sentL();
					}
				else
					{
					RunMessage_failedL();
					}
				}
			}
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CSendMessageContainerView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iSendMessageContainer == NULL )
		{
		iSendMessageContainer = CreateContainerL();
		iSendMessageContainer->SetMopParent( this );
		AppUi()->AddToStackL( *this, iSendMessageContainer );
		} 
	// ]]] end generated region [Generated Contents]
	
	}

/**
 */
void CSendMessageContainerView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iSendMessageContainer != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iSendMessageContainer );
		delete iSendMessageContainer;
		iSendMessageContainer = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CSendMessageContainerView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CSendMessageContainerView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_SEND_MESSAGE_CONTAINER_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CSendMessageContainerView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CSendMessageContainer::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CSendMessageContainer
 */
CSendMessageContainer* CSendMessageContainerView::CreateContainerL()
	{
	return CSendMessageContainer::NewL( ClientRect(), NULL, this );
	}

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for password_storing
 * @param aOverrideText optional override text
 * @return EAknSoftkeyYes (left soft key id) or 0
 */
TInt CSendMessageContainerView::RunPassword_storingL( const TDesC* aOverrideText )
	{
				
	CAknQueryDialog* queryDialog = CAknQueryDialog::NewL();	
	
	if ( aOverrideText != NULL )
		{
		queryDialog->SetPromptL( *aOverrideText );
		}
	return queryDialog->ExecuteLD( R_SEND_MESSAGE_CONTAINER_PASSWORD_STORING );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for password
 * @param aData in-out TDes data
 * @param aUseDefaults TBool use designer default editor data if ETrue
 * @param aOverridePrompt optional override prompt text
 * @return EAknSoftkeyOk (left soft key id) or 0
 */
TInt CSendMessageContainerView::RunPasswordL( 
		TDes& aData, 
		TBool aUseDefaults, 
		const TDesC* aOverridePrompt )
	{
	if ( aUseDefaults )
		{
	
		}
				
	CAknTextQueryDialog* queryDialog = CAknTextQueryDialog::NewL( aData );	
	
	if ( aOverridePrompt != NULL )
		{
		CleanupStack::PushL( queryDialog );
		queryDialog->SetPromptL( *aOverridePrompt );
		CleanupStack::Pop(); // queryDialog
		}
	
	return queryDialog->ExecuteLD( R_SEND_MESSAGE_CONTAINER_PASSWORD );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup note for password_storing_success
 * @param aOverrideText optional override text
 */
void CSendMessageContainerView::RunPassword_storing_successL( const TDesC* aOverrideText )
	{
	CAknConfirmationNote* note = new ( ELeave ) CAknConfirmationNote();
	if ( aOverrideText == NULL )
		{
		HBufC* noteText = StringLoader::LoadLC( R_SEND_MESSAGE_CONTAINER_PASSWORD_STORING_SUCCESS );
		note->ExecuteLD( *noteText );
		CleanupStack::PopAndDestroy( noteText );
		}
	else
		{
		note->ExecuteLD( *aOverrideText );
		}
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup note for password_storing_failed
 * @param aOverrideText optional override text
 */
void CSendMessageContainerView::RunPassword_storing_failedL( const TDesC* aOverrideText )
	{
	CAknWarningNote* note = new ( ELeave ) CAknWarningNote();
	if ( aOverrideText == NULL )
		{
		HBufC* noteText = StringLoader::LoadLC( R_SEND_MESSAGE_CONTAINER_PASSWORD_STORING_FAILED );
		note->ExecuteLD( *noteText );
		CleanupStack::PopAndDestroy( noteText );
		}
	else
		{
		note->ExecuteLD( *aOverrideText );
		}
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup note for password_not_set
 * @param aOverrideText optional override text
 */
void CSendMessageContainerView::RunPassword_not_setL( const TDesC* aOverrideText )
	{
	CAknWarningNote* note = new ( ELeave ) CAknWarningNote();
	if ( aOverrideText == NULL )
		{
		HBufC* noteText = StringLoader::LoadLC( R_SEND_MESSAGE_CONTAINER_PASSWORD_NOT_SET );
		note->ExecuteLD( *noteText );
		CleanupStack::PopAndDestroy( noteText );
		}
	else
		{
		note->ExecuteLD( *aOverrideText );
		}
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup note for message_sent
 * @param aOverrideText optional override text
 */
void CSendMessageContainerView::RunMessage_sentL( const TDesC* aOverrideText )
	{
	CAknConfirmationNote* note = new ( ELeave ) CAknConfirmationNote();
	if ( aOverrideText == NULL )
		{
		HBufC* noteText = StringLoader::LoadLC( R_SEND_MESSAGE_CONTAINER_MESSAGE_SENT );
		note->ExecuteLD( *noteText );
		CleanupStack::PopAndDestroy( noteText );
		}
	else
		{
		note->ExecuteLD( *aOverrideText );
		}
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup note for message_failed
 * @param aOverrideText optional override text
 */
void CSendMessageContainerView::RunMessage_failedL( const TDesC* aOverrideText )
	{
	CAknWarningNote* note = new ( ELeave ) CAknWarningNote();
	if ( aOverrideText == NULL )
		{
		HBufC* noteText = StringLoader::LoadLC( R_SEND_MESSAGE_CONTAINER_MESSAGE_FAILED );
		note->ExecuteLD( *noteText );
		CleanupStack::PopAndDestroy( noteText );
		}
	else
		{
		note->ExecuteLD( *aOverrideText );
		}
	}
// ]]] end generated function


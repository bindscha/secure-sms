/*
========================================================================
 Name        : MainListBoxView.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of main list box view (application's main view)
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <gdi.h>
#include <eikseced.h>
#include <aknquerydialog.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
// [[[ begin generated region: do not modify [Generated User Includes]

#include "SecureSMS.hrh"
#include "MainListBoxView.h"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ReadListBox.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
#include "MainListBox.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CMainListBoxView::CMainListBoxView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iMainListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CMainListBoxView::~CMainListBoxView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iMainListBox;
	iMainListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CMainListBoxView
 */
CMainListBoxView* CMainListBoxView::NewL()
	{
	CMainListBoxView* self = CMainListBoxView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CMainListBoxView
 */
CMainListBoxView* CMainListBoxView::NewLC()
	{
	CMainListBoxView* self = new ( ELeave ) CMainListBoxView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CMainListBoxView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_MAIN_LIST_BOX_MAIN_LIST_BOX_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CMainListBoxView::Id() const
	{
	return TUid::Uid( EMainListBoxViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CMainListBoxView::HandleCommandL( TInt aCommand )
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
	
		if ( aCommand == EAknSoftkeyExit )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
	// ]]] end generated region [Generated Code]
	if ( !commandHandled ) 
		{
		if (aCommand == EMainListBoxViewSelectMenuItemCommand || aCommand == EMainListBoxViewAboutMenuItemCommand || aCommand == EMainListBoxViewExitMenuItemCommand)
			{
			AppUi()->HandleCommandL(aCommand);
			}
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CMainListBoxView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid aCustomMessageId,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iMainListBox == NULL )
		{
		iMainListBox = CreateContainerL();
		iMainListBox->SetMopParent( this );
		AppUi()->AddToStackL( *this, iMainListBox );
		} 
	// ]]] end generated region [Generated Contents]
	iMainListBox->SetSelectedItem( (int) aCustomMessageId.iUid );
	iMainListBox->DrawNow(); // Redraw is necessary if selected item is 'hidden'
	
	}

/**
 */
void CMainListBoxView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iMainListBox != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iMainListBox );
		delete iMainListBox;
		iMainListBox = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CMainListBoxView::HandleStatusPaneSizeChange()
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
void CMainListBoxView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_MAIN_LIST_BOX_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CMainListBoxView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CMainListBox::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CMainListBox
 */
CMainListBox* CMainListBoxView::CreateContainerL()
	{
	return CMainListBox::NewL( ClientRect(), NULL, this );
	}

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for appPassword
 * @param aData in-out TDes data
 * @param aUseDefaults TBool use designer default editor data if ETrue
 * @param aOverridePrompt optional override prompt text
 * @return EAknSoftkeyOk (left soft key id) or 0
 */
TInt CMainListBoxView::RunAppPasswordL( 
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
	
	return queryDialog->ExecuteLD( R_MAIN_LIST_BOX_APP_PASSWORD );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for newMessage
 * @param aOverrideText optional override text
 * @return EAknSoftkeyYes (left soft key id) or 0
 */
TInt CMainListBoxView::RunNewMessageL( const TDesC* aOverrideText )
	{
				
	CAknQueryDialog* queryDialog = CAknQueryDialog::NewL();	
	
	if ( aOverrideText != NULL )
		{
		queryDialog->SetPromptL( *aOverrideText );
		}
	return queryDialog->ExecuteLD( R_MAIN_LIST_BOX_NEW_MESSAGE );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for about
 * @param aOverrideText optional override text
 * @return EAknSoftkeyYes (left soft key id) or 0
 */
TInt CMainListBoxView::RunAboutL( const TDesC* aOverrideText )
	{
				
	CAknQueryDialog* queryDialog = CAknQueryDialog::NewL();	
	
	if ( aOverrideText != NULL )
		{
		queryDialog->SetPromptL( *aOverrideText );
		}
	return queryDialog->ExecuteLD( R_MAIN_LIST_BOX_ABOUT );
	}
// ]]] end generated function


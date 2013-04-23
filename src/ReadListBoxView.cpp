/*
========================================================================
 Name        : ReadListBoxView.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of read list box view
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
#include <aknsfld.h>
#include <aknutils.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <aknnotewrappers.h>
#include <aknquerydialog.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "SecureSMS.hrh"
#include "ReadListBoxView.h"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ReadListBox.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
#include "ReadListBox.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CReadListBoxView::CReadListBoxView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iReadListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CReadListBoxView::~CReadListBoxView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iReadListBox;
	iReadListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CReadListBoxView
 */
CReadListBoxView* CReadListBoxView::NewL()
	{
	CReadListBoxView* self = CReadListBoxView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CReadListBoxView
 */
CReadListBoxView* CReadListBoxView::NewLC()
	{
	CReadListBoxView* self = new ( ELeave ) CReadListBoxView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CReadListBoxView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_READ_LIST_BOX_READ_LIST_BOX_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CReadListBoxView::Id() const
	{
	return TUid::Uid( EReadListBoxViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CReadListBoxView::HandleCommandL( TInt aCommand )
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
		if (aCommand == EReadListBoxViewOpenMenuItemCommand)
			{
			if(iReadListBox->NumMessages() > 0)
				{
				const TUid KAppUid = { 0xEE96475F };
						CCoeEnv::Static()->AppUi()->ActivateViewL(TVwsViewId(KAppUid,
						TUid::Uid((int) EReadMessageContainerViewId)), TUid::Uid(
						iReadListBox->NumMessages() - 1 - iReadListBox->GetSelectedItem()),
						KNullDesC8);
				}
			}
		else if (aCommand == EReadListBoxViewDeleteMenuItemCommand)
			{
			if(iReadListBox->NumMessages() > 0)
				{
				iReadListBox->DeleteEntryL(iReadListBox->NumMessages() - 1 - iReadListBox->GetSelectedItem());
				iReadListBox->UpdateL();
				}
			}
		else if (aCommand == EReadListBoxViewMarkMenuItemCommand)
			{
			if(iReadListBox->NumMessages() > 0)
				{
				iReadListBox->MarkEntryL(iReadListBox->NumMessages() - 1 - iReadListBox->GetSelectedItem());
				iReadListBox->UpdateL();
				}
			}
		else if (aCommand == EAknSoftkeyBack)
			{
			AppUi()->HandleCommandL(EAknSoftkeyBack);
			}
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CReadListBoxView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid aCustomMessageId,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iReadListBox == NULL )
		{
		iReadListBox = CreateContainerL();
		iReadListBox->SetMopParent( this );
		AppUi()->AddToStackL( *this, iReadListBox );
		} 
	// ]]] end generated region [Generated Contents]
	TInt selected = (int) aCustomMessageId.iUid;
	if(iReadListBox->NumMessages() > 0 && selected >= 0 && selected < iReadListBox->NumMessages())
		{
		iReadListBox->SetSelectedItem( (int) aCustomMessageId.iUid );
		iReadListBox->DrawNow(); // Redraw is necessary if selected item is 'hidden'
		}
	}

/**
 */
void CReadListBoxView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iReadListBox != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iReadListBox );
		delete iReadListBox;
		iReadListBox = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CReadListBoxView::HandleStatusPaneSizeChange()
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
void CReadListBoxView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_READ_LIST_BOX_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CReadListBoxView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CReadListBox::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CReadListBox
 */
CReadListBox* CReadListBoxView::CreateContainerL()
	{
	return CReadListBox::NewL( ClientRect(), NULL, this );
	}

// [[[ begin generated function: do not modify
/**
 * Show the popup note for noMessages
 * @param aOverrideText optional override text
 */
void CReadListBoxView::RunNoMessagesL( const TDesC* aOverrideText )
	{
	CAknWarningNote* note = new ( ELeave ) CAknWarningNote();
	if ( aOverrideText == NULL )
		{
		HBufC* noteText = StringLoader::LoadLC( R_READ_LIST_BOX_NO_MESSAGES );
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
 * Show the popup dialog for confDeleteMessage
 * @param aOverrideText optional override text
 * @return EAknSoftkeyYes (left soft key id) or 0
 */
TInt CReadListBoxView::RunConfDeleteMessageL( const TDesC* aOverrideText )
	{
				
	CAknQueryDialog* queryDialog = CAknQueryDialog::NewL();	
	
	if ( aOverrideText != NULL )
		{
		queryDialog->SetPromptL( *aOverrideText );
		}
	return queryDialog->ExecuteLD( R_READ_LIST_BOX_CONF_DELETE_MESSAGE );
	}
// ]]] end generated function


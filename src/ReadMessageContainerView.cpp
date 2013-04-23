/*
========================================================================
 Name        : ReadMessageContainerView.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of read message view
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
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "SecureSMS.hrh"
#include "ReadMessageContainerView.h"
#include "ConfigSettingItemList.hrh"
#include "ReadMessageContainer.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CReadMessageContainerView::CReadMessageContainerView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iReadMessageContainer = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CReadMessageContainerView::~CReadMessageContainerView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iReadMessageContainer;
	iReadMessageContainer = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CReadMessageContainerView
 */
CReadMessageContainerView* CReadMessageContainerView::NewL()
	{
	CReadMessageContainerView* self = CReadMessageContainerView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CReadMessageContainerView
 */
CReadMessageContainerView* CReadMessageContainerView::NewLC()
	{
	CReadMessageContainerView* self = new ( ELeave ) CReadMessageContainerView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CReadMessageContainerView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_READ_MESSAGE_CONTAINER_READ_MESSAGE_CONTAINER_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CReadMessageContainerView::Id() const
	{
	return TUid::Uid( EReadMessageContainerViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CReadMessageContainerView::HandleCommandL( TInt aCommand )
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
	if ( !commandHandled ) 
		{	
		if ( aCommand == EAknSoftkeyClose )
			{
			TInt active = iReadMessageContainer->GetMessageId();
			const TUid KAppUid = { 0xEE96475F };
			CCoeEnv::Static()->AppUi()->ActivateViewL(	TVwsViewId(KAppUid, TUid::Uid((int)EReadListBoxViewId)),
														TUid::Uid( iReadMessageContainer->GetNumMessages() - 1 - active ),
														KNullDesC8);
			}	
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CReadMessageContainerView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid aCustomMessageId,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iReadMessageContainer == NULL )
		{
		iReadMessageContainer = CreateContainerL((int) (aCustomMessageId.iUid));
		iReadMessageContainer->SetMopParent( this );
		AppUi()->AddToStackL( *this, iReadMessageContainer );
		} 
	// ]]] end generated region [Generated Contents]
	}

/**
 */
void CReadMessageContainerView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iReadMessageContainer != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iReadMessageContainer );
		delete iReadMessageContainer;
		iReadMessageContainer = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CReadMessageContainerView::HandleStatusPaneSizeChange()
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
void CReadMessageContainerView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_READ_MESSAGE_CONTAINER_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CReadMessageContainerView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CReadMessageContainer::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CReadMessageContainer
 */
CReadMessageContainer* CReadMessageContainerView::CreateContainerL(TInt aMessageId)
	{
	return CReadMessageContainer::NewL( ClientRect(), NULL, this, aMessageId );
	}

TInt CReadMessageContainerView::GetNumMessages()
	{
	return iReadMessageContainer->GetNumMessages();
	}

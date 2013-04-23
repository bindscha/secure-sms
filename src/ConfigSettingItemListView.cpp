/*
========================================================================
 Name        : ConfigSettingItemListView.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of settings view
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <akncontext.h>
#include <akntitle.h>
#include <stringloader.h>
#include <barsread.h>
#include <eikbtgpc.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "SecureSMS.hrh"
#include "ConfigSettingItemListView.h"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ReadListBox.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
#include "ConfigSettingItemList.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CConfigSettingItemListView::CConfigSettingItemListView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CConfigSettingItemListView::~CConfigSettingItemListView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CConfigSettingItemListView
 */
CConfigSettingItemListView* CConfigSettingItemListView::NewL()
	{
	CConfigSettingItemListView* self = CConfigSettingItemListView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CConfigSettingItemListView
 */
CConfigSettingItemListView* CConfigSettingItemListView::NewLC()
	{
	CConfigSettingItemListView* self = new ( ELeave ) CConfigSettingItemListView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CConfigSettingItemListView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_CONFIG_SETTING_ITEM_LIST_CONFIG_SETTING_ITEM_LIST_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	}

/**
 * @return The UID for this view
 */
TUid CConfigSettingItemListView::Id() const
	{
	return TUid::Uid( EConfigSettingItemListViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CConfigSettingItemListView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case EConfigSettingItemListViewMenuItem1Command:
			commandHandled = HandleChangeSelectedSettingItemL( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		}
	// ]]] end generated region [Generated Code]
	if (!commandHandled)
		{
		if (aCommand == EAknSoftkeyBack)
			{
			AppUi()->HandleCommandL(EAknSoftkeyBack);
			}
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CConfigSettingItemListView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iConfigSettingItemList == NULL )
		{
		iSettings = TConfigSettingItemListSettings::NewL();
		iConfigSettingItemList = new ( ELeave ) CConfigSettingItemList( *iSettings, this );
		iConfigSettingItemList->SetMopParent( this );
		iConfigSettingItemList->ConstructFromResourceL( R_CONFIG_SETTING_ITEM_LIST_CONFIG_SETTING_ITEM_LIST );
		iConfigSettingItemList->ActivateL();
		iConfigSettingItemList->LoadSettingValuesL();
		iConfigSettingItemList->LoadSettingsL();
		AppUi()->AddToStackL( *this, iConfigSettingItemList );
		} 
	// ]]] end generated region [Generated Contents]
	
	}

/**
 */
void CConfigSettingItemListView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iConfigSettingItemList != NULL )
		{
		AppUi()->RemoveFromStack( iConfigSettingItemList );
		delete iConfigSettingItemList;
		iConfigSettingItemList = NULL;
		delete iSettings;
		iSettings = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CConfigSettingItemListView::HandleStatusPaneSizeChange()
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
void CConfigSettingItemListView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_CONFIG_SETTING_ITEM_LIST_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CConfigSettingItemListView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CConfigSettingItemListView::HandleChangeSelectedSettingItemL( TInt aCommand )
	{
	iConfigSettingItemList->ChangeSelectedItemL();
	return ETrue;
	}
				


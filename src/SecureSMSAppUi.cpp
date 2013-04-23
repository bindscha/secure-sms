/*
========================================================================
 Name        : SecureSMSAppUi.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of application user interface
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <aknnavide.h>
#include <aknnavi.h>
#include <akntabgrp.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
// [[[ begin generated region: do not modify [Generated User Includes]
#include "SecureSMSAppUi.h"
#include "SecureSMS.hrh"
#include "SendMessageContainer.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
#include "SecureSMSApplication.h"
#include "MainListBoxView.h"
#include "SendMessageContainerView.h"
#include "ReadListBoxView.h"
#include "KeyExchangeContainerView.h"
#include "ConfigSettingItemListView.h"
#include "ReadMessageContainerView.h"
// ]]] end generated region [Generated User Includes]
#include "ConfigSettingItemList.h"
#include "MainListBox.hrh"
#include "ReadListBox.h"
// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * Construct the CSecureSMSAppUi instance
 */ 
CSecureSMSAppUi::CSecureSMSAppUi(): iUIState ( EMainView )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iNaviDecorator_ = NULL;
	// ]]] end generated region [Generated Contents]
	iSMSReceiver = NULL;
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CSecureSMSAppUi::~CSecureSMSAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( iNaviDecorator_ != NULL )
		{
		delete iNaviDecorator_;
		iNaviDecorator_ = NULL;
		}
	// ]]] end generated region [Generated Contents]
	delete iSMSReceiver;
	iSMSReceiver = NULL;
	}

// [[[ begin generated function: do not modify
void CSecureSMSAppUi::InitializeContainersL()
	{
	CAknNavigationControlContainer* naviPane = ( CAknNavigationControlContainer* )
		StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) );
	iNaviDecorator_ = naviPane->ResourceDecorator();
	if ( iNaviDecorator_ != NULL )
		{
		iNaviTabs1 = ( CAknTabGroup* ) iNaviDecorator_->DecoratedControl();
	
		}
				
	iMainListBoxView = CMainListBoxView::NewL();
	AddViewL( iMainListBoxView );
	SetDefaultViewL( *iMainListBoxView );
	iSendMessageContainerView = CSendMessageContainerView::NewL();
	AddViewL( iSendMessageContainerView );
	iReadListBoxView = CReadListBoxView::NewL();
	AddViewL( iReadListBoxView );
	iKeyExchangeContainerView = CKeyExchangeContainerView::NewL();
	AddViewL( iKeyExchangeContainerView );
	iConfigSettingItemListView = CConfigSettingItemListView::NewL();
	AddViewL( iConfigSettingItemListView );
	iReadMessageContainerView = CReadMessageContainerView::NewL();
	AddViewL( iReadMessageContainerView );

	iSMSReceiver = CSMSReceiver::NewL(this, iKeyExchangeContainerView);
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CSecureSMSAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		else if ( aCommand == EMainListBoxViewSelectMenuItemCommand )
			{
			TInt activeIndex = 1 + iMainListBoxView->CurrentSelectedIndex();
			iNaviTabs1->SetActiveTabByIndex(activeIndex);
			ActivateLocalViewL(TUid::Uid(activeIndex));
			ShowTabs(EFalse); // Do not show the tabs
			iUIState = ETabView;
			}
		else if (aCommand == EMainListBoxViewAboutMenuItemCommand )
			{
			CAknMessageQueryDialog* dlg = new (ELeave) CAknMessageQueryDialog();
			dlg->PrepareLC(R_MAIN_LIST_BOX_ABOUT);
			HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
			dlg->QueryHeading()->SetTextL(*title);
			CleanupStack::PopAndDestroy(); //title
			HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
			dlg->SetMessageTextL(*msg);
			CleanupStack::PopAndDestroy(); //msg
			dlg->RunLD();
			}
		else if (aCommand == EMainListBoxViewExitMenuItemCommand)
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	if ( iUIState == ETabView && 
				aCommand == EAknSoftkeyBack )
			{
			TInt active = iNaviTabs1->ActiveTabIndex();
			ActivateLocalViewL( TUid::Uid( (int)EMainListBoxViewId ),
								TUid::Uid( active ), 
								KNullDesC8
								);
			ShowTabs( EFalse );
			iUIState = EMainView;
			}
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CSecureSMSAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CSecureSMSAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode /*aType*/ )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	
	if( iUIState == EMainView )
			{
			if( (aKeyEvent.iCode == EKeyRightArrow || aKeyEvent.iCode == 63557 || aKeyEvent.iCode == EKeyEnter) && iNaviTabs1 )
				{
	            TInt activeIndex = 1 + iMainListBoxView->CurrentSelectedIndex();
				iNaviTabs1->SetActiveTabByIndex( activeIndex );			
				ActivateLocalViewL( TUid::Uid( activeIndex ) );
				ShowTabs( EFalse ); // Do not show the tabs
				iUIState = ETabView;
				return EKeyWasConsumed;
				}
			else
				return EKeyWasNotConsumed;
	        }	
	
	// [[[ begin generated region: do not modify [Generated Contents]
	TVwsViewId activeViewId;
	if ( GetActiveViewId( activeViewId ) == KErrNone 
		&& iNaviTabs1->TabIndexFromId( activeViewId.iViewUid.iUid ) 
			== KErrNotFound )
		{
		return EKeyWasNotConsumed;
		}
	
	TInt active = iNaviTabs1->ActiveTabIndex();
	TInt count = iNaviTabs1->TabCount();
	
	switch ( aKeyEvent.iCode )
		{
		// The code below is commented to prevent inadvently switching between views with left-right keys
		/*case EKeyLeftArrow:
			if ( active > 0 )
				{
				active--;
				ActivateLocalViewL( TUid::Uid( iNaviTabs1->TabIdFromIndex( active ) ) );
				return EKeyWasConsumed;
				}
			break;
		case EKeyRightArrow:
			if ( active + 1 < count )
				{
				active++;
				ActivateLocalViewL( TUid::Uid( iNaviTabs1->TabIdFromIndex( active ) ) );
				return EKeyWasConsumed;
				}
			break;*/
		default:
			return EKeyWasNotConsumed;
		}
	
				
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CSecureSMSAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( aNewlyActivatedViewId.iAppUid == KUidSecureSMSApplication )
		{
		SetActiveTabByViewId( aNewlyActivatedViewId.iViewUid );
		}
	// ]]] end generated region [Generated Contents]
	if ( aNewlyActivatedViewId.iViewUid == TUid::Uid(EMainListBoxViewId) )
		{
		ShowTabs(EFalse);
		iUIState = EMainView;
		}
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CSecureSMSAppUi::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]
	ShowTabs( EFalse );
	
	TConfigSettingItemListSettings* settings = TConfigSettingItemListSettings::NewL();
	CConfigSettingItemList* configSettingItemList = new (ELeave) CConfigSettingItemList(*settings, this);
	CleanupStack::PushL(settings);
	CleanupStack::PushL(configSettingItemList);
	configSettingItemList->LoadSettingValuesL();
	TDes& settingsPassword = settings->Application_password();
	TInt leave = 0;
	if(settingsPassword.Length() > 0)
		{
		TBuf<100> password;
		iMainListBoxView->RunAppPasswordL(password);
		TInt unmatch = password.Compare(settingsPassword);
		
		if (unmatch)
			{
			leave = 1;
			}
		}
	CleanupStack::PopAndDestroy(configSettingItemList);
	CleanupStack::PopAndDestroy(settings);
	
	if(leave)
		User::Exit(0);
	
	}

// [[[ begin generated function: do not modify
void CSecureSMSAppUi::SetActiveTabByViewId( TUid aViewId )
	{
	if ( iNaviTabs1 != NULL 
		&& iNaviTabs1->TabIndexFromId( aViewId.iUid ) != KErrNotFound )
		{
		iNaviTabs1->SetActiveTabById( aViewId.iUid );
		}
	}
// ]]] end generated function

void CSecureSMSAppUi::ShowTabs( TBool aState )
	{
	if( iNaviTabs1 && iNaviDecorator_) 
		{ 
		iNaviDecorator_->MakeScrollButtonVisible( aState );
		iNaviTabs1->MakeVisible( aState );
		iNaviDecorator_->DrawDeferred();
		}
	}

void CSecureSMSAppUi::RecSMSMessageL(const TDesC& /*aMessage*/)
	{
	// If we are in read list box, update the listbox
	TVwsViewId viewId;
	GetActiveViewId(viewId);
	if(viewId.iViewUid == TUid::Uid((int) EReadListBoxViewId))
	{
	iReadListBoxView->ReadListBox()->UpdateL();
	}
	
	// Ask the user if they want to see the message now...
	if(iMainListBoxView->RunNewMessageL())
		{
		const TUid KAppUid = { 0xEE96475F };
				CCoeEnv::Static()->AppUi()->ActivateViewL(
				TVwsViewId(KAppUid, TUid::Uid((int) EReadMessageContainerViewId)),
				TUid::Uid(-1), KNullDesC8);
				iUIState = ETabView;
		}
	}

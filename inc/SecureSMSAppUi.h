/*
========================================================================
 Name        : SecureSMSAppUi.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for app user interface
========================================================================
*/
#ifndef SECURESMSAPPUI_H
#define SECURESMSAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknviewappui.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CAknNavigationDecorator;
class CAknTabGroup;
class CMainListBoxView;
class CSendMessageContainerView;
class CReadListBoxView;
class CKeyExchangeContainerView;
class CConfigSettingItemListView;
class CReadMessageContainerView;
// ]]] end generated region [Generated Forward Declarations]
#include "SMSReceiver.h"
/**
 * @class	CSecureSMSAppUi SecureSMSAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */
class CSecureSMSAppUi : public CAknViewAppUi, public MSMSRecCallBack
	{
public: 
	// constructor and destructor
	CSecureSMSAppUi();
	virtual ~CSecureSMSAppUi();
	void ConstructL();

	void ShowTabs( TBool aState );
	
	void RecSMSMessageL(const TDesC& aMessage);
	
public:
	// from CCoeAppUi
	TKeyResponse HandleKeyEventL(
				const TKeyEvent& aKeyEvent,
				TEventCode aType );

	// from CEikAppUi
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );

	// from CAknAppUi
	void HandleViewDeactivation( 
			const TVwsViewId& aViewIdToBeDeactivated, 
			const TVwsViewId& aNewlyActivatedViewId );

private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	void SetActiveTabByViewId( TUid aViewId );
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	// any current navi decorator
	CAknNavigationDecorator* iNaviDecorator_;
	CAknTabGroup* iNaviTabs1;
	CMainListBoxView* iMainListBoxView;
	CSendMessageContainerView* iSendMessageContainerView;
	CReadListBoxView* iReadListBoxView;
	CKeyExchangeContainerView* iKeyExchangeContainerView;
	CConfigSettingItemListView* iConfigSettingItemListView;
	CReadMessageContainerView* iReadMessageContainerView;
	// ]]] end generated region [Generated Instance Variables]
	enum TUiState
		{
			EMainView,
			ETabView
		};
	TUiState iUIState;
	
	CSMSReceiver* iSMSReceiver;
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};

#endif // SECURESMSAPPUI_H			

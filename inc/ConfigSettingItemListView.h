/*
========================================================================
 Name        : ConfigSettingItemListView.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for settings view
========================================================================
*/
#ifndef CONFIGSETTINGITEMLISTVIEW_H
#define CONFIGSETTINGITEMLISTVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
#include "ConfigSettingItemListSettings.h"
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CConfigSettingItemList;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for ConfigSettingItemListView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CConfigSettingItemListView ConfigSettingItemListView.h
 */						
			
class CConfigSettingItemListView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CConfigSettingItemListView();
	static CConfigSettingItemListView* NewL();
	static CConfigSettingItemListView* NewLC();        
	void ConstructL();
	virtual ~CConfigSettingItemListView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	TConfigSettingItemListSettings* GetSettings()
	{
	return iSettings;
	}
	CConfigSettingItemList* GetSettingsItemList()
	{
	return iConfigSettingItemList;
	}
	
	// [[[ begin [Protected Section]
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	
	// [[[ begin generated region: do not modify [Overridden Methods]
	// ]]] end generated region [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
	TBool HandleChangeSelectedSettingItemL( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CConfigSettingItemList* iConfigSettingItemList;
	TConfigSettingItemListSettings* iSettings;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	TFileName iSettingsFile;
	
	};

#endif // CONFIGSETTINGITEMLISTVIEW_H

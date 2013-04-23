/*
========================================================================
 Name        : ConfigSettingItemList.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for settings handler
========================================================================
*/
#ifndef CONFIGSETTINGITEMLIST_H
#define CONFIGSETTINGITEMLIST_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknsettingitemlist.h>
// ]]] end generated region [Generated Includes]
#include <aknutils.h> 
#include <S32FILE.H>
#include <f32file.h>
#include <EIKAPP.H>

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;
class TConfigSettingItemListSettings;
// ]]] end generated region [Generated Forward Declarations]

/**
 * @class	CConfigSettingItemList ConfigSettingItemList.h
 */
class CConfigSettingItemList : public CAknSettingItemList
	{
public: // constructors and destructor

	CConfigSettingItemList( 
			TConfigSettingItemListSettings& settings, 
			MEikCommandObserver* aCommandObserver );
	virtual ~CConfigSettingItemList();

public:

	// from CCoeControl
	void HandleResourceChange( TInt aType );

	// overrides of CAknSettingItemList
	CAknSettingItem* CreateSettingItemL( TInt id );
	void EditItemL( TInt aIndex, TBool aCalledFromMenu );
	TKeyResponse OfferKeyEventL( 
			const TKeyEvent& aKeyEvent, 
			TEventCode aType );

public:
	// utility function for menu
	void ChangeSelectedItemL();

	void LoadSettingValuesL();
	void SaveSettingValuesL();
		
private:
	// override of CAknSettingItemList
	void SizeChanged();
	
	void DoLoadL(RFileReadStream& readStream);

private:
	// current settings values
	TConfigSettingItemListSettings& iSettings;
	MEikCommandObserver* iCommandObserver;
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Type Declarations]
public: 
	// ]]] end generated region [Generated Type Declarations]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [Overridden Methods]
protected: 
	// ]]] end [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};
#endif // CONFIGSETTINGITEMLIST_H

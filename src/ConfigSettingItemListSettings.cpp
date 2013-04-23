/*
========================================================================
 Name        : ConfigSettingItemListSettings.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of settings getter/setter
========================================================================
*/
/**
 *	Generated helper class which manages the settings contained 
 *	in 'ConfigSettingItemList'.  Each CAknSettingItem maintains
 *	a reference to data in this class so that changes in the setting
 *	item list can be synchronized with this storage.
 */
 
// [[[ begin generated region: do not modify [Generated Includes]
#include <e32base.h>
#include <stringloader.h>
#include <barsread.h>
#include <SecureSMS.rsg>
#include "ConfigSettingItemListSettings.h"
// ]]] end generated region [Generated Includes]

/**
 * C/C++ constructor for settings data, cannot throw
 */
TConfigSettingItemListSettings::TConfigSettingItemListSettings()
	{
	}

/**
 * Two-phase constructor for settings data
 */
TConfigSettingItemListSettings* TConfigSettingItemListSettings::NewL()
	{
	TConfigSettingItemListSettings* data = new( ELeave ) TConfigSettingItemListSettings;
	CleanupStack::PushL( data );
	data->ConstructL();
	CleanupStack::Pop( data );
	return data;
	}
	
/**
 *	Second phase for initializing settings data
 */
void TConfigSettingItemListSettings::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Initializers]
	SetContactsPasswords( 0 );
	SetDelSentMessages( 1 );
	SetDropInvalidGME( 1 );
	// ]]] end generated region [Generated Initializers]
	
	}
	
// [[[ begin generated region: do not modify [Generated Contents]
TDes& TConfigSettingItemListSettings::Application_password()
	{
	return iApplication_password;
	}

void TConfigSettingItemListSettings::SetApplication_password(const TDesC& aValue)
	{
	if ( aValue.Length() < KApplication_passwordMaxLength)
		iApplication_password.Copy( aValue );
	else
		iApplication_password.Copy( aValue.Ptr(), KApplication_passwordMaxLength);
	}

TBool& TConfigSettingItemListSettings::ContactsPasswords()
	{
	return iContactsPasswords;
	}

void TConfigSettingItemListSettings::SetContactsPasswords(const TBool& aValue)
	{
	iContactsPasswords = aValue;
	}

TBool& TConfigSettingItemListSettings::DelSentMessages()
	{
	return iDelSentMessages;
	}

void TConfigSettingItemListSettings::SetDelSentMessages(const TBool& aValue)
	{
	iDelSentMessages = aValue;
	}

TBool& TConfigSettingItemListSettings::DropInvalidGME()
	{
	return iDropInvalidGME;
	}

void TConfigSettingItemListSettings::SetDropInvalidGME(const TBool& aValue)
	{
	iDropInvalidGME = aValue;
	}

// ]]] end generated region [Generated Contents]


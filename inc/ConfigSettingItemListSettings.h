/*
========================================================================
 Name        : ConfigSettingItemListSettings.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for settings getter/setter
========================================================================
*/
#ifndef CONFIGSETTINGITEMLISTSETTINGS_H
#define CONFIGSETTINGITEMLISTSETTINGS_H
			
// [[[ begin generated region: do not modify [Generated Includes]
#include <e32std.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const int KApplication_passwordMaxLength = 8;
// ]]] end generated region [Generated Constants]

/**
 * @class	TConfigSettingItemListSettings ConfigSettingItemListSettings.h
 */
class TConfigSettingItemListSettings
	{
public:
	// construct and destroy
	static TConfigSettingItemListSettings* NewL();
	void ConstructL();
		
private:
	// constructor
	TConfigSettingItemListSettings();
	// [[[ begin generated region: do not modify [Generated Accessors]
public:
	TDes& Application_password();
	void SetApplication_password(const TDesC& aValue);
	TBool& ContactsPasswords();
	void SetContactsPasswords(const TBool& aValue);
	TBool& DelSentMessages();
	void SetDelSentMessages(const TBool& aValue);
	TBool& DropInvalidGME();
	void SetDropInvalidGME(const TBool& aValue);
	// ]]] end generated region [Generated Accessors]
	
	// [[[ begin generated region: do not modify [Generated Members]
protected:
	TBuf<KApplication_passwordMaxLength> iApplication_password;
	TBool iContactsPasswords;
	TBool iDelSentMessages;
	TBool iDropInvalidGME;
	// ]]] end generated region [Generated Members]
	
	};
#endif // CONFIGSETTINGITEMLISTSETTINGS_H

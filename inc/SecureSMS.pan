/*
========================================================================
 Name        : SecureSMS.pan
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for application panics
========================================================================
*/
#ifndef SECURESMS_PAN_H
#define SECURESMS_PAN_H

/** SecureSMS application panic codes */
enum TSecureSMSPanics
	{
	ESecureSMSUi = 1
	// add further panics here
	};

inline void Panic(TSecureSMSPanics aReason)
	{
	_LIT(applicationName,"SecureSMS");
	User::Panic(applicationName, aReason);
	}

#endif // SECURESMS_PAN_H

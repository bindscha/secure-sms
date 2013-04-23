/*
========================================================================
 Name        : SecureSMSApplication.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for secure SMS application
========================================================================
*/
#ifndef SECURESMSAPPLICATION_H
#define SECURESMSAPPLICATION_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknapp.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const TUid KUidSecureSMSApplication = { 0xEE96475F };
// ]]] end generated region [Generated Constants]

/**
 *
 * @class	CSecureSMSApplication SecureSMSApplication.h
 * @brief	A CAknApplication-derived class is required by the S60 application 
 *          framework. It is subclassed to create the application's document 
 *          object.
 */
class CSecureSMSApplication : public CAknApplication
	{
private:
	TUid AppDllUid() const;
	CApaDocument* CreateDocumentL();
	
	};
			
#endif // SECURESMSAPPLICATION_H		

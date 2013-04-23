/*
========================================================================
 Name        : SecureSMSApplication.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of SSMS application
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated Includes]
#include "SecureSMSApplication.h"
#include "SecureSMSDocument.h"
#ifdef EKA2
#include <eikstart.h>
#endif
// ]]] end generated region [Generated Includes]

/**
 * @brief Returns the application's UID (override from CApaApplication::AppDllUid())
 * @return UID for this application (KUidSecureSMSApplication)
 */
TUid CSecureSMSApplication::AppDllUid() const
	{
	return KUidSecureSMSApplication;
	}

/**
 * @brief Creates the application's document (override from CApaApplication::CreateDocumentL())
 * @return Pointer to the created document object (CSecureSMSDocument)
 */
CApaDocument* CSecureSMSApplication::CreateDocumentL()
	{
	return CSecureSMSDocument::NewL( *this );
	}

#ifdef EKA2

/**
 *	@brief Called by the application framework to construct the application object
 *  @return The application (CSecureSMSApplication)
 */	
LOCAL_C CApaApplication* NewApplication()
	{
	return new CSecureSMSApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
 */	
GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}
	
#else 	// Series 60 2.x main DLL program code

/**
* @brief This standard export constructs the application object.
* @return The application (CSecureSMSApplication)
*/
EXPORT_C CApaApplication* NewApplication()
	{
	return new CSecureSMSApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
*/
GLDEF_C TInt E32Dll(TDllReason /*reason*/)
	{
	return KErrNone;
	}

#endif // EKA2

/*
========================================================================
 Name        : SecureSMSDocument.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of document class
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "SecureSMSDocument.h"
#include "SecureSMSAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CSecureSMSDocument::CSecureSMSDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CSecureSMSDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CSecureSMSDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CSecureSMSDocument
 */
CSecureSMSDocument* CSecureSMSDocument::NewL( CEikApplication& aApp )
	{
	CSecureSMSDocument* self = new ( ELeave ) CSecureSMSDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CSecureSMSDocument::CreateAppUiL()
	{
	return new ( ELeave ) CSecureSMSAppUi;
	}
				

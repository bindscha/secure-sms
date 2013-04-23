/*
========================================================================
 Name        : SecureSMSDocument.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for document class
========================================================================
*/
#ifndef SECURESMSDOCUMENT_H
#define SECURESMSDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CSecureSMSDocument SecureSMSDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CSecureSMSDocument : public CAknDocument
	{
public: 
	// constructor
	static CSecureSMSDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CSecureSMSDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // SECURESMSDOCUMENT_H

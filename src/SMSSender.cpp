/*
========================================================================
 Name        : SMSSender.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of SMS sender
========================================================================
*/
#include "SMSSender.h"
#include "SecurityModule.h"

// Public static constructor defined in SMSSender.h
CSMSSender* CSMSSender::NewL()
	{
	CSMSSender* self = new CSMSSender();
	self->ConstructL();
	return self;
	}

// Public virtual destructor defined in SMSSender.h
CSMSSender::~CSMSSender()
	{
	delete iSmsHandler;
	iSmsHandler = NULL;
	}

// Public function defined in SMSSender.h
TBool CSMSSender::SendL(TDesC& content, TDesC& to, TDesC& password)
	{
	TDesC& encrypted = CSecurityModule::EncryptLC(content, password);
	CGMEMessage* gme = CGMEMessage::NewL(SECURE_SMS, encrypted, CHECKSUM_ENABLED);
	CleanupStack::PushL(gme);
	TDesC& message = gme->DataL();
	
	TBool ret = iSmsHandler->SendL(to, message);
	
	CleanupStack::PopAndDestroy(gme);
	CleanupStack::PopAndDestroy();
	return ret;
	}

// Protected 2nd-phase constructor defined in SMSSender.h
void CSMSSender::ConstructL()
	{
	iSmsHandler = CSmsHandler::NewL();
	}

// Private 1st-phase constructor defined in SMSSender.h
CSMSSender::CSMSSender()
	{
	}

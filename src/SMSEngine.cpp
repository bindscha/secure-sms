/*
 ========================================================================
 Name        : SMSEngine.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of SMS engine
 ========================================================================
 */
#include "SMSEngine.h"

CSMSEngine* CSMSEngine::NewL(MEngineObserver& aObserver, CKeyExchangeContainerView *callback)
	{
	CSMSEngine* self = CSMSEngine::NewLC(aObserver, callback);
	CleanupStack::Pop(self);
	return self;
	}

CSMSEngine* CSMSEngine::NewLC(MEngineObserver& aObserver, CKeyExchangeContainerView *callback)
	{
	CSMSEngine* self = new (ELeave) CSMSEngine(aObserver, callback);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSMSEngine::CSMSEngine(MEngineObserver& aObserver, CKeyExchangeContainerView *callback) :
	CAbstractEngine(aObserver), iCallback(callback)
	{
	}

CSMSEngine::~CSMSEngine()
	{
	delete iSmsHandler;
	iSmsHandler = NULL;
	iCallback = NULL;
	}

void CSMSEngine::ConstructL()
	{
	iSmsHandler = CSmsHandler::NewL();
	}

void CSMSEngine::ConnectL()
	{
	iCallback->RunAskPhoneNbL(iPhoneNb);
	iObserver.HandleConnectedL();
	}

void CSMSEngine::DisconnectL()
	{

	}

TDesC& CSMSEngine::ContactPhoneNumberL()
	{
	return iPhoneNb;
	}

void CSMSEngine::Send(const TDesC8& aData)
	{
	TBuf<KMAX_MESSAGE_SIZE> data;
	data.Copy(aData);
	CGMEMessage* gme = CGMEMessage::NewL(KEY_EXCHANGE_SMS, data, CHECKSUM_ENABLED);
	CleanupStack::PushL(gme);
	
	TDesC& message = gme->DataL();
	iSmsHandler->SendL(iPhoneNb, message);

	CleanupStack::PopAndDestroy(gme);
	}

void CSMSEngine::RecSMSMessageL(const TDesC& aMessage)
	{
	iObserver.HandleDataReceivedL(CGMEMessage::ExtractBodyLC(aMessage));
	}

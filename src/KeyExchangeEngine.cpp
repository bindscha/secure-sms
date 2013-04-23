/*
========================================================================
 Name        : KeyExchangeEngine.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of key exchange engine
========================================================================
*/
#include "KeyExchangeEngine.h"
#include "KeyExchangeContainer.h"
#include "ContactsHandler.h"

_LIT(KConnecting, "Connecting...\n");
_LIT8(KConnecting8, "Connecting");
_LIT(KConnected, "Connected!\n");
_LIT8(KConnected8, "Connected");
_LIT(KInitA, "Initiated\n");
_LIT(KDone, "Done\n");
_LIT(KConnError, "Error!\n");
_LIT(KKey, "Key: ");

CKeyExchangeEngine* CKeyExchangeEngine::NewL(CAbstractEngine& aEngine,
		TBool aInitiateExchange, const TDesC& aPassword, CKeyExchangeContainerView& aView)
	{
	CKeyExchangeEngine* self = CKeyExchangeEngine::NewLC(aEngine, aInitiateExchange, aPassword, aView);
	CleanupStack::Pop(self);
	return self;
	}

CKeyExchangeEngine* CKeyExchangeEngine::NewLC(CAbstractEngine& aEngine,
		TBool aInitiateExchange, const TDesC& aPassword, CKeyExchangeContainerView& aView)
	{
	CKeyExchangeEngine* self = new (ELeave) CKeyExchangeEngine(aEngine, aInitiateExchange, aPassword, aView);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

void CKeyExchangeEngine::ConstructL()
	{
	iKeyExchangeModule = CKeyExchangeModule::NewL();
	}

CKeyExchangeEngine::CKeyExchangeEngine(CAbstractEngine& aEngine,
		TBool aInitiateExchange, const TDesC& aPassword, CKeyExchangeContainerView& aView) :
	iEngine(aEngine), iInitiateExchange(aInitiateExchange), iPassword(aPassword), iView(aView), iState(ENone)
	{
	}

CKeyExchangeEngine::~CKeyExchangeEngine()
	{
	delete iKeyExchangeModule;
	iKeyExchangeModule = NULL;
	}

void CKeyExchangeEngine::StartL()
	{
	AppendToLog(KConnecting());
	iState = EConnecting;
	iEngine.ConnectL();
	}

void CKeyExchangeEngine::HandleConnectedL()
	{
	if(iState == EConnecting)
		{

		AppendToLog(KConnected());

		if (iInitiateExchange)
			{
			PerformInitA();
			}
		else
			{
			PerformInitB();
			}
		
		}
	}

void CKeyExchangeEngine::HandleEngineError(TInt aError)
	{
	
	}

void CKeyExchangeEngine::HandleDataReceivedL(const TDesC& aData)
	{
	// Ensure coherence of key exchange states (i.e. I must be A if I initiated the exchange)
	if(iInitiateExchange && iState >= EAStep1 && iState <= EAStepLast)
		{
		switch(iState)
			{
			case EAStep1:
				PerformLastA(aData);
				break;
			default:
				AppendToLog(KConnError());
			}
		}
	else if(iState >= EBStep1 && iState <= EBStepLast)
		{ // If I'm not A, I must be B
		switch (iState)
			{
			case EBStep1:
				PerformLastB(aData);
				break;
			default:
				AppendToLog(KConnError());
			}
		}
	else
		{
		AppendToLog(KConnError());
		}
	}

void CKeyExchangeEngine::AppendToLog(const TDesC& aMessage)
	{
	iView.Container().AppendToLog(aMessage);
	}

void CKeyExchangeEngine::PerformInitA()
	{
	AppendToLog(KInitA());
	iState = EAStep1;
	TDesC& ret = iKeyExchangeModule->DHMethode1L(iPassword);
	TBuf8<1000> sentMsg;
	sentMsg.Copy(ret);
	iEngine.Send(sentMsg);
	}

void CKeyExchangeEngine::PerformLastA(const TDesC& aData)
	{
	iKeyExchangeModule->DHMethode3L(iPassword, aData);
	iState = EDone;
	AppendToLog(KDone());
	TBuf<100> key;
	const HBufC8* symKey = (iKeyExchangeModule->iSymetrickey2)->Alloc();
	key.Copy(*symKey);
	CContactsHandler::WriteKeyL(iEngine.ContactPhoneNumberL(), key);
	}

void CKeyExchangeEngine::PerformInitB()
	{
	iState = EBStep1;
	}

void CKeyExchangeEngine::PerformLastB(const TDesC& aData)
	{
	TDesC& ret = iKeyExchangeModule->DHMethode2L(iPassword, aData);
	iState = EDone;
	AppendToLog(KDone());
	TBuf8<1000> sentMsg;
	sentMsg.Copy(ret);
	iEngine.Send(sentMsg);
	TBuf<100> key;
	const HBufC8* symKey = (iKeyExchangeModule->iSymetrickey1)->Alloc();
	key.Copy(*symKey);
	CContactsHandler::WriteKeyL(iEngine.ContactPhoneNumberL(), key);
	}


/*
========================================================================
 Name        : KeyExchangeEngine.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for key exchange engine
========================================================================
*/
#ifndef KEYEXCHANGEENGINE_H_
#define KEYEXCHANGEENGINE_H_

#include <e32base.h>
#include "AbstractEngine.h"
#include "KeyExchangeContainerView.h"
#include "KeyExchangeModule.h"

class CKeyExchangeEngine : public CBase, public MEngineObserver
	{

public:

	static CKeyExchangeEngine* NewL(CAbstractEngine& aEngine,
			TBool aInitiateExchange, const TDesC& aPassword, CKeyExchangeContainerView& aView);
	static CKeyExchangeEngine* NewLC(CAbstractEngine& aEngine,
			TBool aInitiateExchange, const TDesC& aPassword, CKeyExchangeContainerView& aView);

	~CKeyExchangeEngine();

	void StartL();
	
	void HandleConnectedL();
	void HandleEngineError(TInt aError);
	void HandleDataReceivedL(const TDesC& aData);
	
	void PerformInitA();
	void PerformLastA(const TDesC& aData);
	
	void PerformInitB();
	void PerformLastB(const TDesC& aData);

protected:

	void ConstructL();

	CKeyExchangeEngine(CAbstractEngine& aEngine, TBool aInitiateExchange, const TDesC& aPassword, CKeyExchangeContainerView& aView);

private:
	
	void AppendToLog(const TDesC& aMessage);
	
private:

	CAbstractEngine& iEngine;
	TBool iInitiateExchange;
	
	CKeyExchangeContainerView& iView;
	
	CKeyExchangeModule* iKeyExchangeModule;
	
	const TDesC& iPassword;
	
	enum TState
		{
		ENone = 1,
		EConnecting,
		EAReady,
		EAStep1,
		EAStep2,
		EAStep3,
		EBReady,
		EBStep1,
		EBStep2,
		EBStep3,
		EABReady,
		EDone
		};

#define EAStepLast EAStep3
#define EBStepLast EBStep3
	
	TState iState;

	};

#endif /* KEYEXCHANGEENGINE_H_ */

/*
========================================================================
 Name        : AbstractEngine.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for the abstract communications engine
========================================================================
*/
#ifndef ABSTRACTENGINE_H_
#define ABSTRACTENGINE_H_

#include <e32base.h>

class MEngineObserver
	{
	
public:
	
	virtual void HandleConnectedL()=0;
	virtual void HandleEngineError(TInt aError)=0;
	virtual void HandleDataReceivedL(const TDesC& aData)=0;
	
	};

class CAbstractEngine
	{

public:
	
	static CAbstractEngine* NewL(MEngineObserver& aObserver);
	static CAbstractEngine* NewLC(MEngineObserver& aObserver);
	
	virtual ~CAbstractEngine();
	
	virtual void ConnectL();
	virtual void DisconnectL();
	
	virtual void Send(const TDesC8& aData);
	
	virtual TDesC& ContactPhoneNumberL();
	
protected:
	
	void ConstructL();

	CAbstractEngine(MEngineObserver& aObserver);
	
	MEngineObserver& iObserver;
	
private:
	
	};

#endif /* ABSTRACTENGINE_H_ */

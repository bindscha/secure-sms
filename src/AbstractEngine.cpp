/*
========================================================================
 Name        : AbstractEngine.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of abstract engine
========================================================================
*/
#include "AbstractEngine.h"

CAbstractEngine* CAbstractEngine::NewL(MEngineObserver& aObserver)
	{
	CAbstractEngine* self = CAbstractEngine::NewLC(aObserver);
	CleanupStack::Pop(self);
	return self;
	}
CAbstractEngine* CAbstractEngine::NewLC(MEngineObserver& aObserver)
	{
	CAbstractEngine* self = new (ELeave) CAbstractEngine(aObserver);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}
	
CAbstractEngine::~CAbstractEngine()
	{
	}

void CAbstractEngine::ConstructL()
	{
	}
	
CAbstractEngine::CAbstractEngine(MEngineObserver& aObserver): iObserver(aObserver)
	{
	}

void CAbstractEngine::ConnectL()
	{
	}

void CAbstractEngine::DisconnectL()
	{
	}
	
void CAbstractEngine::Send(const TDesC8& aData)
	{
	}

TDesC& CAbstractEngine::ContactPhoneNumberL()
	{
	}

/*
========================================================================
 Name        : SMSEngine.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for SMS engine
========================================================================
*/
#ifndef SMSENGINE_H_
#define SMSENGINE_H_

#include <e32base.h>
#include <aknviewappui.h>

#include "AbstractEngine.h"
#include "KeyExchangeContainerView.h"
#include "SMSReceiver.h"
#include "SMSHandler.h"

#define KMAX_PHONE_NB 20
#define KMAX_MESSAGE_SIZE 200

class CSMSEngine: public CBase, public CAbstractEngine, public MSMSRecCallBack
	{
	
public:
	
	static CSMSEngine* NewL(MEngineObserver& aObserver, CKeyExchangeContainerView *callback);
    static CSMSEngine* NewLC(MEngineObserver& aObserver, CKeyExchangeContainerView *callback);
	
    ~CSMSEngine();
    
    void ConnectL();
    void DisconnectL();
    void Send(const TDesC8& aData);
    
    void RecSMSMessageL(const TDesC& aMessage);
    
    TDesC& ContactPhoneNumberL();
	
protected:
	
	void ConstructL();
	
private:
	
	CSMSEngine(MEngineObserver& aObserver, CKeyExchangeContainerView *callback);
	
private:
	
	CSmsHandler* iSmsHandler;
	CKeyExchangeContainerView* iCallback;
	
	TBuf<KMAX_PHONE_NB> iPhoneNb;
	
	};


#endif /* BLUETOOTHENGINE_H_ */

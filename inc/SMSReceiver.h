/*
========================================================================
 Name        : SMSReceiver.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for SMS receiver
========================================================================
*/
#ifndef SMSRECEIVER_H_
#define SMSRECEIVER_H_

#include <msvstd.h>
#include <msvuids.h>
#include "msvapi.h"
#include "msvids.h"
#include "mtclreg.h"
#include "smut.h"
#include "mtclbase.h"
#include "txtrich.h"
#include "GME.h"

class MSMSRecCallBack 
{
public:
	virtual void RecSMSMessageL(const TDesC& aMessage) = 0;
};
 
	
class CSMSReceiver : public CBase, MMsvSessionObserver
    {
    
public:
	static CSMSReceiver* NewL(MSMSRecCallBack* aSSMSObserver, MSMSRecCallBack* aKeyExchangeObserver);
	~CSMSReceiver();
protected:
	CSMSReceiver(MSMSRecCallBack& aSSMSObserver, MSMSRecCallBack& aKeyExchangeObserver);
    void ConstructL(void);	
	void HandleSessionEventL(TMsvSessionEvent aEvent, TAny *aArg1, TAny *aArg2, TAny *aArg3);
private:
	void HandleEntryL(TMsvId& aEntId);
	TBool CheckIfFolderExistsL();
	TBool CreateFolderL();
private:
	MSMSRecCallBack&	iSSMSObserver;
	MSMSRecCallBack&	iKeyExchangeObserver;
	
	CMsvSession*		iSession;
	CClientMtmRegistry*	iMtmRegistry;
	CBaseMtm* 			iSmsMtm;
	
	TMsvId				iNewFolderId;

    };

#endif /* SMSRECEIVER_H_ */

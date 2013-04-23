/*
========================================================================
 Name        : BluetoothEngine.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for the Bluetooth engine
========================================================================
*/
#ifndef BLUETOOTHENGINE_H_
#define BLUETOOTHENGINE_H_

#include <e32base.h>
#include <aknviewappui.h>

#include <coecntrl.h>
#include <es_sock.h>
#include <btdevice.h>
#include <bt_sock.h>
#include <btsdp.h>
#include <btmanclient.h>

#include "AbstractEngine.h"

#include "BluetoothCommon.h"
#include "BluetoothListener.h"
#include "BluetoothConnector.h"
#include "BluetoothServiceAdvertiser.h"
#include "BluetoothDeviceDiscoverer.h"
#include "BluetoothServiceDiscoverer.h"

#include "KeyExchangeContainerView.h"

_LIT(KHostName, "Key exchange partner");

const TInt KChannel = 6;

class CBluetoothEngine: public CBase, public CAbstractEngine, public MListenerObserver, public MConnectorObserver, public MDeviceDiscoObserver, public MServiceDiscoObserver
	{
	
public:
	
	static CBluetoothEngine* NewL(MEngineObserver& aObserver, RSocketServ& aSocketServ, TBool serverMode, CKeyExchangeContainerView *callback);
    static CBluetoothEngine* NewLC(MEngineObserver& aObserver, RSocketServ& aSocketServ, TBool serverMode, CKeyExchangeContainerView *callback);
	
    ~CBluetoothEngine();
    
    void ConnectL();
    void DisconnectL();
    void Send(const TDesC8& aData);
    
    TDesC& ContactPhoneNumberL();
    
	void HandleListenerDataReceivedL(const TDesC& aData);
	void HandleListenerConnectedL();
	void HandleListenerDisconnectedL();
	
	void HandleConnectorDataReceivedL(THostName aName, const TDesC& aData);
	void HandleConnectorErrorL(THostName aName, TInt aError);
	
	void HandleDeviceDiscoveryComplete(TInt aError);    
	void DeviceDiscovered(const TDeviceData& aDevice);
	
	void HandleServiceDiscoveryCompleteL();
	void ReportServiceDiscoveryErrorL(TInt aError);
	
protected:
	
	void ConstructL();
	
private:
	
	CBluetoothEngine(MEngineObserver& aObserver, RSocketServ& aSocketServ, TBool serverMode, CKeyExchangeContainerView *callback);
	
	const TBTDevAddr& GetDeviceAddressL();
	
private:
	
	RSocketServ iSocketServ;
	TBool iServerMode;
	CKeyExchangeContainerView *iCallback;
	
	CListener *iListener;
	CConnector *iConnector;
	CServiceAdvertiser *iAdvertiser;
	CDeviceDiscoverer *iDeviceDiscoverer;
	CServiceDiscoverer *iServiceDiscoverer;
	
	TDeviceDataList iDevDataList;
	
	TBuf<20> iPhoneNb;
	
	};


#endif /* BLUETOOTHENGINE_H_ */

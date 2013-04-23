/*
========================================================================
 Name        : BluetoothEngine.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of Bluetooth engine
========================================================================
*/
#include "BluetoothEngine.h"

#include <BTExtNotifiers.h>
#include <btsdp.h>

#include <avkon.hrh>
#include <aknnotewrappers.h>

#include "KeyExchangeContainer.h"

CBluetoothEngine* CBluetoothEngine::NewL(MEngineObserver& aObserver, RSocketServ& aSocketServ, TBool serverMode, CKeyExchangeContainerView *callback)
    {
    CBluetoothEngine* self = CBluetoothEngine::NewLC(aObserver, aSocketServ, serverMode, callback);
    CleanupStack::Pop(self);
    return self;
    }

CBluetoothEngine* CBluetoothEngine::NewLC(MEngineObserver& aObserver, RSocketServ& aSocketServ, TBool serverMode, CKeyExchangeContainerView *callback)
    {
    CBluetoothEngine* self = new (ELeave) CBluetoothEngine(aObserver, aSocketServ, serverMode, callback);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CBluetoothEngine::ConstructL()
    {
    	if(iServerMode)
    		{
    		iListener = CListener::NewL(*this, iSocketServ);
    		iConnector = NULL;
    		iAdvertiser = CServiceAdvertiser::NewL();
    		iDeviceDiscoverer = NULL;
    		iServiceDiscoverer = NULL;
    		}
    	else
    		{
    		iListener = NULL;
    		iConnector = CConnector::NewL(*this, iSocketServ);
    		iAdvertiser = NULL;
    		iDeviceDiscoverer = CDeviceDiscoverer::NewL(iSocketServ, *this);
    		iServiceDiscoverer = CServiceDiscoverer::NewL(*this);
    		}
    }

CBluetoothEngine::CBluetoothEngine(MEngineObserver& aObserver,
		RSocketServ& aSocketServ, TBool serverMode,
		CKeyExchangeContainerView *callback) :
	CAbstractEngine(aObserver), iSocketServ(aSocketServ), iServerMode(
			serverMode), iCallback(callback)
	{
	}

CBluetoothEngine::~CBluetoothEngine()
    {
    if (iServerMode)
		{
		delete iListener;
		delete iAdvertiser;
		}
	else
		{
		delete iConnector;
		delete iDeviceDiscoverer;
		delete iServiceDiscoverer;
		}
	iListener = NULL;
	iConnector = NULL;
	iAdvertiser = NULL;
	iDeviceDiscoverer = NULL;
	iServiceDiscoverer = NULL;
	}

void CBluetoothEngine::ConnectL()
	{
	if(iServerMode)
		{
		TInt channel;
		iListener->StartListenerL(channel);
		iAdvertiser->StartAdvertiserL(channel);
		_LIT(KWaitServer, "Waiting for partner device connection...");
		iCallback->ExecuteWaitPartnerLD(&KWaitServer());
		}
	else
		{
		iDeviceDiscoverer->DiscoverDevicesL(&iDevDataList);
		iCallback->ExecuteWaitPartnerLD();
		}
	}

void CBluetoothEngine::DisconnectL()
	{
	}

void CBluetoothEngine::Send(const TDesC8& aData)
	{
	if(iServerMode)
		{
		iListener->SendData(aData);
		}
	else
		{
		iConnector->SendData(aData);
		}
	}

void CBluetoothEngine::HandleListenerDataReceivedL(const TDesC& aData)
	{
	iObserver.HandleDataReceivedL(aData);
	}

void CBluetoothEngine::HandleListenerConnectedL()
	{
	iCallback->RemoveWaitPartnerL();
	iObserver.HandleConnectedL();
	}

void CBluetoothEngine::HandleListenerDisconnectedL()
	{
	// TODO
	}

void CBluetoothEngine::HandleConnectorDataReceivedL(THostName aName, const TDesC& aData)
	{
	iObserver.HandleDataReceivedL(aData);
	}

void CBluetoothEngine::HandleConnectorErrorL(THostName aName, TInt aError)
	{
	// TODO
	}

void CBluetoothEngine::HandleDeviceDiscoveryComplete(TInt aError)
	{
	iServiceDiscoverer->DiscoverServicesL(&iDevDataList);
	}

void CBluetoothEngine::DeviceDiscovered(const TDeviceData& aDevice)
	{
	
	}

void CBluetoothEngine::HandleServiceDiscoveryCompleteL()
	{
	CDesC16ArraySeg* array = new (ELeave) CDesC16ArraySeg(16);
	for (TInt i = 0; i < iDevDataList.Count(); ++i)
		{
		TDeviceData dev = *(iDevDataList[i]);
		HBufC* item = HBufC::New(0x100);
		item->Des().Copy(dev.iDeviceName);
		array->AppendL(*item);
		}
	iCallback->RemoveWaitPartnerL();
	TInt selection = iCallback->RunKeyExchangeDevSelectionL(NULL, array, NULL);
	TDeviceData selectedDev = *(iDevDataList[selection]);
	TBuf<0x100> hostname;
	hostname.Copy(KHostName);

	iConnector->ConnectL(selectedDev.iDeviceName, selectedDev.iDeviceAddr, selectedDev.iDeviceServicePort);
	iObserver.HandleConnectedL();
	}

void CBluetoothEngine::ReportServiceDiscoveryErrorL(TInt aError)
	{
	
	}

const TBTDevAddr& CBluetoothEngine::GetDeviceAddressL()
	{
	RNotifier btNotifier;
	User::LeaveIfError(btNotifier.Connect());

	TBTDeviceSelectionParamsPckg selectionFilter;
	TBTDeviceResponseParamsPckg selectionResponse;

	selectionFilter().SetUUID(KBT_serviceID);

	TRequestStatus status;
	btNotifier.StartNotifierAndGetResponse(status, KDeviceSelectionNotifierUid,
			selectionFilter, selectionResponse);
	User::WaitForRequest(status);

	btNotifier.Close();

	User::LeaveIfError(status.Int());

	// use the response data ....
	//TBTDeviceName dname = selectionResponse().DeviceName();
	//TBTDeviceClass dclass = selectionResponse().DeviceClass();
	// ... etc...

	return selectionResponse().BDAddr();
	}

TDesC& CBluetoothEngine::ContactPhoneNumberL()
	{
	iCallback->RunAskPhoneNbL(iPhoneNb);
	return iPhoneNb;
	}

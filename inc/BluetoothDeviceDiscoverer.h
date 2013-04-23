/*
========================================================================
 Name        : BluetoothDeviceDiscoverer.h
 Author		 : Nokia Corporation
 Modified    : Laurent Bindschaedler
 Copyright   : Copyright (c) Nokia Corporation 2009
 Description : Header file for the Bluetooth device discoverer
========================================================================
*/
#ifndef DEVICEDISCOVERER_H
#define DEVICEDISCOVERER_H

// INCLUDES
#include <e32base.h>
#include <aknviewappui.h> 

#include <coecntrl.h>
#include <es_sock.h>
#include <btdevice.h>
#include <bt_sock.h>
#include <btsdp.h>

#include "BluetoothCommon.h"


class MDeviceDiscoObserver
{

public:
/*!
 * HandleDeviceDiscoveryComplete()
 *
 * discussion Observer interface for handling device discovery complete event.
 */ 
    virtual void HandleDeviceDiscoveryComplete(TInt aError)=0;
    
/*!
 * DeviceDiscovered()
 * 
 * discussion nofify observer that a new device was found.
 */ 
    virtual void DeviceDiscovered(const TDeviceData& aDevice)=0;
};


class CDeviceDiscoverer : public CActive
{
public:
     
/*!
 * NewL()
 * 
 * discussion Create new CDeviceDiscoverer object
 * return a pointer to the created instance of CDeviceDiscoverer
 */
    static CDeviceDiscoverer* NewL(RSocketServ& aSocketServ,
        MDeviceDiscoObserver& aObserver);
        
/*!
 * NewLC()
 * 
 */
    static CDeviceDiscoverer* NewLC(RSocketServ& aSocketServ,
        MDeviceDiscoObserver& aObserver);

/*!
 * ~CDeviceDiscoverer()
 *
 * discussion Destroy the object and release all memory objects
 */
    ~CDeviceDiscoverer();

/*!
 * DiscoverDevicesL()
 *
 * discussion Discovers remote bluetooth devices within range.
 *
 * param aDevDataList device data list where the found devices will be placed.
 */
    void DiscoverDevicesL(TDeviceDataList* aDevDataList);

/*!
 * HasDevices()
 *
 * discussion any devices discovered?
 *
 * return true if any devices were discovered.
 */
    TBool HasDevices();


#ifdef ENABLE_LIAC
/*!
 * SetLIAC()
 * 
 * discussion Set LimitedDiscoverableStatus status
 * 
 */
    void SetLIAC( TBool aState );
#endif

/*!
 * StopDiscovery()
 * 
 * discussion Stops ongoing device discovery
 * 
 */
    void StopDiscovery();

protected:

/*!
 * RunL()
 *
 * discussion Handle the active objects request completion.
 */
    void RunL();

/*!
 * DoCancel()
 *
 * discussion Cancels the outstanding request on active object.
 */
    void DoCancel();


private:

/*!
 * CDeviceDiscoverer()
 *
 * discussion Perform the first phase of two phase construction 
 *
 * param aSocketServ reference to socket server
 */
    CDeviceDiscoverer(RSocketServ& aSocketServ,
        MDeviceDiscoObserver& aObserver);

/*!
 * ConstructL()
 *
 */
    void ConstructL();

private: //data

    // socket server handle
    RSocketServ& iSocketServ;
    // observer reference
    MDeviceDiscoObserver& iObserver;
    // device data list, to be filled by resolver results
    TDeviceDataList *iDevDataList;
    // host resolver
    RHostResolver iResolver;
    TInquirySockAddr iAddr;
    TNameEntry iEntry;

#ifdef ENABLE_LIAC
    TBool iLIAC;
#endif

};

#endif

/*
========================================================================
 Name        : BluetoothServiceAdvertiser.h
 Author		 : Nokia Corporation
 Modified    : Laurent Bindschaedler
 Copyright   : Copyright (c) Nokia Corporation 2009
 Description : Header file for the Bluetooth service advertiser
========================================================================
*/
#ifndef SERVICEADVERTISER_H
#define SERVICEADVERTISER_H

// INCLUDES
#include <e32base.h>

#include <coecntrl.h>
#include <es_sock.h>
#include <btdevice.h>
#include <bt_sock.h>
#include <btsdp.h>
#include <btmanclient.h> 

#include "BluetoothCommon.h"


class CServiceAdvertiser : public CBase
{
public:
     
/*!
 * NewL()
 * 
 * discussion Create new CServiceAdvertiser object
 * return a pointer to the created instance of CServiceAdvertiser
 */
    static CServiceAdvertiser* NewL();
        
/*!
 * NewLC()
 * 
 */
    static CServiceAdvertiser* NewLC();

/*!
 * ~CDeviceDiscoverer()
 *
 * discussion Destroy the object and release all memory objects
 */
    ~CServiceAdvertiser();

/*!
 * StartAdvertiserL()
 *
 * discussion Starts the service advertiser.
 *
 * param aChannel the communication channel (port) the service will be
 * advertised on.  an entry for our advertisement will be added to service
 * discovery database.
 */
    void StartAdvertiserL(TInt /*aChannel*/);

/*!
 * StopAdvertiserL()
 *
 * discussion Stops the service advertiser.  our entry from service 
 * discovery database will be removed.
 */
    void StopAdvertiserL();

/*!
 * UpdateAvailabilityL()
 *
 * discussion Updates the availability of advertised service.  the service
 * record in service discovery database will be updated accordingly.
 *
 * param aAvailable true if the service should be set as available, 
 * false if unavailable.
 */
    void UpdateAvailabilityL(TBool /*aAvailable*/);
        
private:

/*!
 * CServiceAdvertiser()
 *
 * discussion Perform the first phase of two phase construction 
 */
    CServiceAdvertiser();

/*!
 * ConstructL()
 *
 */
    void ConstructL();

private:    // data

    // service discovery protocol session
    RSdp iSdp;
    // service discovery database (sdp)
    RSdpDatabase iSdpDB;
    // service record
    TSdpServRecordHandle iRecord;
    // service record state
    TInt iRecordState;
};

#endif


/*
========================================================================
 Name        : BluetoothServiceAdvertiser.cpp
 Author		 : Nokia Corporation
 Modified    : Laurent Bindschaedler
 Copyright   : Copyright (c) Nokia Corporation 2009
 Description : Implementation of Bluetooth service advertiser
========================================================================
*/
// INCLUDE FILES
#include <btmanclient.h>
#include "BluetoothServiceAdvertiser.h"

// see https://www.bluetooth.org/foundry/assignnumb/document/service_discovery

// service name and description for our service
_LIT(KBTServiceName, "BTpmp");
_LIT(KBTServiceDesc, "BTpmp");

CServiceAdvertiser* CServiceAdvertiser::NewL()
    {
    CServiceAdvertiser* self = CServiceAdvertiser::NewLC();
    CleanupStack::Pop(self);
    return self;
    }


CServiceAdvertiser* CServiceAdvertiser::NewLC()
    {
    CServiceAdvertiser* self = new (ELeave) CServiceAdvertiser();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }


void CServiceAdvertiser::ConstructL()
    {
    }


// ----------------------------------------------------------------------------
// CServiceAdvertiser::CServiceAdvertiser()
//
// constructor
// ----------------------------------------------------------------------------
CServiceAdvertiser::CServiceAdvertiser()
    {
    }


// ----------------------------------------------------------------------------
// CServiceAdvertiser::~CServiceAdvertiser()
//
// destructor
// ----------------------------------------------------------------------------
CServiceAdvertiser::~CServiceAdvertiser()
    {
    TRAPD(err, StopAdvertiserL());
    }



// ----------------------------------------------------------------------------
// CServiceAdvertiser::StartAdvertiserL(TInt aChannel)
//
// start service advertiser on given channel.  an entry to service discovery
// database will be entered describing our advertised service.
// ----------------------------------------------------------------------------
void CServiceAdvertiser::StartAdvertiserL(TInt aChannel)
    {
    // open sdp session
    User::LeaveIfError(iSdp.Connect());
    // open sdp database session
    User::LeaveIfError(iSdpDB.Open(iSdp));
    // create a record of the correct service class
    TUUID serviceUUID(KBT_serviceID);
    iSdpDB.CreateServiceRecordL(serviceUUID, iRecord);

    // add a protocol to the record
    CSdpAttrValueDES* protocolDescriptorList = CSdpAttrValueDES::NewDESL(NULL);
    CleanupStack::PushL(protocolDescriptorList);

    TBuf8<1> channel;
    channel.Append((TChar)aChannel);
    // create protocol list for our service
    protocolDescriptorList
    ->StartListL()   //  list of protocols required for this method
        ->BuildDESL()
        ->StartListL()
            ->BuildUUIDL(KL2CAP)
        ->EndListL()

        ->BuildDESL()
        ->StartListL()
            ->BuildUUIDL(KRFCOMM)
            ->BuildUintL(channel)
        ->EndListL()
    ->EndListL();

    // set protocol list to the record
    iSdpDB.UpdateAttributeL(iRecord, KSdpAttrIdProtocolDescriptorList,
        *protocolDescriptorList);
    CleanupStack::PopAndDestroy(protocolDescriptorList);

    // add a name to the record
    iSdpDB.UpdateAttributeL(iRecord,
                                KSdpAttrIdBasePrimaryLanguage +
                                    KSdpAttrIdOffsetServiceName,
                                KBTServiceName);

    // add a description to the record
    iSdpDB.UpdateAttributeL(iRecord,
                                KSdpAttrIdBasePrimaryLanguage +
                                    KSdpAttrIdOffsetServiceDescription,
                                KBTServiceDesc);

    // set service available
    UpdateAvailabilityL(ETrue);
    }


// ----------------------------------------------------------------------------
// CServiceAdvertiser::StopAdvertiserL()
//
// stop service advertiser.  delete service record from service discovery
// database to stop advertising.
// ----------------------------------------------------------------------------
void CServiceAdvertiser::StopAdvertiserL()
    {
    if ( iRecord!=0 )
        {
        // delete out record from service discovery database
        iSdpDB.DeleteRecordL(iRecord);
        // close sdp and sdp db sessions
        iSdpDB.Close();
        iSdp.Close();
        iRecord=0;
        }
    }


// ----------------------------------------------------------------------------
// CServiceAdvertiser::UpdateAvailability(TBool aAvailable)
//
// set availability of our advertised service.  the service record on the
// service discovery database will be updated accordingly.
// ----------------------------------------------------------------------------
void CServiceAdvertiser::UpdateAvailabilityL(TBool aAvailable)
    {
    TInt state = aAvailable ? 0xFF : 0x00;
    // set availability
    iSdpDB.UpdateAttributeL(iRecord, KSdpAttrIdServiceAvailability, state);
    // mark record changed
    iSdpDB.UpdateAttributeL(iRecord, KSdpAttrIdServiceRecordState,
        ++iRecordState);
    }


/*
========================================================================
 Name        : BluetoothConnector.h
 Author		 : Nokia Corporation
 Modified    : Laurent Bindschaedler
 Copyright   : Copyright (c) Nokia Corporation 2009
 Description : Header file for the Bluetooth connector (client)
========================================================================
*/
#ifndef CONNECTOR_H
#define CONNECTOR_H

// INCLUDES
#include <e32base.h>

#include <es_sock.h>
#include <btdevice.h>
#include <bt_sock.h>


class MConnectorObserver
{

public:
/*!
 * HandleConnectorDataReceivedL()
 *
 * discussion Observer interface for handling connector data reception event.
 */
    virtual void HandleConnectorDataReceivedL(THostName aName, const TDesC& aData)=0;
    virtual void HandleConnectorErrorL(THostName aName, TInt aError)=0;
};


class CConnector : public CActive
{
public:

/*!
 * NewL()
 *
 * discussion Create new CConnector object
 * return a pointer to the created instance of CConnector
 */
    static CConnector* NewL(MConnectorObserver& aObserver,
                            RSocketServ& aSocketServ);

/*!
 * NewLC()
 *
 */
    static CConnector* NewLC(MConnectorObserver& aObserver,
                             RSocketServ& aSocketServ);

/*!
 * ~CConnector()
 *
 * discussion Destroy the object and release all memory objects
 */
    ~CConnector();

/*!
 * ConnectL()
 *
 * discussion Creates a connection to given remote address on given port.
 *
 * param aName the name of the slave to connect to.
 * param aAddr the address of the slave to connect to.
 * param aPort the port on slave to connect to.
 *
 * return the status of connection attempt
 */
    TRequestStatus ConnectL(THostName aName, TBTDevAddr aAddr, TInt aPort);

/*!
 * Disconnect()
 *
 * discussion Disconnects connector from slave.
 */
    void Disconnect();

/*!
 * SendDataL()
 *
 * discussion Sends given data to slave.
 *
 * param aData the message to send to slave.
 */
    void SendData(const TDesC8& /*aData*/);

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

    TInt RunError(TInt aError);
    
private:

/*!
 * CConnector()
 *
 * discussion Perform the first phase of two phase construction
 *
 * param aObserver reference to observer handling the connector events
 * param aSocketServ reference to socket server
 */
    CConnector(MConnectorObserver& aObserver, RSocketServ& aSocketServ);

/*!
 * ConstructL()
 *
 */
    void ConstructL();

/*!
 * HandleConnectedDataReceivedL()
 *
 * discussion Handles the data received from a slave.  the handling request
 * will be passed onto handling observer.
 *
 * param aName the name of the slave that sent the data.
 * param aData the data received.
 */
    void HandleConnectorDataReceivedL(THostName aName, const TDesC& aData);

/*!
 * WaitAndReceiveL()
 *
 * discussion Wait for and receive data from slave.
 */
    void WaitAndReceive();

public: // data

    // name of the device connector connects
    THostName iName;
    // address of the device connector connects
    TBTDevAddr iAddr;
    // port of the device connector connects
    TInt iPort;
    // connecting socket
    RSocket iSock;
    // buffer holding received data
    TBuf8<40> iBuffer;
    // length of received data
    TSockXfrLength iLen;
    // reference to observer
    MConnectorObserver& iObserver;
    // socket server handle
    RSocketServ& iSocketServ;
    // the state of the connector
    enum TState
        {
        ENone = 1,
        EConnecting,
        EWaiting,
        ESending
        };

    TState iState;
};

#endif

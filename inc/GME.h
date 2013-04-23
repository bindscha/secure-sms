/*
========================================================================
 Name        : GME.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for GME module
========================================================================
*/
#ifndef GME_H_
#define GME_H_
// Include basic libraries
#include <e32def.h>
#include <e32std.h>
#include <e32base.h>
// Litteral prefix identifying GME SMSs
_LIT(KPrefix,"#?");

_LIT(KGMEFolderName, "GMEFolder");

// Type definitions
typedef TUint8 TFlag;
typedef TUint16 TCheckSum;
typedef TUint16 TOffset;

typedef enum
	{

	STANDARD_SMS = 1, SECURE_SMS = 2, KEY_EXCHANGE_SMS = 4, COMPRESSED_SMS = 8

	} TProtocolType;

typedef enum
	{

	CHECKSUM_ENABLED, CHECKSUM_DISABLED

	} TCheckSumStatus;

// Forward reference
class CMessageData;

// Forward declaration
class CGMESMS;

/**
 * This class corresponds to a GME message.
 * CGMEMessage is immutable.
 */
class CGMEMessage : public CBase
	{

public:

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a new CGMEMessage.
	 * @param aProtocol the inner protocol type
	 * @param aData the message data
	 * @param aCheckSumStatus whether checksum should be added
	 * (defaults to CHECKSUM_ENABLED)
	 * @return a pointer to the CGMEMessage created
	 */
	static CGMEMessage* NewL(const TProtocolType aProtocol, TDesC& aData,
			const TCheckSumStatus aCheckSumStatus = CHECKSUM_ENABLED);

	/**
	 * IsGME.
	 * Checks whether the message is a GME Message
	 * @param aMessage the message to check
	 * @return ETrue if the message is a GME Message, EFalse otherwise
	 */
	static TBool IsGME(const TDesC& aMessage);

	/**
	 * IsValidGME.
	 * Checks whether the message is a valid GME Message
	 * @param aMessage the message to check
	 * @return ETrue if the message is a valid GME Message, EFalse otherwise
	 */
	static TBool IsValidGME(const TDesC& aMessage);

	static TProtocolType ProtocolType(const TDesC& aMessage);
	
	/**
	 * ExtractBody.
	 * Decapsulates the message.
	 * @param aMessage the message to decapsulate
	 * @return ETrue if the message is a GME Message, EFalse otherwise
	 */
	static TDesC& ExtractBodyLC(const TDesC& aMessage);

	/**
	 * ~CGMEMessage.
	 * Virtual Destructor.
	 */
	virtual ~CGMEMessage();

	/**
	 * DataL.
	 * Returns SMS packets with the encapsulated data.
	 * @return a pointer to the CGMESMS object created
	 */
	TDesC& DataL();

protected:

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 * Perform the second phase construction of a CGMEMessage object.
	 * @param aData the message data
	 */
	void ConstructL(TDesC& aData);

private:

	// Some constants
	const static TFlag CHECKSUMPRESENT = 0x80;
	const static TFlag OFFSETPRESENT = 0x40;

	const static TFlag URGENT = 0x01;

	// Class members
	const TProtocolType iProtocol;
	const TCheckSumStatus iCheckSumStatus;

	HBufC* iGMEData;
	TCheckSum iCheckSum;
	TFlag iFlags;

	/**
	 * CGMEMessage.
	 * 1st phase constructor.
	 * Perform the first phase construction of a CGMEMessage object.
	 * @param aProtocol the inner protocol type
	 * @param aCheckSumStatus whether checksum should be added
	 */
	CGMEMessage(const TProtocolType aProtocol,
			const TCheckSumStatus aCheckSumStatus);

	};

/**
 * This class corresponds to a set of GME SMS encapsulations.
 * CGMESMS is immutable.
 */
class CGMESMS : public CBase
	{

public:

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a new CGMESMS.
	 * @param aCount the number of SMS messages
	 * @param aData a pointer to the first message data
	 * @return a pointer to the CGMESMS created
	 */
	static CGMESMS* NewL(const TUint8 aCount, TDesC& aData);

	/**
	 * ~CGMESMS.
	 * Virtual Destructor.
	 */
	virtual ~CGMESMS();

	/**
	 * Count.
	 * Returns the number of SMS messages.
	 * @return an unsigned integer representing the number of SMS messages
	 */
	const TUint8 Count();

	/**
	 * Data.
	 * Returns the message data.
	 * @return a pointer to CMessageData objects representing the message data
	 */
	TDesC& Data();

protected:

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 * Perform the second phase construction of a CGMESMS object.
	 */
	void ConstructL();

private:

	// Class members
	const TUint8 iCount;
	TDesC& iData;
	/**
	 * CGMESMS.
	 * 1st phase constructor.
	 * Perform the first phase construction of a CGMESMS object.
	 * @param aCount the number of SMS messages
	 * @param aData a pointer to the first message data
	 */
	CGMESMS(const TUint8 aCount, TDesC& aData);

	};

#endif

/*
========================================================================
 Name        : GME.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of GME module
========================================================================
*/
#include <cmessagedata.h>
#include <txtrich.h>

#include "GME.h"

// CGMEMessage implementation

// Public static constructor defined in GME.h
CGMEMessage* CGMEMessage::NewL(const TProtocolType aProtocol, TDesC& aData,
		const TCheckSumStatus aCheckSumStatus)
	{
	CGMEMessage* self = new (ELeave) CGMEMessage(aProtocol, aCheckSumStatus);
	self->ConstructL(aData);
	return self;
	}

// Public virtual destructor defined in GME.h
CGMEMessage::~CGMEMessage()
	{
	delete iGMEData;
	iGMEData = NULL;
	}

// Public const function defined in GME.h
TDesC& CGMEMessage::DataL()
	{
	return *iGMEData;
	}

// Protected 2nd-phase constructor defined in GME.h
void CGMEMessage::ConstructL(TDesC& aData)
	{
	TInt addedHeaderLength = 1;
	// Calculate checksum if needed
	if (iCheckSumStatus == CHECKSUM_ENABLED)
		{
		++addedHeaderLength;
		for (TInt i = 0; i < aData.Length(); ++i)
			{
			iCheckSum ^= aData[i];
			}
		// Special case: descriptors don't like \0
		if (iCheckSum == 0)
			iCheckSum = 0xFFFF;
		// Set C flag
		iFlags |= 0x80;
		}

	// Prepare message content
	HBufC* prefix = KPrefix().Alloc();
	HBufC* data = aData.Alloc();
	HBufC* message = HBufC::New(prefix->Des().Length()
			+ addedHeaderLength + data->Des().Length());
	TUint16 protocolAndFlags = (iProtocol << 8) | iFlags;
	
	// Fill up message
	message->Des().Append(*prefix);
	message->Des().Append(protocolAndFlags);
	if (iCheckSumStatus == CHECKSUM_ENABLED)
		message->Des().Append(TChar(iCheckSum));
	message->Des().Append(*data);
	
	// Store message in class variable
	iGMEData = message;
	
	// Cleanup
	delete prefix;
	delete data;
	}

TBool CGMEMessage::IsGME(const TDesC& aMessage)
	{
	return aMessage.Mid(0, 2) == KPrefix;
	}

TBool CGMEMessage::IsValidGME(const TDesC& aMessage)
	{
	if (IsGME(aMessage))
		{
		if (aMessage[2] & 0x80)
			{
			TCheckSum checkSum = 0;
			TPtrC data = aMessage.Right(aMessage.Length() - 4);
			for (TInt i = 0; i < data.Length(); ++i)
				{
				checkSum ^= data[i];
				}
			if (checkSum == 0)
				checkSum = 0xFFFF;
			if(aMessage[3] == checkSum)
				return ETrue;
			}
		}
	return EFalse;
	}

TProtocolType CGMEMessage::ProtocolType(const TDesC& aMessage)
	{
	if(IsGME(aMessage))
		{
		TInt type = aMessage[2] >> 8;
		switch(type)
			{
			case 1:
				return STANDARD_SMS;
			case 2:
				return SECURE_SMS;
			case 4:
				return KEY_EXCHANGE_SMS;
			case 8:
				return COMPRESSED_SMS;
			default:
				return STANDARD_SMS;
			}
		}
	return STANDARD_SMS;
	}

TDesC& CGMEMessage::ExtractBodyLC(const TDesC& aMessage)
	{
	HBufC* ret = NULL;
	if (IsGME(aMessage))
			{
			if (aMessage[2] & 0x80)
				{
				ret = aMessage.Right(aMessage.Length() - 4).Alloc();
				}
			else
				{
				ret = (aMessage.Right(aMessage.Length() - 3).Alloc());
				}
			}
	else 
		{
		User::Leave(-1);
		}
	CleanupStack::PushL(ret);
	return *ret;
	}

// Private 1st-phase constructor defined in GME.h
CGMEMessage::CGMEMessage(const TProtocolType aProtocol,
		const TCheckSumStatus aCheckSumStatus) :
	iProtocol(aProtocol), iCheckSumStatus(aCheckSumStatus), iCheckSum(0),
			iFlags(0)
	{
	}

// CGMESMS class implementation

// Public static constructor defined in GME.h
CGMESMS* CGMESMS::NewL(const TUint8 aCount, TDesC& aData)
	{
	CGMESMS* self = new CGMESMS(aCount, aData);
	self->ConstructL();
	return self;
	}

// Public virtual destructor defined in GME.h
CGMESMS::~CGMESMS()
	{
	}

// Public const function defined in GME.h
const TUint8 CGMESMS::Count()
	{
	return iCount;
	}

// Public const function defined in GME.h
TDesC& CGMESMS::Data()
	{
	return iData;
	}

// Protected 2nd-phase constructor defined in GME.h
void CGMESMS::ConstructL()
	{
	}

// Private 1st-phase constructor defined in GME.h
CGMESMS::CGMESMS(const TUint8 aCount, TDesC& aData) :
	iCount(aCount), iData(aData)
	{
	}

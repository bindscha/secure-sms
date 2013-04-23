/*
 ========================================================================
 Name        : KeyExchangeModule.cpp
 Author      : Marc Bailly
 Author		 : Laurent Bindschaedler
 Copyright   : Copyright (c) Marc Bailly 2009
 Description : 
 ========================================================================
 */
#include "cntdef.hrh"
#include "KeyExchangeModule.h"
#include "cntitem.h"
#include "cntdb.h"
#include "cntdef.h"
#include "cntfield.h"
#include "cntfldst.h"

#define PRIME_NB 1500450271 

CKeyExchangeModule* CKeyExchangeModule::NewL()
	{
	CKeyExchangeModule* self = new CKeyExchangeModule();
	self->ConstructL();
	return self;
	}
// Public virtual destructor
CKeyExchangeModule::~CKeyExchangeModule()
	{
	delete iKeyPair;
	delete iSymetrickey1;
	delete iSymetrickey2;
	}
void CKeyExchangeModule::ConstructL()
	{
	}

CKeyExchangeModule::CKeyExchangeModule()
	{

	}

TDesC& CKeyExchangeModule::DHMethode1L(const TDesC& pass)
	{


	RInteger g = RInteger::NewL(5);
	RInteger n = RInteger::NewL(PRIME_NB);

	CDHKeyPair* keyPair = CDHKeyPair::NewL(n, g);
	const CDHPublicKey &iPuKey = keyPair->PublicKey();
	RInteger x = RInteger::NewL(iPuKey.X());
	iKeyPair = keyPair;
	//delete keyPair;

	TBuf8<500> tbuf;
	TInt intX = x.ConvertToLongL();

	tbuf.AppendNum(intX);
	TBuf8<50> sign;
	sign.Append(pass);
	sign.AppendNum(intX);

	//Create a Signature
	TBuf8<20> hash;
	CSHA1* sha1 = CSHA1::NewL();
	sha1->Update(sign);
	hash.Copy(sha1->Final());
	delete sha1;
	tbuf.Append(hash);

	TBuf<500> signedText;
	signedText.Copy(tbuf);

	HBufC* cipher = signedText.Alloc();
	//CleanupStack::PushL(cipher);
	return *cipher;
	}

//THis methode take a message as input look at the memory to take it own key
void CKeyExchangeModule::DHMethode3L(const TDesC& pass, const TDesC& text)
	{

	//extract the X from message
	TBuf8<100> message;
	message.Copy(text);
	TInt l2 = text.Length();
	TInt intX;

	//----convert TBuf to TInt
	TLex lex(text.Left(l2 - 20));
	lex.Val(intX);
	//----end of conversio
	TBuf8<50> sign;
	sign.Append(pass);
	sign.AppendNum(intX);

	//Create a Signature
	TBuf8<20> hash;
	CSHA1* sha1 = CSHA1::NewL();
	sha1->Update(sign);
	hash.Copy(sha1->Final());
	delete sha1;

	if (!(hash.Compare(message.Right(20))))
		{
		
		RInteger g = RInteger::NewL(5);
		RInteger n = RInteger::NewL(PRIME_NB);
		//take the publick key from memory
		CDHKeyPair* ownkeyPair = iKeyPair;
		const CDHPrivateKey &iPrivKey = ownkeyPair->PrivateKey();
		const CDHPublicKey &iPubKey = ownkeyPair->PublicKey();
		
		RInteger x = RInteger::NewL(intX);

		//Create friends public key
		const CDHPublicKey* ifriendPuKey = CDHPublicKey::NewL(n, g, x);
		CDH* cd = CDH::NewL(iPrivKey);

		//Key to store
		const HBufC8* symetrickey = cd->AgreeL(*ifriendPuKey);
		iSymetrickey2 = symetrickey;
		//delete ownkeyPair,symetrickey,cd;

		}

	}

TDesC& CKeyExchangeModule::DHMethode2L(const TDesC& pass, const TDesC& text)
	{

	//extract the X from message
	TBuf8<100> message;
	message.Copy(text);
	TInt l2 = text.Length();
	TInt intX;

	//----convert TBuf to TInt
	TLex lex(text.Left(l2 - 20));
	lex.Val(intX);
	//----end of conversio
	TBuf8<50> sign;
	sign.Append(pass);
	sign.AppendNum(intX);

	//Create a Signature
	TBuf8<20> hash;
	CSHA1* sha1 = CSHA1::NewL();
	sha1->Update(sign);
	hash.Copy(sha1->Final());
	delete sha1;

	if (!(hash.Compare(message.Right(20))))
		{
		TBuf<500> signedText;
		//take g=5
		RInteger g = RInteger::NewL(5);
		RInteger n = RInteger::NewL(PRIME_NB);

		//Generate a key Pair
		CDHKeyPair* ownkeyPair = CDHKeyPair::NewL(n, g);
		const CDHPrivateKey &iPrivKey = ownkeyPair->PrivateKey();
		const CDHPublicKey &iPubKey = ownkeyPair->PublicKey();
		
		//extract the X avle to compute the publick key

		RInteger x = RInteger::NewL(intX);

		//Create friends public key
		const CDHPublicKey* ifriendPuKey = CDHPublicKey::NewL(n, g, x);
		CDH* cd = CDH::NewL(iPrivKey);
		//Key to store
		const HBufC8* symetrickey = cd->AgreeL(*ifriendPuKey);
		iSymetrickey1 = symetrickey;
		//Create message to send 
		RInteger xToSend = RInteger::NewL(iPubKey.X());
		TInt intXtosend = xToSend.ConvertToLongL();
		TBuf8<500> tbuf;
		tbuf.AppendNum(intXtosend);
		TBuf8<50> sign;
		sign.Append(pass);
		sign.AppendNum(intXtosend);

		//Create a Signature
		TBuf8<20> hash;
		CSHA1* sha1 = CSHA1::NewL();
		sha1->Update(sign);
		hash.Copy(sha1->Final());
		delete sha1;
		tbuf.Append(hash);

		signedText.Copy(tbuf);

		//delete ownkeyPair,ifriendPuKey, symetrickey,cd;
		HBufC* cipher = signedText.Alloc();
		//CleanupStack::PushL(cipher);
		return *cipher;
		}
	else
		{
		TBuf<500> signedText;
		_LIT(error,"Error");
		signedText.Append(error);
		HBufC* cipher = signedText.Alloc();
		//CleanupStack::PushL(cipher);
		return *cipher;
		}
	}


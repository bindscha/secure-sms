/*
 ========================================================================
 Name        : SecurityModule.cpp
 Author      : Marc Bailly
 Author		 : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of security module
 ========================================================================
 */
#include "SecurityModule.h"

TDesC& CSecurityModule::EncryptLC(TDesC& text, TDesC& password)
	{

	//create a random value
	//ATTENTION QUAND LE CHIFFE EST PLUS PETIT QUE 10 BYTES ERREUR!!!!!!!
	TUint32 num = Math::Random();
	TBuf8<50> str;

	str.AppendNum(num);
	TBuf8<20> hashrand;
	CSHA1* sha1rand = CSHA1::NewL();
	sha1rand->Update(str);
	hashrand.Copy(sha1rand->Final());
	delete sha1rand;

	//Concat RV and password
	TBuf8<50> aeskey;
	aeskey.Copy(password);
	aeskey.Append(hashrand.Right(10));

	//Create a Hash and compute hash of the RV and Pass
	TBuf8<20> hash;
	CSHA1* sha1 = CSHA1::NewL();
	sha1->Update(aeskey);
	hash.Copy(sha1->Final());
	delete sha1;

	//Final key 16 bytes of the Hashed value
	TBuf8<16> aeskey1;
	aeskey1.Append(hash.Left(aeskey1.MaxLength()));

	//Create Buffer fo all the message
	TBuf8<150> indata, encdata;
	indata.Copy(text);

	// The key length must be either KAESKeySize128 (=16), KAESKeySize192 (=24) or KAESKeySize256 (=32) bytes. 

	CAESEncryptor* iTrans = CAESEncryptor::NewL(aeskey1);
	TInt KAESBlockSize = iTrans->BlockSize();

	//delete iTrans;
	CPaddingPKCS7* pad = CPaddingPKCS7::NewL(KAESBlockSize);
	//delete pad;
	CBufferedTransformation* iBfrd = CBufferedEncryptor::NewLC(iTrans, pad);
	iBfrd->ProcessFinalL(indata, encdata);
	CleanupStack::PopAndDestroy(iBfrd);

	//Create the complete message to send
	TBuf8<150> mess;
	mess.Append(hashrand.Right(10));
	mess.Append(encdata);

	// Added by Laurent
	TBuf<150> message;
	message.Copy(mess);

	HBufC* message2 = message.Alloc();
	CleanupStack::PushL(message2);
	return *message2;
	//Fin de la méthode pour le cryptage
	}

TDesC& CSecurityModule::DecryptLC(TDesC& text, TDesC& password)
	{
	//Début de la méthode d encryption
	TBuf<50> str;
	str.Append(text.Left((TInt) 10));

	//Concat RV and password
	TBuf8<50> aeskey;
	aeskey.Copy(password);
	aeskey.Append(str);
	//Create a Hash and compute hash of the RV and Pass
	TBuf8<20> hash;
	CSHA1* sha1 = CSHA1::NewL();
	sha1->Update(aeskey);
	hash.Copy(sha1->Final());
	delete sha1;
	//Final key 16 bytes of the Hashed value
	TBuf8<16> aeskey1;
	aeskey1.Append(hash.Left(aeskey1.MaxLength()));

	//Create Buffer fo all the message
	TBuf8<150> encdata, decdata;
	encdata.Copy(text.Right(text.Length() - str.Length()));

	// The key length must be either KAESKeySize128 (=16), KAESKeySize192 (=24) or KAESKeySize256 (=32) bytes. 
	CAESDecryptor* iDec = CAESDecryptor::NewL(aeskey1);
	TInt KAESBlockSize = iDec->BlockSize();
	CPaddingPKCS7* pad2 = CPaddingPKCS7::NewL(KAESBlockSize);
	CBufferedTransformation* iDecbuf = CBufferedDecryptor::NewLC(iDec, pad2);
	iDecbuf->ProcessFinalL(encdata, decdata);
	//crée le message complet
	CleanupStack::PopAndDestroy(iDecbuf);
	TBuf<150> message;
	message.Copy(decdata);

	HBufC* message2 = message.Alloc();
	CleanupStack::PushL(message2);
	return *message2;
	//Fin de la méthode pour le decryptage
	}


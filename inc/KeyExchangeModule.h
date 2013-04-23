/*
 ========================================================================
 Name        : KeyExchangeModule.cpp
 Author      : Marc Bailly
 Author		 : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for key exchange module
 ========================================================================
 */

#ifndef KEYEXCHANGEMODULE_H_
#define KEYEXCHANGEMODULE_H_

// Include basic libraries
#include <e32def.h>
#include <e32std.h>
#include <e32base.h>

#include <e32math.h>
#include <cryptosymmetric.h>

#include <cryptoasymmetric.h>

#include <cryptopbe.h>
#include <hash.h>
#include <cryptopanic.h>

#include <cntdef.h>
#include <cntdb.h>

class CKeyExchangeModule : public CBase
	{

public:
	const HBufC8* iSymetrickey1;
	const HBufC8* iSymetrickey2;
	/**
		 * NewL.
		 * Two-phased constructor.
		 * Create a new CKeyExchangeModule.
		 * @return a pointer to the CKeyExchangeModule created
		  */
	static CKeyExchangeModule* NewL();
	TDesC& DHMethode1L(const TDesC& pass);
	TDesC& DHMethode2L(const TDesC& pass, const TDesC& text);
	void DHMethode3L(const TDesC& pass, const TDesC& text);

	/**
		 * ~CKeyExchangeModule.
		 * Virtual Destructor.
		*/ 
		virtual ~CKeyExchangeModule();
		
protected:

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 * Perform the second phase construction of a CKeyExchangeModule object.
	*/
	void ConstructL();
	
private:

	// Class members
	CDHKeyPair* iKeyPair; 
	
	/**
	 * CSecurityModule.
	 * 1st phase constructor.
	 * Perform the first phase construction of a CSecurityModule object.
	*/
	CKeyExchangeModule();
 
	};

#endif /* KEYEXCHANGEMODULE_H_ */




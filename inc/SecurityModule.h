/*
 ========================================================================
 Name        : SecurityModule.h
 Author		 : Marc Bailly
 Author		 : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for security module
 ========================================================================
 */

#ifndef SECURITYMODULE_H_
#define SECURITYMODULE_H_

// Include basic libraries
#include <e32def.h>
#include <e32std.h>
#include <e32base.h>

#include <e32math.h>
#include <cryptosymmetric.h>
#include <cryptopbe.h>
#include <hash.h>
#include <cryptopanic.h>

class CSecurityModule : public CBase
	{

public:
	static TDesC& EncryptLC(TDesC& text, TDesC& password);

	static TDesC& DecryptLC(TDesC& text, TDesC& password);

	};

#endif /* SECURITYMODULE_H_ */

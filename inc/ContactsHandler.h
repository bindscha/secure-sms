/*
 ========================================================================
 Name        : ContactsHandler.h
 Author		 : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for contacts handler
 ========================================================================
 */

#ifndef CONTACTSHANDLER_H_
#define CONTACTSHANDLER_H_

// Include basic libraries
#include <e32def.h>
#include <e32std.h>
#include <e32base.h>

#include <cntdb.h>
#include <cntitem.h>
#include <cntfield.h>
#include <cntdef.h>
#include <cntfldst.h>

#define MAX_KEY_LENGTH 50

class CContactsHandler : public CBase
	{

public:
	static TDesC& ReadKeyLC(TDesC& phone);

	static TBool WriteKeyL(TDesC& phone, TDesC& key);

	};

#endif /* CONTACTSHANDLER_H__ */

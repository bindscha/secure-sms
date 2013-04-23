/*
========================================================================
 Name        : SMSSender.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for SMS sender
========================================================================
*/
#ifndef SMSSENDER_H_
#define SMSSENDER_H_

// Include basic libraries
#include <e32def.h>
#include <e32std.h>
#include <e32base.h>

// Include libraries needed to provide functionalities
#include <sendui.h>
#include <SendUiConsts.h>
#include <cmessagedata.h>
#include <txtrich.h>
#include "GME.h"
#include "SMSHandler.h"

class CSMSSender : public CBase
	{

public:

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a new CSMSSender.
	 * @return a pointer to the CSMSSender created
	 */
	static CSMSSender* NewL();

	/**
	 * ~CSMSSender.
	 * Virtual Destructor.
	 */
	virtual ~CSMSSender();

	/**
	 * SendL.
	 * Sends a SMS to the recipient.
	 * @param content the content of the SMS
	 * @param to the recipient of the message
	 */
	TBool SendL(TDesC& content, TDesC& to, TDesC& password);

protected:

	/**
	 * ConstructL.
	 * 2nd phase constructor.
	 * Perform the second phase construction of a CSMSSender object.
	 */
	void ConstructL();

private:
	
	/**
	 * CSMSSender.
	 * 1st phase constructor.
	 * Perform the first phase construction of an CSMSSender object.
	 */
	CSMSSender();

	CSmsHandler* iSmsHandler;
	
	};


#endif /* SMSSENDER_H_ */

/*
========================================================================
 Name        : ReadMessageContainer.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for read message container
========================================================================
*/
#ifndef READMESSAGECONTAINER_H
#define READMESSAGECONTAINER_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
// ]]] end generated region [Generated Includes]

#include <msvstd.h>
#include <msvuids.h>
#include <msvapi.h>
#include "msvids.h"
#include "mtclreg.h"
#include "smut.h"
#include "mtclbase.h"
#include "txtrich.h"
#include "GME.h"
#include "SecurityModule.h"

const TInt KMaxPasswordLength = 16;

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CEikRichTextEditor;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Container class for ReadMessageContainer
 * 
 * @class	CReadMessageContainer ReadMessageContainer.h
 */
class CReadMessageContainer : public CCoeControl, MMsvSessionObserver
	{
public:
	// constructors and destructor
	CReadMessageContainer();
	static CReadMessageContainer* NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver,
		TInt aMessageId );
	static CReadMessageContainer* NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver,
		TInt aMessageId );
	void ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver,
		TInt aMessageId );
	virtual ~CReadMessageContainer();
	void HandleSessionEventL(TMsvSessionEvent /*aEvent*/, TAny */*aArg1*/, TAny */*aArg2*/, TAny */*aArg3*/) {}

public:
	TInt GetMessageId() { return iMessageId; }
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl( TInt aIndex ) const;
	TKeyResponse OfferKeyEventL( 
			const TKeyEvent& aKeyEvent, 
			TEventCode aType );
	void HandleResourceChange( TInt aType );
	
protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;

private:
	TBool ShowPasswordDialogL(TDes& aPassword);
	void InitializeControlsL();
	void LayoutControls();
	CCoeControl* iFocusControl;
	MEikCommandObserver* iCommandObserver;
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Type Declarations]
public: 
	// ]]] end generated region [Generated Type Declarations]
	TInt GetNumMessages();
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CEikRichTextEditor* iMessage;
	CEikRichTextEditor* iSender;
	CEikRichTextEditor* iDate;
	// ]]] end generated region [Generated Instance Variables]
	TInt iMessageId;
	
	CMsvSession* iSession;
	CClientMtmRegistry* iMtmRegistry;
	CBaseMtm* iSmsMtm;
	
	TMsvId iNewFolderId;
	
	HBufC* iPassword;
	
	// [[[ begin [Overridden Methods]
protected: 
	// ]]] end [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
protected: 
	void SetMessageFormattingL();
	void SetSenderFormattingL();
	void SetDateFormattingL();
	// ]]] end [User Handlers]
	TBool CheckIfFolderExistsL();
	TBool CreateFolderL();
	void SetMessage();
	void Fill();
	TDesC& GetSenderPhoneLC();
	
public: 
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]
		EMessage,
		ESender,
		EDate,
		
		// ]]] end generated region [Generated Contents]
		
		// add any user-defined entries here...
		
		ELastControl
		};
	};
				
#endif // READMESSAGECONTAINER_H

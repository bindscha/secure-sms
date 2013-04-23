/*
========================================================================
 Name        : KeyExchangeContainer.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2008
 Description : Header file for key exchange container
========================================================================
*/
#ifndef KEYEXCHANGECONTAINER_H
#define KEYEXCHANGECONTAINER_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
// ]]] end generated region [Generated Includes]

#include <e32base.h>
#include <bt_sock.h>
#include <BTExtNotifiers.h>
#include <btsdp.h>

#include "BluetoothEngine.h"
#include "KeyExchangeContainerView.h"

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CEikRichTextEditor;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Container class for KeyExchangeContainer
 * 
 * @class	CKeyExchangeContainer KeyExchangeContainer.h
 */
class CKeyExchangeContainer : public CCoeControl
	{
public:
	// constructors and destructor
	CKeyExchangeContainer();
	static CKeyExchangeContainer* NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	static CKeyExchangeContainer* NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	void ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	virtual ~CKeyExchangeContainer();

public:
	
	void AppendToLog(const TDesC& aMessage);
	
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl( TInt aIndex ) const;
	TKeyResponse OfferKeyEventL( 
			const TKeyEvent& aKeyEvent, 
			TEventCode aType );
	void HandleResourceChange( TInt aType );
	
	void FireEngine(TBool serverMode, CKeyExchangeContainerView *callback);
	
	void GetDeviceAddressL(THostName& aHostname, TBTDevAddr& aAddr);
	
protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;
	
private:
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
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CEikRichTextEditor* iLog;
	// ]]] end generated region [Generated Instance Variables]
	CBluetoothEngine *iEngine;
	//RSocketServ iSocketServ;
	// [[[ begin [Overridden Methods]
protected: 
	// ]]] end [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
protected: 
	void SetRichText1FormattingL();
	void SetTextFormattingL();
	void SetLogFormattingL();
	// ]]] end [User Handlers]
	
public: 
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]
		ELog,
		
		// ]]] end generated region [Generated Contents]
		
		// add any user-defined entries here...
		
		ELastControl
		};
	};
				
#endif // KEYEXCHANGECONTAINER_H

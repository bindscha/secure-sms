/*
========================================================================
 Name        : KeyExchangeContainerView.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2008
 Description : Header file for key exchange container view
========================================================================
*/
#ifndef KEYEXCHANGECONTAINERVIEW_H
#define KEYEXCHANGECONTAINERVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
#include <aknwaitdialog.h>
// ]]] end generated region [Generated Includes]
#include <gulicon.h>

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

class CKeyExchangeContainerView;
class CKeyExchangeEngine;

#include "KeyExchangeEngine.h"
#include "AbstractEngine.h"
#include "SMSEngine.h"
#include "SMSReceiver.h"

#include <e32base.h>
#include <bt_sock.h>
#include <BTExtNotifiers.h>
#include <btsdp.h>
#include "ReadMessageContainer.h"
// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CKeyExchangeContainer;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for KeyExchangeContainerView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CKeyExchangeContainerView KeyExchangeContainerView.h
 */						
			
class CKeyExchangeContainerView : public CAknView, public MEngineObserver,  public MSMSRecCallBack
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CKeyExchangeContainerView();
	static CKeyExchangeContainerView* NewL();
	static CKeyExchangeContainerView* NewLC();        
	void ConstructL();
	virtual ~CKeyExchangeContainerView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	CKeyExchangeContainer* CreateContainerL();
	static TInt RunInitiateQueryL( const TDesC* aOverrideText = NULL );
	static TInt RunKeyExchangeTypeL( const TDesC* aOverrideText = NULL );
	static void CreateKeyExchangeDevSelectionItemL( 
			TDes& aBuffer,
			
			const TDesC& aMainText );
	static void CreateKeyExchangeDevSelectionResourceArrayItemL( 
			TDes& aBuffer, 
			TInt aResourceId );
	static CDesCArray* InitializeKeyExchangeDevSelectionLC();
	static CArrayPtr< CGulIcon >* SetupKeyExchangeDevSelectionIconsLC();
	static TInt RunKeyExchangeDevSelectionL( 
			const TDesC* aOverrideText = NULL, 
			CDesCArray* aOverrideItemArray = NULL,
			CArrayPtr< CGulIcon >* aOverrideIconArray = NULL );
	void ExecuteWaitPartnerLD( const TDesC* aOverrideText = NULL );
	void RemoveWaitPartnerL();
	static void RunHostingKeyExchangeL( const TDesC* aOverrideText = NULL );
	static TInt RunAskPhoneNbL( 
			TDes& aData, 
			TBool aUseDefaults = ETrue, 
			const TDesC* aOverridePrompt = NULL );
	static void CreateKeyExchangeOverItemL( 
			TDes& aBuffer,
			
			const TDesC& aMainText );
	static void CreateKeyExchangeOverResourceArrayItemL( 
			TDes& aBuffer, 
			TInt aResourceId );
	static CDesCArray* InitializeKeyExchangeOverLC();
	static CArrayPtr< CGulIcon >* SetupKeyExchangeOverIconsLC();
	static TInt RunKeyExchangeOverL( 
			const TDesC* aOverrideText = NULL, 
			CDesCArray* aOverrideItemArray = NULL,
			CArrayPtr< CGulIcon >* aOverrideIconArray = NULL );
	static TInt RunPasswordQueryL( 
			TDes& aData, 
			TBool aUseDefaults = ETrue, 
			const TDesC* aOverridePrompt = NULL );
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	CKeyExchangeContainer& Container();
	
	void RecSMSMessageL(const TDesC& aMessage);
	
	void HandleConnectedL();
	void HandleEngineError(TInt aError);
	void HandleDataReceivedL(const TDesC& aData);
	
	// [[[ begin [Protected Section]
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	
	// [[[ begin generated region: do not modify [Overridden Methods]
	// ]]] end generated region [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CKeyExchangeContainer* iKeyExchangeContainer;
	CAknWaitDialog* iWaitPartner;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	enum TKeyExchangeDevSelectionImages
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		EKeyExchangeDevSelectionFirstUserImageIndex
		
		// ]]] end generated region [Generated Enums]
		
		};
	
	CAbstractEngine* iEngine;
	CKeyExchangeEngine* iKeyEngine;
	
	TBool iActive;
	
	RSocketServ iSocketServ;
	TBuf<KMaxPasswordLength> iPassword;
	
	enum TKeyExchangeOverImages
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		EKeyExchangeOverFirstUserImageIndex
		
		// ]]] end generated region [Generated Enums]
		
		};
	};

#endif // KEYEXCHANGECONTAINERVIEW_H

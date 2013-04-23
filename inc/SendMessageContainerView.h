/*
========================================================================
 Name        : SendMessageContainerView.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for send message container view
========================================================================
*/
#ifndef SENDMESSAGECONTAINERVIEW_H
#define SENDMESSAGECONTAINERVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]
#include "SMSSender.h"

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CSendMessageContainer;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for SendMessageContainerView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CSendMessageContainerView SendMessageContainerView.h
 */						
			
class CSendMessageContainerView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CSendMessageContainerView();
	static CSendMessageContainerView* NewL();
	static CSendMessageContainerView* NewLC();        
	void ConstructL();
	virtual ~CSendMessageContainerView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	CSendMessageContainer* CreateContainerL();
	static TInt RunPassword_storingL( const TDesC* aOverrideText = NULL );
	static TInt RunPasswordL( 
			TDes& aData, 
			TBool aUseDefaults = ETrue, 
			const TDesC* aOverridePrompt = NULL );
	static void RunPassword_storing_successL( const TDesC* aOverrideText = NULL );
	static void RunPassword_storing_failedL( const TDesC* aOverrideText = NULL );
	static void RunPassword_not_setL( const TDesC* aOverrideText = NULL );
	static void RunMessage_sentL( const TDesC* aOverrideText = NULL );
	static void RunMessage_failedL( const TDesC* aOverrideText = NULL );
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	
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
	CSendMessageContainer* iSendMessageContainer;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	CSMSSender* iSender;
	
	};

#endif // SENDMESSAGECONTAINERVIEW_H

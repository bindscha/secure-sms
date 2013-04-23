/*
========================================================================
 Name        : KeyExchangeContainer.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of key exchange container
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <barsread.h>
#include <stringloader.h>
#include <gdi.h>
#include <eikgted.h>
#include <eikenv.h>
#include <aknviewappui.h>
#include <eikappui.h>
#include <txtfrmat.h>
#include <eikrted.h>
#include <txtrich.h>
#include <gulcolor.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "KeyExchangeContainer.h"
#include "KeyExchangeContainerView.h"
#include "SecureSMS.hrh"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ReadListBox.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CKeyExchangeContainer::CKeyExchangeContainer()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iLog = NULL;
	// ]]] end generated region [Generated Contents]
	
	}
/** 
 * Destroy child controls.
 */
CKeyExchangeContainer::~CKeyExchangeContainer()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iLog;
	iLog = NULL;
	// ]]] end generated region [Generated Contents]
	delete iEngine;
	iEngine = NULL;
	}
				
/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CKeyExchangeContainer
 */
CKeyExchangeContainer* CKeyExchangeContainer::NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CKeyExchangeContainer* self = CKeyExchangeContainer::NewLC( 
			aRect, 
			aParent, 
			aCommandObserver );
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CKeyExchangeContainer
 */
CKeyExchangeContainer* CKeyExchangeContainer::NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CKeyExchangeContainer* self = new ( ELeave ) CKeyExchangeContainer();
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aParent, aCommandObserver );
	return self;
	}
			
/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */ 
void CKeyExchangeContainer::ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	if ( aParent == NULL )
	    {
		CreateWindowL();
	    }
	else
	    {
	    SetContainerWindowL( *aParent );
	    }
	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;
	InitializeControlsL();
	SetRect( aRect );
	ActivateL();
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	SetLogFormattingL();	
	// ]]] end generated region [Post-ActivateL initializations]

	//User::LeaveIfError(iSocketServ.Connect());
	}
			
/**
* Return the number of controls in the container (override)
* @return count
*/
TInt CKeyExchangeContainer::CountComponentControls() const
	{
	return ( int ) ELastControl;
	}
				
/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CKeyExchangeContainer::ComponentControl( TInt aIndex ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
		case ELog:
			return iLog;
		}
	// ]]] end generated region [Generated Contents]
	
	// handle any user controls here...
	
	return NULL;
	}
				
/**
 *	Handle resizing of the container. This implementation will lay out
 *  full-sized controls like list boxes for any screen size, and will layout
 *  labels, editors, etc. to the size they were given in the UI designer.
 *  This code will need to be modified to adjust arbitrary controls to
 *  any screen size.
 */				
void CKeyExchangeContainer::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	// [[[ begin generated region: do not modify [Generated Contents]
			
	// ]]] end generated region [Generated Contents]
	
	}
				
// [[[ begin generated function: do not modify
/**
 * Layout components as specified in the UI Designer
 */
void CKeyExchangeContainer::LayoutControls()
	{
	iLog->SetExtent( TPoint( 0, 0 ), TSize( 176, 140 ) );
	}
// ]]] end generated function

/**
 *	Handle key events.
 */				
TKeyResponse CKeyExchangeContainer::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	
	// ]]] end generated region [Generated Contents]
	
	if ( iFocusControl != NULL
		&& iFocusControl->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
		{
		return EKeyWasConsumed;
		}
	return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
	}
				
// [[[ begin generated function: do not modify
/**
 *	Initialize each control upon creation.
 */				
void CKeyExchangeContainer::InitializeControlsL()
	{
	iLog = new ( ELeave ) CEikRichTextEditor;
	iLog->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_KEY_EXCHANGE_CONTAINER_LOG );
		iLog->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
		{
		HBufC* text = StringLoader::LoadLC( R_KEY_EXCHANGE_CONTAINER_LOG_2 );
		iLog->SetTextL( text );
		CleanupStack::PopAndDestroy( text );
		}
	
	iLog->SetFocus( ETrue );
	iFocusControl = iLog;
	
	}
// ]]] end generated function

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CKeyExchangeContainer::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( EKeyExchangeContainerViewId ) )->ClientRect() );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
				
/**
 *	Draw container contents.
 */				
void CKeyExchangeContainer::Draw( const TRect& aRect ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	
	// ]]] end generated region [Generated Contents]
	
	}
				
void CKeyExchangeContainer::GetDeviceAddressL(THostName& aHostname, TBTDevAddr& aAddr)
	{
	RNotifier btNotifier;
	User::LeaveIfError(btNotifier.Connect());

	TBTDeviceSelectionParamsPckg selectionFilter;
	TBTDeviceResponseParamsPckg selectionResponse;

	selectionFilter().SetUUID(KBT_serviceID);

	TRequestStatus status;
	btNotifier.StartNotifierAndGetResponse(status, KDeviceSelectionNotifierUid,
			selectionFilter, selectionResponse);
	User::WaitForRequest(status);
	
	btNotifier.Close();

	User::LeaveIfError(status.Int());

	aHostname = selectionResponse().DeviceName();
	aAddr = selectionResponse().BDAddr();
	}

void CKeyExchangeContainer::FireEngine(TBool serverMode, CKeyExchangeContainerView *callback)
	{
	//iEngine = CBluetoothEngine::NewL(iSocketServ, serverMode, callback);
	//iEngine->ConnectL();
	}
void CKeyExchangeContainer::SetRichText1FormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	// ]]] end generated region [Generated GlobalText formatting]
	
	}
void CKeyExchangeContainer::SetTextFormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	// ]]] end generated region [Generated GlobalText formatting]
	
	}
void CKeyExchangeContainer::SetLogFormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	
	// ]]] end generated region [Generated GlobalText formatting]
	
	}

void CKeyExchangeContainer::AppendToLog(const TDesC& aMessage)
	{
	CRichText* text = iLog->RichText();
	TInt textSize = text->DocumentLength();
	text->InsertL(textSize, aMessage);
	textSize = text->DocumentLength();
	text->InsertL(textSize, CEditableText::ELineBreak);
	iLog->HandleTextChangedL();
	}

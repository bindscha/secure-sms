/*
========================================================================
 Name        : KeyExchangeContainerView.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of key exchange container view
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <gdi.h>
#include <eikgted.h>
#include <eikenv.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <aknquerydialog.h>
#include <aknlistquerydialog.h>
#include <akniconarray.h>
#include <aknnotewrappers.h>
#include <eikedwin.h>
#include <eikseced.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "SecureSMS.hrh"
#include "KeyExchangeContainerView.h"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ReadListBox.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
#include "KeyExchangeContainer.h"
// ]]] end generated region [Generated User Includes]
#include "GME.h"
// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CKeyExchangeContainerView::CKeyExchangeContainerView(): iActive(EFalse)
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iKeyExchangeContainer = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CKeyExchangeContainerView::~CKeyExchangeContainerView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iKeyExchangeContainer;
	iKeyExchangeContainer = NULL;
	TRAPD( err_WaitPartner, RemoveWaitPartnerL() );
	// ]]] end generated region [Generated Contents]
	iSocketServ.Close();
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CKeyExchangeContainerView
 */
CKeyExchangeContainerView* CKeyExchangeContainerView::NewL()
	{
	CKeyExchangeContainerView* self = CKeyExchangeContainerView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CKeyExchangeContainerView
 */
CKeyExchangeContainerView* CKeyExchangeContainerView::NewLC()
	{
	CKeyExchangeContainerView* self = new ( ELeave ) CKeyExchangeContainerView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CKeyExchangeContainerView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_KEY_EXCHANGE_CONTAINER_KEY_EXCHANGE_CONTAINER_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	User::LeaveIfError(iSocketServ.Connect());
	
	iEngine = NULL;
	iKeyEngine = NULL;
	}

/**
 * @return The UID for this view
 */
TUid CKeyExchangeContainerView::Id() const
	{
	return TUid::Uid( EKeyExchangeContainerViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CKeyExchangeContainerView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		}
	// ]]] end generated region [Generated Code]
	if (!commandHandled)
		{
		if (aCommand == EAknSoftkeyBack)
			{
			AppUi()->HandleCommandL(EAknSoftkeyBack);
			}
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CKeyExchangeContainerView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iKeyExchangeContainer == NULL )
		{
		iKeyExchangeContainer = CreateContainerL();
		iKeyExchangeContainer->SetMopParent( this );
		AppUi()->AddToStackL( *this, iKeyExchangeContainer );
		} 
	// ]]] end generated region [Generated Contents]
	
	if (!iActive && RunInitiateQueryL())
		{
		iActive = ETrue;
		TInt type = RunKeyExchangeOverL();
		TBool serverMode = RunKeyExchangeTypeL();
		iPassword.Copy(KNullDesC);
		if(RunPasswordQueryL(iPassword))
			{
			if(type == 0)
				{
				iEngine = CSMSEngine::NewL(*this, this);
				}
			else
				{
				iEngine = CBluetoothEngine::NewL(*this, iSocketServ, serverMode, this);
				}
	
			iKeyEngine = CKeyExchangeEngine::NewL(*iEngine, !serverMode, iPassword, *this);
			iKeyEngine->StartL();
			}
		}
	
	}

/**
 */
void CKeyExchangeContainerView::DoDeactivate()
	{
	iActive = EFalse;
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iKeyExchangeContainer != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iKeyExchangeContainer );
		delete iKeyExchangeContainer;
		iKeyExchangeContainer = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CKeyExchangeContainerView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CKeyExchangeContainerView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_KEY_EXCHANGE_CONTAINER_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CKeyExchangeContainerView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CKeyExchangeContainer::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CKeyExchangeContainer
 */
CKeyExchangeContainer* CKeyExchangeContainerView::CreateContainerL()
	{
	return CKeyExchangeContainer::NewL( ClientRect(), NULL, this );
	}

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for initiateQuery
 * @param aOverrideText optional override text
 * @return EAknSoftkeyYes (left soft key id) or 0
 */
TInt CKeyExchangeContainerView::RunInitiateQueryL( const TDesC* aOverrideText )
	{
				
	CAknQueryDialog* queryDialog = CAknQueryDialog::NewL();	
	
	if ( aOverrideText != NULL )
		{
		queryDialog->SetPromptL( *aOverrideText );
		}
	return queryDialog->ExecuteLD( R_KEY_EXCHANGE_CONTAINER_INITIATE_QUERY );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for keyExchangeType
 * @param aOverrideText optional override text
 * @return EAknSoftkeyYes (left soft key id) or 0
 */
TInt CKeyExchangeContainerView::RunKeyExchangeTypeL( const TDesC* aOverrideText )
	{
				
	CAknQueryDialog* queryDialog = CAknQueryDialog::NewL();	
	
	if ( aOverrideText != NULL )
		{
		queryDialog->SetPromptL( *aOverrideText );
		}
	return queryDialog->ExecuteLD( R_KEY_EXCHANGE_CONTAINER_KEY_EXCHANGE_TYPE );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Create a list box item with the given column values.
 */
void CKeyExchangeContainerView::CreateKeyExchangeDevSelectionItemL( 
		TDes& aBuffer, 
		
		const TDesC& aMainText )
	{
	_LIT ( KStringHeader, "%S" );

	aBuffer.Format( KStringHeader(), &aMainText );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Add an item to the list by reading the text items from resource
 *	and setting a single image property (if available) from an index
 *	in the list box's icon array.
 *	@param aResourceId id of an ARRAY resource containing the textual
 *	items in the columns
 *	
 */
void CKeyExchangeContainerView::CreateKeyExchangeDevSelectionResourceArrayItemL( 
		TDes& aBuffer, 
		TInt aResourceId )
	{
	CDesCArray* array = CCoeEnv::Static()->ReadDesCArrayResourceL( aResourceId );
	CleanupStack::PushL( array );
	CreateKeyExchangeDevSelectionItemL( aBuffer, ( *array ) [ 0 ] );
	CleanupStack::PopAndDestroy( array );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Initialize contents of the popup item list.  This constructs the array
 *	and pushes it on the cleanup stack.
 *	@return item array, never null
 */
CDesCArray* CKeyExchangeContainerView::InitializeKeyExchangeDevSelectionLC()
	{
	const int KNumItems = 0;
	CDesCArray* itemArray = new ( ELeave ) CDesCArrayFlat( KNumItems ? KNumItems : 1 );
	CleanupStack::PushL( itemArray );
	
	// This is intended to be large enough, but if you get 
	// a USER 11 panic, consider reducing string sizes.
	TBuf< 512 > des;
	return itemArray;
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Set up the list query's icon array.  If any icons are used, allocates an
 *	icon array, and places it on the cleanup stack. 
 *	@return icon array, or NULL
 */
CArrayPtr< CGulIcon >* CKeyExchangeContainerView::SetupKeyExchangeDevSelectionIconsLC()
	{
	CArrayPtr< CGulIcon >* icons = NULL;
	return icons;
	}
	
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup list query dialog for keyExchangeDevSelection.
 * <p>
 * You may override the designer-specified items or icons, though generally
 * both should be overridden together.
 * @param aOverrideText optional override text
 * @param aOverrideItemArray if not NULL, the array of formatted list items to display (passes ownership)
 * @param aOverrideIconArray if not NULL, the array of icons to display (passes ownership)
 * @return selected index (>=0) or -1 for Cancel
 */
TInt CKeyExchangeContainerView::RunKeyExchangeDevSelectionL( 
		const TDesC* aOverrideText,
		CDesCArray* aOverrideItemArray,
		CArrayPtr< CGulIcon >* aOverrideIconArray )
	{
	TInt index = 0;
	CAknListQueryDialog* queryDialog = NULL;
	queryDialog = new ( ELeave ) CAknListQueryDialog( &index );	
	CleanupStack::PushL( queryDialog );
	
	queryDialog->PrepareLC( R_KEY_EXCHANGE_CONTAINER_KEY_EXCHANGE_DEV_SELECTION );
	if ( aOverrideText != NULL )
		{
		queryDialog->SetHeaderTextL( *aOverrideText );
		}
		
	// initialize list items
	CDesCArray* itemArray = NULL;
	
	if ( aOverrideItemArray != NULL ) 
		{
		CleanupStack::PushL( aOverrideItemArray );
		itemArray = aOverrideItemArray;
		}
	else
		{
		itemArray = InitializeKeyExchangeDevSelectionLC();
		}
		
	queryDialog->SetItemTextArray( itemArray );
	queryDialog->SetOwnershipType( ELbmOwnsItemArray );
	CleanupStack::Pop( itemArray );
	
	// initialize list icons
	CArrayPtr< CGulIcon >* iconArray = NULL;
	
	if ( aOverrideIconArray != NULL )
		{
		CleanupStack::PushL( aOverrideIconArray );
		iconArray = aOverrideIconArray;
		}
	else
		{
		iconArray = SetupKeyExchangeDevSelectionIconsLC();
		}
		
	if ( iconArray != NULL ) 
		{
		queryDialog->SetIconArrayL( iconArray );	// passes ownership
		CleanupStack::Pop( iconArray );
		}
	
	// run dialog
	TInt result = queryDialog->RunLD();
	
	// clean up
	CleanupStack::Pop( queryDialog );
	
	return result == 0 ? -1 : index;
	}
	
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Execute the wait dialog for waitPartner. This routine returns
 * while the dialog is showing. It will be closed and destroyed when
 * RemoveWaitPartnerL() or the user selects the Cancel soft key.
 * @param aOverrideText optional override text. When null the text configured
 * in the UI Designer is used.
 */
void CKeyExchangeContainerView::ExecuteWaitPartnerLD( const TDesC* aOverrideText )
	{
	iWaitPartner = new ( ELeave ) CAknWaitDialog( 
			reinterpret_cast< CEikDialog** >( &iWaitPartner ), EFalse );
	if ( aOverrideText != NULL )
		{
		iWaitPartner->SetTextL( *aOverrideText );
		}
	iWaitPartner->ExecuteLD( R_KEY_EXCHANGE_CONTAINER_WAIT_PARTNER );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Close and dispose of the wait dialog for waitPartner
 */
void CKeyExchangeContainerView::RemoveWaitPartnerL()
	{
	if ( iWaitPartner != NULL )
		{
		iWaitPartner->SetCallback( NULL );
		iWaitPartner->ProcessFinishedL();    // deletes the dialog
		iWaitPartner = NULL;
		}
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup note for hostingKeyExchange
 * @param aOverrideText optional override text
 */
void CKeyExchangeContainerView::RunHostingKeyExchangeL( const TDesC* aOverrideText )
	{
	CAknConfirmationNote* note = new ( ELeave ) CAknConfirmationNote();
	if ( aOverrideText == NULL )
		{
		HBufC* noteText = StringLoader::LoadLC( R_KEY_EXCHANGE_CONTAINER_HOSTING_KEY_EXCHANGE );
		note->ExecuteLD( *noteText );
		CleanupStack::PopAndDestroy( noteText );
		}
	else
		{
		note->ExecuteLD( *aOverrideText );
		}
	}
// ]]] end generated function

CKeyExchangeContainer& CKeyExchangeContainerView::Container()
	{
	return *iKeyExchangeContainer;
	}

void CKeyExchangeContainerView::HandleConnectedL()
	{
	iKeyEngine->HandleConnectedL();
	}

void CKeyExchangeContainerView::HandleEngineError(TInt aError)
	{
	iKeyEngine->HandleEngineError(aError);
	}

void CKeyExchangeContainerView::HandleDataReceivedL(const TDesC& aData)
	{
	iKeyEngine->HandleDataReceivedL(aData);
	}

void CKeyExchangeContainerView::RecSMSMessageL(const TDesC& aMessage)
	{
	if(iKeyEngine != NULL)
		iKeyEngine->HandleDataReceivedL(CGMEMessage::ExtractBodyLC(aMessage));
	}

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for askPhoneNb
 * @param aData in-out TDes data
 * @param aUseDefaults TBool use designer default editor data if ETrue
 * @param aOverridePrompt optional override prompt text
 * @return EAknSoftkeyOk (left soft key id) or 0
 */
TInt CKeyExchangeContainerView::RunAskPhoneNbL( 
		TDes& aData, 
		TBool aUseDefaults, 
		const TDesC* aOverridePrompt )
	{
	if ( aUseDefaults )
		{
		HBufC* text = StringLoader::LoadLC( R_KEY_EXCHANGE_CONTAINER_EDIT1 );
		aData.Copy( *text );
		CleanupStack::PopAndDestroy( text );
		}
				
	CAknTextQueryDialog* queryDialog = CAknTextQueryDialog::NewL( aData );	
	
	if ( aOverridePrompt != NULL )
		{
		CleanupStack::PushL( queryDialog );
		queryDialog->SetPromptL( *aOverridePrompt );
		CleanupStack::Pop(); // queryDialog
		}
	
	return queryDialog->ExecuteLD( R_KEY_EXCHANGE_CONTAINER_ASK_PHONE_NB );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Create a list box item with the given column values.
 */
void CKeyExchangeContainerView::CreateKeyExchangeOverItemL( 
		TDes& aBuffer, 
		
		const TDesC& aMainText )
	{
	_LIT ( KStringHeader, "%S" );

	aBuffer.Format( KStringHeader(), &aMainText );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Add an item to the list by reading the text items from resource
 *	and setting a single image property (if available) from an index
 *	in the list box's icon array.
 *	@param aResourceId id of an ARRAY resource containing the textual
 *	items in the columns
 *	
 */
void CKeyExchangeContainerView::CreateKeyExchangeOverResourceArrayItemL( 
		TDes& aBuffer, 
		TInt aResourceId )
	{
	CDesCArray* array = CCoeEnv::Static()->ReadDesCArrayResourceL( aResourceId );
	CleanupStack::PushL( array );
	CreateKeyExchangeOverItemL( aBuffer, ( *array ) [ 0 ] );
	CleanupStack::PopAndDestroy( array );
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Initialize contents of the popup item list.  This constructs the array
 *	and pushes it on the cleanup stack.
 *	@return item array, never null
 */
CDesCArray* CKeyExchangeContainerView::InitializeKeyExchangeOverLC()
	{
	const int KNumItems = 2;
	CDesCArray* itemArray = new ( ELeave ) CDesCArrayFlat( KNumItems ? KNumItems : 1 );
	CleanupStack::PushL( itemArray );
	
	// This is intended to be large enough, but if you get 
	// a USER 11 panic, consider reducing string sizes.
	TBuf< 512 > des;
	CreateKeyExchangeOverResourceArrayItemL(
			des, R_KEY_EXCHANGE_CONTAINER_LISTBOX_ITEM1 );
	itemArray->AppendL( des );
	CreateKeyExchangeOverResourceArrayItemL(
			des, R_KEY_EXCHANGE_CONTAINER_LISTBOX_ITEM2 );
	itemArray->AppendL( des );
	return itemArray;
	}
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Set up the list query's icon array.  If any icons are used, allocates an
 *	icon array, and places it on the cleanup stack. 
 *	@return icon array, or NULL
 */
CArrayPtr< CGulIcon >* CKeyExchangeContainerView::SetupKeyExchangeOverIconsLC()
	{
	CArrayPtr< CGulIcon >* icons = NULL;
	return icons;
	}
	
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup list query dialog for keyExchangeOver.
 * <p>
 * You may override the designer-specified items or icons, though generally
 * both should be overridden together.
 * @param aOverrideText optional override text
 * @param aOverrideItemArray if not NULL, the array of formatted list items to display (passes ownership)
 * @param aOverrideIconArray if not NULL, the array of icons to display (passes ownership)
 * @return selected index (>=0) or -1 for Cancel
 */
TInt CKeyExchangeContainerView::RunKeyExchangeOverL( 
		const TDesC* aOverrideText,
		CDesCArray* aOverrideItemArray,
		CArrayPtr< CGulIcon >* aOverrideIconArray )
	{
	TInt index = 0;
	CAknListQueryDialog* queryDialog = NULL;
	queryDialog = new ( ELeave ) CAknListQueryDialog( &index );	
	CleanupStack::PushL( queryDialog );
	
	queryDialog->PrepareLC( R_KEY_EXCHANGE_CONTAINER_KEY_EXCHANGE_OVER );
	if ( aOverrideText != NULL )
		{
		queryDialog->SetHeaderTextL( *aOverrideText );
		}
		
	// initialize list items
	CDesCArray* itemArray = NULL;
	
	if ( aOverrideItemArray != NULL ) 
		{
		CleanupStack::PushL( aOverrideItemArray );
		itemArray = aOverrideItemArray;
		}
	else
		{
		itemArray = InitializeKeyExchangeOverLC();
		}
		
	queryDialog->SetItemTextArray( itemArray );
	queryDialog->SetOwnershipType( ELbmOwnsItemArray );
	CleanupStack::Pop( itemArray );
	
	// initialize list icons
	CArrayPtr< CGulIcon >* iconArray = NULL;
	
	if ( aOverrideIconArray != NULL )
		{
		CleanupStack::PushL( aOverrideIconArray );
		iconArray = aOverrideIconArray;
		}
	else
		{
		iconArray = SetupKeyExchangeOverIconsLC();
		}
		
	if ( iconArray != NULL ) 
		{
		queryDialog->SetIconArrayL( iconArray );	// passes ownership
		CleanupStack::Pop( iconArray );
		}
	
	// run dialog
	TInt result = queryDialog->RunLD();
	
	// clean up
	CleanupStack::Pop( queryDialog );
	
	return result == 0 ? -1 : index;
	}
	
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Show the popup dialog for passwordQuery
 * @param aData in-out TDes data
 * @param aUseDefaults TBool use designer default editor data if ETrue
 * @param aOverridePrompt optional override prompt text
 * @return EAknSoftkeyOk (left soft key id) or 0
 */
TInt CKeyExchangeContainerView::RunPasswordQueryL( 
		TDes& aData, 
		TBool aUseDefaults, 
		const TDesC* aOverridePrompt )
	{
	if ( aUseDefaults )
		{
	
		}
				
	CAknTextQueryDialog* queryDialog = CAknTextQueryDialog::NewL( aData );	
	
	if ( aOverridePrompt != NULL )
		{
		CleanupStack::PushL( queryDialog );
		queryDialog->SetPromptL( *aOverridePrompt );
		CleanupStack::Pop(); // queryDialog
		}
	
	return queryDialog->ExecuteLD( R_KEY_EXCHANGE_CONTAINER_PASSWORD_QUERY );
	}
// ]]] end generated function


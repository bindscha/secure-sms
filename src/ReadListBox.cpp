/*
 ========================================================================
 Name        : ReadListBox.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of read list box container
 ========================================================================
 */
// [[[ begin generated region: do not modify [Generated System Includes]
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <aknsfld.h>
#include <aknutils.h>
#include <aknviewappui.h>
#include <eikappui.h>
#include <SecureSMS.mbg>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "ReadListBox.h"
#include "ReadListBoxView.h"
#include "SecureSMS.hrh"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ReadListBox.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
_LIT( KSecureSMSFile, "\\resource\\apps\\SecureSMS.mbm" );
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CReadListBox::CReadListBox()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iListBox = NULL;
	iListBoxSearchField = NULL;
	// ]]] end generated region [Generated Contents]

	}
/** 
 * Destroy child controls.
 */
CReadListBox::~CReadListBox()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iListBox;
	iListBox = NULL;
	delete iListBoxSearchField;
	iListBoxSearchField = NULL;
	// ]]] end generated region [Generated Contents]
	
	delete iSmsMtm;
	iSmsMtm = NULL;
	delete iMtmRegistry;
	iMtmRegistry = NULL;
	delete iSession;
	iSession = NULL;

	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CReadListBox
 */
CReadListBox* CReadListBox::NewL(const TRect& aRect,
		const CCoeControl* aParent, MEikCommandObserver* aCommandObserver)
	{
	CReadListBox* self = CReadListBox::NewLC(aRect, aParent, aCommandObserver);
	CleanupStack::Pop(self);
	return self;
	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CReadListBox
 */
CReadListBox* CReadListBox::NewLC(const TRect& aRect,
		const CCoeControl* aParent, MEikCommandObserver* aCommandObserver)
	{
	CReadListBox* self = new (ELeave) CReadListBox();
	CleanupStack::PushL(self);
	self->ConstructL(aRect, aParent, aCommandObserver);
	return self;
	}

/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */
void CReadListBox::ConstructL(const TRect& aRect, const CCoeControl* aParent,
		MEikCommandObserver* aCommandObserver)
	{
	if (aParent == NULL)
		{
		CreateWindowL();
		}
	else
		{
		SetContainerWindowL(*aParent);
		}
	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;

	iSession = CMsvSession::OpenSyncL(*this);
	iMtmRegistry = CClientMtmRegistry::NewL(*iSession);
	iSmsMtm = iMtmRegistry->NewMtmL(KUidMsgTypeSMS);

	InitializeControlsL();
	SetRect(aRect);
	ActivateL();
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	// ]]] end generated region [Post-ActivateL initializations]

	}

/**
 * Return the number of controls in the container (override)
 * @return count
 */
TInt CReadListBox::CountComponentControls() const
	{
	return (int) ELastControl;
	}

/**
 * Get the control with the given index (override)
 * @param aIndex Control index [0...n) (limited by #CountComponentControls)
 * @return Pointer to control
 */
CCoeControl* CReadListBox::ComponentControl(TInt aIndex) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
	case EListBox:
		return iListBox;
	case EListBoxSearchField:
		return iListBoxSearchField;
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
void CReadListBox::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	// [[[ begin generated region: do not modify [Generated Contents]
			
	AknFind::HandleFixedFindSizeChanged( this, iListBox, iListBoxSearchField );
	// ]]] end generated region [Generated Contents]

	}

// [[[ begin generated function: do not modify
/**
 * Layout components as specified in the UI Designer
 */
void CReadListBox::LayoutControls()
	{
	iListBox->SetExtent( TPoint( 0, 0 ), iListBox->MinimumSize() );
	}
// ]]] end generated function

/**
 *	Handle key events.
 */
TKeyResponse CReadListBox::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( aKeyEvent.iCode == EKeyLeftArrow 
		|| aKeyEvent.iCode == EKeyRightArrow )
		{
		// Listbox takes all events even if it doesn't use them
		return EKeyWasNotConsumed;
		}
	if ( iListBoxSearchField != NULL
		&& iListBoxSearchField->OfferKeyEventL( aKeyEvent, aType ) 
			== EKeyWasConsumed )
		{
		return EKeyWasConsumed;
		}
	
	// ]]] end generated region [Generated Contents]

	if (aKeyEvent.iCode == 63557 || aKeyEvent.iCode == EKeyEnter)
		{
		const TUid KAppUid = { 0xEE96475F };
		CCoeEnv::Static()->AppUi()->ActivateViewL(	TVwsViewId(KAppUid, TUid::Uid((int)EReadMessageContainerViewId)),
													TUid::Uid(NumMessages() - 1 - iListBox->CurrentItemIndex()),
													KNullDesC8);
		return EKeyWasConsumed;
		}
	
	// Useless when there is a search bar...
	/*if(aKeyEvent.iCode == EKeyDelete)
		{
		DeleteEntryL(NumMessages() - 1 - iListBox->CurrentItemIndex());
		return EKeyWasConsumed;
		}
	
	if (aKeyEvent.iCode == EKeySpace)
		{
		MarkEntryL(NumMessages() - 1 - iListBox->CurrentItemIndex());
		return EKeyWasConsumed;
		}*/

	if (iFocusControl != NULL
			&& iFocusControl->OfferKeyEventL(aKeyEvent, aType)
					== EKeyWasConsumed)
		{
		return EKeyWasConsumed;
		}
	return CCoeControl::OfferKeyEventL(aKeyEvent, aType);
	}

// [[[ begin generated function: do not modify
/**
 *	Initialize each control upon creation.
 */				
void CReadListBox::InitializeControlsL()
	{
	iListBox = new ( ELeave ) CAknSingleGraphicStyleListBox;
	iListBox->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_READ_LIST_BOX_LIST_BOX );
		iListBox->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
	// the listbox owns the items in the list and will free them
	iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
	
	// setup the icon array so graphics-style boxes work
	SetupListBoxIconsL();
	
	
	// add list items
	/*AddListBoxResourceArrayItemL( R_READ_LIST_BOX_LISTBOX_ITEM1,
			EListBoxSecuresmsOpen_envelope_iconIndex );
	AddListBoxResourceArrayItemL( R_READ_LIST_BOX_LISTBOX_ITEM2,
			EListBoxSecuresmsUnopen_envelope_iconIndex );*/
	FillListBoxL();
	
	// set up the Search Field
	
	CAknSearchField* searchField = 
			CAknSearchField::NewL( *this, CAknSearchField::ESearch, 0, 40 );
	
	CleanupStack::PushL ( searchField );
	CAknFilteredTextListBoxModel* filteredModel = 
		static_cast< CAknFilteredTextListBoxModel* >( iListBox->Model() );
	filteredModel->CreateFilterL( iListBox, searchField );
	CleanupStack::Pop( searchField );
	searchField->MakeVisible( ETrue );
	iListBoxSearchField = searchField;
	
	iListBox->SetFocus( ETrue );
	iFocusControl = iListBox;
	
	}
// ]]] end generated function

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CReadListBox::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	SetRect(iAvkonViewAppUi->View(TUid::Uid(EReadListBoxViewId))->ClientRect());
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]

	}

/**
 *	Draw container contents.
 */
void CReadListBox::Draw(const TRect& aRect) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	
	// ]]] end generated region [Generated Contents]

	}

// [[[ begin generated function: do not modify
/**
 *	Add a list box item to a list.
 */
void CReadListBox::AddListBoxItemL( 
		CEikTextListBox* aListBox,
		const TDesC& aString )
	{
	CTextListBoxModel* model = aListBox->Model();
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	itemArray->AppendL( aString );
	aListBox->HandleItemAdditionL();
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Get the array of selected item indices, with respect to the list model.
 * The array is sorted in ascending order.
 * The array should be destroyed with two calls to CleanupStack::PopAndDestroy(),
 * the first with no argument (referring to the internal resource) and the
 * second with the array pointer.
 * @return newly allocated array, which is left on the cleanup stack;
 *	or NULL for empty list. 
 */
RArray< TInt >* CReadListBox::GetSelectedListBoxItemsLC( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return NULL;
		
	// get currently selected indices
	const CListBoxView::CSelectionIndexArray* selectionIndexes =
		aListBox->SelectionIndexes();
	TInt selectedIndexesCount = selectionIndexes->Count();
	if ( selectedIndexesCount == 0 )
		return NULL;
		
	// copy the indices and sort numerically
	RArray<TInt>* orderedSelectedIndices = 
		new (ELeave) RArray< TInt >( selectedIndexesCount );
	
	// push the allocated array
	CleanupStack::PushL( orderedSelectedIndices );
	
	// dispose the array resource
	CleanupClosePushL( *orderedSelectedIndices );
	
	// see if the search field is enabled
	CAknListBoxFilterItems* filter = model->Filter();
	if ( filter != NULL )
		{
		// when filtering enabled, translate indices back to underlying model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			{
			TInt filteredItem = ( *selectionIndexes ) [ idx ];
			TInt actualItem = filter->FilteredItemIndex ( filteredItem );
			orderedSelectedIndices->InsertInOrder( actualItem );
			}
		}
	else
		{
		// the selection indices refer directly to the model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			orderedSelectedIndices->InsertInOrder( ( *selectionIndexes ) [ idx ] );
		}	
		
	return orderedSelectedIndices;
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Delete the selected item or items from the list box.
 */
void CReadListBox::DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return;
	
	RArray< TInt >* orderedSelectedIndices = GetSelectedListBoxItemsLC( aListBox );		
	if ( !orderedSelectedIndices )
		return;
		
	// Delete selected items from bottom up so indices don't change on us
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	TInt currentItem = 0;
	
	for ( TInt idx = orderedSelectedIndices->Count(); idx-- > 0; ) 
		{
		currentItem = ( *orderedSelectedIndices )[ idx ];
		itemArray->Delete ( currentItem );
		}
	
	// dispose the array resources
	CleanupStack::PopAndDestroy();
	
	// dispose the array pointer
	CleanupStack::PopAndDestroy( orderedSelectedIndices );
	
	// refresh listbox's cursor now that items are deleted
	AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
		aListBox, currentItem, ETrue );
	}

void CReadListBox::DeleteListBoxItemsL( CEikTextListBox* aListBox )
	{
	CTextListBoxModel* model = aListBox->Model();
	CDesCArray* itemArray = static_cast<CDesCArray*> (model->ItemTextArray());
	itemArray->Reset();
	aListBox->HandleItemRemovalL();
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Get the listbox.
 */
CAknSingleGraphicStyleListBox* CReadListBox::ListBox()
	{
	return iListBox;
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Create a list box item with the given column values.
 */
void CReadListBox::CreateListBoxItemL( TDes& aBuffer, 
		TInt aIconIndex,
		const TDesC& aMainText )
	{
	_LIT ( KStringHeader, "%d\t%S" );
	
	aBuffer.Format( KStringHeader(), aIconIndex, &aMainText );
	} 
				
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Add an item to the list by reading the text items from the array resource
 *	and setting a single image property (if available) from an index
 *	in the list box's icon array.
 *	@param aResourceId id of an ARRAY resource containing the textual
 *	items in the columns
 *	@param aIconIndex the index in the icon array, or -1
 */
void CReadListBox::AddListBoxResourceArrayItemL( TInt aResourceId, TInt aIconIndex )
	{
	CDesCArray* array = iCoeEnv->ReadDesCArrayResourceL( aResourceId );
	CleanupStack::PushL( array );
	// This is intended to be large enough, but if you get 
	// a USER 11 panic, consider reducing string sizes.
	TBuf<512> listString; 
	CreateListBoxItemL( listString, aIconIndex, ( *array ) [ 0 ] );
	AddListBoxItemL( iListBox, listString );
	CleanupStack::PopAndDestroy( array );
	} 
				
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Set up the list's icon array.
 */
void CReadListBox::SetupListBoxIconsL()
	{
	CArrayPtr< CGulIcon >* icons = NULL;		
	icons = new (ELeave) CAknIconArray( 2 );
	CleanupStack::PushL( icons );
	CGulIcon* icon;
	// for EListBoxSecuresmsOpen_envelope_iconIndex
	icon = LoadAndScaleIconL(
			KSecureSMSFile, EMbmSecuresmsOpen_envelope_icon, EMbmSecuresmsOpen_envelope_icon_mask,
			NULL, EAspectRatioPreserved );
	CleanupStack::PushL( icon );
	icons->AppendL( icon );
	CleanupStack::Pop( icon );
	// for EListBoxSecuresmsUnopen_envelope_iconIndex
	icon = LoadAndScaleIconL(
			KSecureSMSFile, EMbmSecuresmsUnopen_envelope_icon, EMbmSecuresmsUnopen_envelope_icon_mask,
			NULL, EAspectRatioPreserved );
	CleanupStack::PushL( icon );
	icons->AppendL( icon );
	CleanupStack::Pop( icon );
	CleanupStack::Pop( icons );
	
	if ( icons != NULL )
		{
		iListBox->ItemDrawer()->ColumnData()->SetIconArray( icons );
		}
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/** 
 *	Handle commands relating to markable lists.
 */
TBool CReadListBox::HandleMarkableListCommandL( TInt aCommand )
	{
	return EFalse;
	}

// ]]] end generated function

TBool CReadListBox::CheckIfFolderExistsL()
	{
	CMsvEntry * entry = iSession->GetEntryL(KMsvMyFoldersEntryIdValue);
	CleanupStack::PushL(entry);
	CMsvEntrySelection * entries = entry->ChildrenWithTypeL(KUidMsvFolderEntry);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(entries);
	TInt nCount = entries->Count();
	TInt found = 0;
	for (TInt i = 1; i < nCount; i++)
		{
		TMsvId entryID = entries->At(i);
		entry = iSession->GetEntryL(entryID);
		CleanupStack::PushL(entry);
		TMsvEntry msvEntry = entry->Entry();

		TPtrC descr = msvEntry.iDetails;
		if (descr.Compare(KGMEFolderName) == 0)
			{
			found = 1;
			iNewFolderId = entryID;
			}
		CleanupStack::PopAndDestroy(entry);
		}
	CleanupStack::PopAndDestroy(entries);

	return found;
	}

TBool CReadListBox::CreateFolderL()
	{
	TMsvId msvServId;
	CMsvEntry *entry1 = NULL;
	CMsvEntry *rootEntry = NULL;
	CMsvEntry *entryRootService = NULL;

	TInt newFldrID = 0;

	//Get the entry (whatever is passed in)                                                    
	entry1 = iSmsMtm->Session().GetEntryL(KMsvMyFoldersEntryIdValue);
	CleanupStack::PushL(entry1);

	if (entry1)
		{
		msvServId = entry1->OwningService();

		entryRootService = iSmsMtm->Session().GetEntryL(msvServId);
		CleanupStack::PushL(entryRootService);

		rootEntry = iSmsMtm->Session().GetEntryL(msvServId);
		CleanupStack::PushL(rootEntry);

		rootEntry->SetEntryL(KMsvMyFoldersEntryIdValue); // set to parent                      

		TMsvEntry newServiceEntry;
		TTime ttime;
		ttime.HomeTime();
		newServiceEntry.iDate = ttime;
		newServiceEntry.iSize = 0;
		newServiceEntry.iType = KUidMsvFolderEntry;
		newServiceEntry.iMtm = KUidMsvLocalServiceMtm;
		newServiceEntry.iServiceId = msvServId;
		newServiceEntry.iDetails.Set(KGMEFolderName);
		newServiceEntry.iDescription.Set(KNullDesC);
		newServiceEntry.SetVisible(ETrue);

		rootEntry->CreateL(newServiceEntry);
		newFldrID = newServiceEntry.Id();
		iNewFolderId = newFldrID;
		CleanupStack::PopAndDestroy(rootEntry);
		CleanupStack::PopAndDestroy(entryRootService);
		}
	CleanupStack::PopAndDestroy(entry1);
	return ETrue;
	}

void CReadListBox::FillListBoxL()
	{
	if (!CheckIfFolderExistsL())
		CreateFolderL();
	
	DeleteListBoxItemsL(iListBox);
	
	CMsvEntry * entry = iSession->GetEntryL(iNewFolderId);
	CleanupStack::PushL(entry);
	CMsvEntrySelection* messages = entry->ChildrenWithMtmL(KUidMsgTypeSMS);
	CDesC16ArraySeg* array = new (ELeave) CDesC16ArraySeg(16);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(array);
	CleanupStack::PushL(messages);
	TInt nCount = messages->Count();
	for (TInt i = nCount - 1; i >= 0; --i)
		{
		HBufC* item = HBufC::New(MAX_ITEM_LENGTH);
		CleanupStack::PushL(item);
		
		iSmsMtm->SwitchCurrentEntryL(messages->At(i));
		entry = iSession->GetEntryL((*messages)[i]);
		CleanupStack::PushL(entry);
		CMsvStore* inboxStore = entry->ReadStoreL();
		CleanupStack::PushL(inboxStore);
		TBool isUnread = ETrue;
		if (inboxStore->HasBodyTextL())
			{
			TMsvEntry entry1 = entry->Entry();
			isUnread = entry1.Unread();
			TBufC<50> aText(entry1.iDetails);
			item->Des().Append(aText);
			item->Des().Append(',');
			item->Des().Append(' ');
			TTime ttime = entry1.iDate;
			TBuf<50> aDate;
			aDate.Format(_L("%02d-%02d %02d:%02d"), ttime.DateTime().Month() + 1,
					ttime.DateTime().Day() + 1, (ttime.DateTime().Hour() + 2) % 24,
					ttime.DateTime().Minute());
			item->Des().Append(aDate);
			}
		
		TInt icon = EListBoxSecuresmsUnopen_envelope_iconIndex;
		if(!isUnread)
			icon = EListBoxSecuresmsOpen_envelope_iconIndex;
		
		TBuf<MAX_ITEM_LENGTH> fullitem;
		CreateListBoxItemL(fullitem, icon, *item);
		AddListBoxItemL(iListBox, fullitem);
		CleanupStack::PopAndDestroy(inboxStore);
		CleanupStack::PopAndDestroy(entry);
		CleanupStack::PopAndDestroy(item);
		}
	
	CleanupStack::PopAndDestroy(messages);
	CleanupStack::Pop(array);
	}

void CReadListBox::DeleteEntryL(TInt entryId)
	{
	if (!CheckIfFolderExistsL())
		CreateFolderL();
	
	CMsvEntry * entry = iSession->GetEntryL(iNewFolderId);
	CleanupStack::PushL(entry);
	CMsvEntrySelection* messages = entry->ChildrenWithMtmL(KUidMsgTypeSMS);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(messages);
	TInt nCount = messages->Count();
		
	iSmsMtm->SwitchCurrentEntryL(messages->At(entryId));
	entry = iSession->GetEntryL((*messages)[entryId]);
	CleanupStack::PushL(entry);
	
	TMsvEntry entry1 = entry->Entry();
	iSmsMtm->Entry().DeleteL(entry1.Id());
	
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PopAndDestroy(messages);
	}

void CReadListBox::MarkEntryL(TInt entryId)
	{
	if (!CheckIfFolderExistsL())
		CreateFolderL();
	
	CMsvEntry * entry = iSession->GetEntryL(iNewFolderId);
	CleanupStack::PushL(entry);
	CMsvEntrySelection* messages = entry->ChildrenWithMtmL(KUidMsgTypeSMS);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(messages);
	TInt nCount = messages->Count();
		
	iSmsMtm->SwitchCurrentEntryL(messages->At(entryId));
	entry = iSession->GetEntryL((*messages)[entryId]);
	CleanupStack::PushL(entry);
	
	TMsvEntry entry1 = entry->Entry();
	entry1.SetUnread(!entry1.Unread());
	iSmsMtm->Entry().ChangeL(entry1);

	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PopAndDestroy(messages);
	}

TInt CReadListBox::NumMessages()
	{
	if (!CheckIfFolderExistsL())
		CreateFolderL();

	CMsvEntry * entry = iSession->GetEntryL(iNewFolderId);
	CleanupStack::PushL(entry);
	CMsvEntrySelection* messages = entry->ChildrenWithMtmL(KUidMsgTypeSMS);
	CleanupStack::PopAndDestroy(entry);
	CleanupStack::PushL(messages);
	TInt nCount = messages->Count();
	CleanupStack::PopAndDestroy(messages);
	return nCount;
	}

void CReadListBox::UpdateL()
	{
	FillListBoxL();
	}

// [[[ begin generated function: do not modify
/**
 *	This routine loads and scales a bitmap or icon.
 *
 *	@param aFileName the MBM or MIF filename
 *	@param aBitmapId the bitmap id
 *	@param aMaskId the mask id or -1 for none
 *	@param aSize the TSize for the icon, or NULL to use real size
 *	@param aScaleMode one of the EAspectRatio* enums when scaling
 *
 */
CGulIcon* CReadListBox::LoadAndScaleIconL( 
		const TDesC& aFileName,
		TInt aBitmapId, 
		TInt aMaskId, 
		TSize* aSize, 
		TScaleMode aScaleMode )
	{
	CFbsBitmap* bitmap;
	CFbsBitmap* mask;
	AknIconUtils::CreateIconL( bitmap, mask, aFileName, aBitmapId, aMaskId );
	
	TSize size;
	if ( aSize == NULL )
		{
		// Use size from the image header.  In case of SVG,
		// we preserve the image data for a while longer, since ordinarily
		// it is disposed at the first GetContentDimensions() or SetSize() call.
		AknIconUtils::PreserveIconData( bitmap );
		AknIconUtils::GetContentDimensions( bitmap, size );
		}
	else
		{
		size = *aSize;
		}
	
	AknIconUtils::SetSize( bitmap, size, aScaleMode );
	AknIconUtils::SetSize( mask, size, aScaleMode );
	
	if ( aSize == NULL )
		{
		AknIconUtils::DestroyIconData( bitmap );
		}
	
	return CGulIcon::NewL( bitmap, mask );
	}

// ]]] end generated function


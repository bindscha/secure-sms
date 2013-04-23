/*
 ========================================================================
 Name        : ReadListBox.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for read list box container
 ========================================================================
 */
#ifndef READLISTBOX_H
#define READLISTBOX_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
#include <akniconutils.h>
#include <gulicon.h>
// ]]] end generated region [Generated Includes]
#include <aknlists.h> // Do not forget !!!

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

#include <aknnotewrappers.h> // TODO

#define MAX_ITEM_LENGTH 50

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CAknSingleGraphicStyleListBox;
class CEikTextListBox;
class CAknSearchField;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Container class for ReadListBox
 * 
 * @class	CReadListBox ReadListBox.h
 */
class CReadListBox : public CCoeControl, MMsvSessionObserver
	{
public:
	// constructors and destructor
	CReadListBox();
	static CReadListBox* NewL(const TRect& aRect, const CCoeControl* aParent,
			MEikCommandObserver* aCommandObserver);
	static CReadListBox* NewLC(const TRect& aRect, const CCoeControl* aParent,
			MEikCommandObserver* aCommandObserver);
	void ConstructL(const TRect& aRect, const CCoeControl* aParent,
			MEikCommandObserver* aCommandObserver);
	virtual ~CReadListBox();
	void HandleSessionEventL(TMsvSessionEvent /*aEvent*/, TAny */*aArg1*/, TAny */*aArg2*/, TAny */*aArg3*/) {}

public:
	TInt GetSelectedItem( ) {return iListBox->CurrentItemIndex(); }
	void SetSelectedItem( TInt aSelectedItem ) { 
		iListBox->SetCurrentItemIndex( aSelectedItem );
	}
	
	void UpdateL();
	
	TInt NumMessages();
	
	void DeleteEntryL(TInt entryId);
	void MarkEntryL(TInt entryId);
	
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl(TInt aIndex) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	void HandleResourceChange(TInt aType);

protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw(const TRect& aRect) const;

	CMsvSession* iSession;
	CClientMtmRegistry* iMtmRegistry;
	CBaseMtm* iSmsMtm;
	
	TMsvId iNewFolderId;
	
	TBool CheckIfFolderExistsL();
	TBool CreateFolderL();
	void FillListBoxL();

private:
	void InitializeControlsL();
	void LayoutControls();
	CCoeControl* iFocusControl;
	MEikCommandObserver* iCommandObserver;
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	static void AddListBoxItemL( 
			CEikTextListBox* aListBox,
			const TDesC& aString );
	static RArray< TInt >* GetSelectedListBoxItemsLC( CEikTextListBox* aListBox );
	static void DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox );
	CAknSingleGraphicStyleListBox* ListBox();
	static void CreateListBoxItemL( TDes& aBuffer, 
			TInt aIconIndex,
			const TDesC& aMainText );
	void AddListBoxResourceArrayItemL( TInt aResourceId, TInt aIconIndex );
	void SetupListBoxIconsL();
	static CGulIcon* LoadAndScaleIconL(
			const TDesC& aFileName,
			TInt aBitmapId,
			TInt aMaskId,
			TSize* aSize,
			TScaleMode aScaleMode );
	TBool HandleMarkableListCommandL( TInt aCommand );
	// ]]] end generated region [Generated Methods]
	void DeleteListBoxItemsL( CEikTextListBox* aListBox );
	// [[[ begin generated region: do not modify [Generated Type Declarations]
public: 
	// ]]] end generated region [Generated Type Declarations]

	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CAknSingleGraphicStyleListBox* iListBox;
	CAknSearchField* iListBoxSearchField;
	// ]]] end generated region [Generated Instance Variables]


	// [[[ begin [Overridden Methods]
protected:
	// ]]] end [Overridden Methods]


	// [[[ begin [User Handlers]
protected:
	// ]]] end [User Handlers]

public:
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]
		EListBox,
		EListBoxSearchField,
		
		// ]]] end generated region [Generated Contents]

		// add any user-defined entries here...

		ELastControl
		};
	enum TListBoxImages
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		EListBoxSecuresmsOpen_envelope_iconIndex = 0,
		EListBoxSecuresmsUnopen_envelope_iconIndex = 1,
		EListBoxFirstUserImageIndex
		
		// ]]] end generated region [Generated Enums]

		};
	};

#endif // READLISTBOX_H

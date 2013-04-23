/*
========================================================================
 Name        : MainListBox.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for main list box (application's main view)
========================================================================
*/
#ifndef MAINLISTBOX_H
#define MAINLISTBOX_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
#include <akniconutils.h>
#include <gulicon.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
#include <eiklbo.h>
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CAknDoubleLargeStyleListBox;
class CEikTextListBox;
// ]]] end generated region [Generated Forward Declarations]
#include <aknlists.h> // Do not forget !!!

/**
 * Container class for MainListBox
 * 
 * @class	CMainListBox MainListBox.h
 */
class CMainListBox : public CCoeControl
	,MEikListBoxObserver	{
public:
	// constructors and destructor
	CMainListBox();
	static CMainListBox* NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	static CMainListBox* NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	void ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	virtual ~CMainListBox();

public:
	TInt GetSelectedItem( ) {return iListBox->CurrentItemIndex(); }
	void SetSelectedItem( TInt aSelectedItem ) { 
		iListBox->SetCurrentItemIndex( aSelectedItem );
	}
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
	CAknDoubleLargeStyleListBox* ListBox();
	static void CreateListBoxItemL( TDes& aBuffer, 
			TInt aIconIndex,
			const TDesC& aMainText,
			const TDesC& aSecondaryText );
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
	
	// [[[ begin generated region: do not modify [Generated Type Declarations]
public: 
	// ]]] end generated region [Generated Type Declarations]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CAknDoubleLargeStyleListBox* iListBox;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [Overridden Methods]
protected: 
	void HandleListBoxEventL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	// ]]] end [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
public: 
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]
		EListBox,
		
		// ]]] end generated region [Generated Contents]
		
		// add any user-defined entries here...
		
		ELastControl
		};
	enum TListBoxImages
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		EListBoxSecuresmsSend_iconIndex = 0,
		EListBoxSecuresmsReceive_iconIndex = 1,
		EListBoxSecuresmsKey_exchange_iconIndex = 2,
		EListBoxSecuresmsSettings_iconIndex = 3,
		EListBoxFirstUserImageIndex
		
		// ]]] end generated region [Generated Enums]
		
		};
	
	// [[[ begin [MEikListBoxObserver support]
private: 
	typedef void ( CMainListBox::*ListBoxEventHandler )( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent );
	
	void AddListBoxEventHandlerL( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent, 
			ListBoxEventHandler aHandler );
	
	struct TListBoxEventDispatch 
		{ 
		CEikListBox* src; 
		TListBoxEvent event; 
		ListBoxEventHandler handler;
		};
		
	RArray< TListBoxEventDispatch > iListBoxEventDispatch;
	// ]]] end [MEikListBoxObserver support]
	
	};
				
#endif // MAINLISTBOX_H

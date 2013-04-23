/*
========================================================================
 Name        : MainListBoxView.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for main list box view (application's main view)
========================================================================
*/
#ifndef MAINLISTBOXVIEW_H
#define MAINLISTBOXVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]
#include "MainListBox.h" // Do not forget this ever again... That's worth a 3-hour headache

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CMainListBox;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for MainListBoxView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CMainListBoxView MainListBoxView.h
 */						
			
class CMainListBoxView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CMainListBoxView();
	static CMainListBoxView* NewL();
	static CMainListBoxView* NewLC();        
	void ConstructL();
	virtual ~CMainListBoxView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	CMainListBox* CreateContainerL();
	static TInt RunAppPasswordL( 
			TDes& aData, 
			TBool aUseDefaults = ETrue, 
			const TDesC* aOverridePrompt = NULL );
	static TInt RunNewMessageL( const TDesC* aOverrideText = NULL );
	static TInt RunAboutL( const TDesC* aOverrideText = NULL );
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
	
public:
	TInt CurrentSelectedIndex( ) {return iMainListBox->GetSelectedItem(); }
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CMainListBox* iMainListBox;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // MAINLISTBOXVIEW_H

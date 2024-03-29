/*
========================================================================
 Name        : ReadListBoxView.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for read list box view
========================================================================
*/
#ifndef READLISTBOXVIEW_H
#define READLISTBOXVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CReadListBox;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for ReadListBoxView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CReadListBoxView ReadListBoxView.h
 */						
			
class CReadListBoxView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CReadListBoxView();
	static CReadListBoxView* NewL();
	static CReadListBoxView* NewLC();        
	void ConstructL();
	virtual ~CReadListBoxView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	CReadListBox* CreateContainerL();
	static void RunNoMessagesL( const TDesC* aOverrideText = NULL );
	static TInt RunConfDeleteMessageL( const TDesC* aOverrideText = NULL );
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	CReadListBox* ReadListBox() { return iReadListBox; }
	
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
	CReadListBox* iReadListBox;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // READLISTBOXVIEW_H

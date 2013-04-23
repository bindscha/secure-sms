/*
========================================================================
 Name        : ReadMessageContainerView.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for read message container view
========================================================================
*/
#ifndef READMESSAGECONTAINERVIEW_H
#define READMESSAGECONTAINERVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CReadMessageContainer;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for ReadMessageContainerView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CReadMessageContainerView ReadMessageContainerView.h
 */						
			
class CReadMessageContainerView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CReadMessageContainerView();
	static CReadMessageContainerView* NewL();
	static CReadMessageContainerView* NewLC();        
	void ConstructL();
	virtual ~CReadMessageContainerView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	CReadMessageContainer* CreateContainerL(TInt aMessageId);
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	TInt GetNumMessages();
	
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
	CReadMessageContainer* iReadMessageContainer;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // READMESSAGECONTAINERVIEW_H

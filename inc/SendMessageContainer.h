/*
========================================================================
 Name        : SendMessageContainer.h
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Header file for send message container
========================================================================
*/
#ifndef SENDMESSAGECONTAINER_H
#define SENDMESSAGECONTAINER_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
// ]]] end generated region [Generated Includes]

// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CEikRichTextEditor;
class CEikLabel;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Container class for SendMessageContainer
 * 
 * @class	CSendMessageContainer SendMessageContainer.h
 */
class CSendMessageContainer : public CCoeControl
	{
public:
	// constructors and destructor
	CSendMessageContainer();
	static CSendMessageContainer* NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	static CSendMessageContainer* NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	void ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	virtual ~CSendMessageContainer();

public:
	void GetMessageL(TDes& aMessage);
	void GetToL(TDes& aTo);
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
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Type Declarations]
public: 
	// ]]] end generated region [Generated Type Declarations]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CEikRichTextEditor* iTo;
	CEikLabel* iLabelMessage;
	CEikLabel* iLabelTo;
	CEikRichTextEditor* iMessage;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin [Overridden Methods]
protected: 
	// ]]] end [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
protected: 
	void SetToFormattingL();
	void SetMessageFormattingL();
	// ]]] end [User Handlers]
	
public: 
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]
		ETo,
		ELabelMessage,
		ELabelTo,
		EMessage,
		
		// ]]] end generated region [Generated Contents]
		
		// add any user-defined entries here...
		
		ELastControl
		};
	};
				
#endif // SENDMESSAGECONTAINER_H

/*
========================================================================
 Name        : SendMessageContainer.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of send message container
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <barsread.h>
#include <stringloader.h>
#include <gdi.h>
#include <eikgted.h>
#include <eikenv.h>
#include <eiklabel.h>
#include <aknviewappui.h>
#include <eikappui.h>
#include <txtfrmat.h>
#include <eikrted.h>
#include <txtrich.h>
#include <gulcolor.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]
#include <gulbordr.h>
// [[[ begin generated region: do not modify [Generated User Includes]
#include "SendMessageContainer.h"
#include "SendMessageContainerView.h"
#include "SecureSMS.hrh"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CSendMessageContainer::CSendMessageContainer()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iTo = NULL;
	iLabelMessage = NULL;
	iLabelTo = NULL;
	iMessage = NULL;
	// ]]] end generated region [Generated Contents]

	}
/** 
 * Destroy child controls.
 */
CSendMessageContainer::~CSendMessageContainer()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iTo;
	iTo = NULL;
	delete iLabelMessage;
	iLabelMessage = NULL;
	delete iLabelTo;
	iLabelTo = NULL;
	delete iMessage;
	iMessage = NULL;
	// ]]] end generated region [Generated Contents]

	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CSendMessageContainer
 */
CSendMessageContainer* CSendMessageContainer::NewL(const TRect& aRect,
		const CCoeControl* aParent, MEikCommandObserver* aCommandObserver)
	{
	CSendMessageContainer* self = CSendMessageContainer::NewLC(aRect, aParent,
			aCommandObserver);
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
 * @return new instance of CSendMessageContainer
 */
CSendMessageContainer* CSendMessageContainer::NewLC(const TRect& aRect,
		const CCoeControl* aParent, MEikCommandObserver* aCommandObserver)
	{
	CSendMessageContainer* self = new (ELeave) CSendMessageContainer();
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
void CSendMessageContainer::ConstructL(const TRect& aRect,
		const CCoeControl* aParent, MEikCommandObserver* aCommandObserver)
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
	InitializeControlsL();
	SetRect(aRect);
	ActivateL();
	iTo->SetBorder(TGulBorder::ESingleBlack);
	iMessage->SetBorder(TGulBorder::ESingleBlack);
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	SetToFormattingL();	
	SetMessageFormattingL();	
	// ]]] end generated region [Post-ActivateL initializations]

	}

/**
 * Return the number of controls in the container (override)
 * @return count
 */
TInt CSendMessageContainer::CountComponentControls() const
	{
	return (int) ELastControl;
	}

/**
 * Get the control with the given index (override)
 * @param aIndex Control index [0...n) (limited by #CountComponentControls)
 * @return Pointer to control
 */
CCoeControl* CSendMessageContainer::ComponentControl(TInt aIndex) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
		case ETo:
			return iTo;
		case ELabelMessage:
			return iLabelMessage;
		case ELabelTo:
			return iLabelTo;
		case EMessage:
			return iMessage;
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
void CSendMessageContainer::SizeChanged()
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
void CSendMessageContainer::LayoutControls()
	{
	TRect rect = CEikonEnv::Static()->AppUiFactory()->ClientRect();
	TInt height = rect.Height();
	TInt width = rect.Width();
	TInt heightFraction = (int) (1.0 / 8.0 * height); // Subdivision of height
	TInt toWidth = (int) (1.0 / 6.0 * width); // Width of the To field
	TInt spacing = 4; // Spacing between components
	iLabelTo->SetExtent(TPoint(0, spacing), TSize(toWidth, heightFraction));
	iTo->SetExtent(TPoint(toWidth, spacing), TSize(width - toWidth - spacing,
			heightFraction));
	iLabelMessage->SetExtent(TPoint(0, heightFraction + spacing), TSize(width,
			heightFraction));
	iMessage->SetExtent(TPoint(spacing, 2 * heightFraction + spacing), TSize(
			width - 2 * spacing, height - 2 * heightFraction - 2 * spacing));
	}
// ]]] end generated function

/**
 *	Handle key events.
 */
TKeyResponse CSendMessageContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,
		TEventCode aType)
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	
	// ]]] end generated region [Generated Contents]

	if (aKeyEvent.iCode == EKeyDownArrow && iFocusControl == iTo)
		{
		iTo->SetFocus(EFalse);
		iMessage->SetFocus(ETrue);
		iFocusControl = iMessage;
		}

	if (aKeyEvent.iCode == EKeyUpArrow && iFocusControl == iMessage
			&& iMessage->CursorPos() == 0)
		{
		iMessage->SetFocus(EFalse);
		iTo->SetFocus(ETrue);
		iFocusControl = iTo;
		}
	
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
void CSendMessageContainer::InitializeControlsL()
	{
	iTo = new ( ELeave ) CEikRichTextEditor;
	iTo->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_SEND_MESSAGE_CONTAINER_TO );
		iTo->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
		{
		HBufC* text = StringLoader::LoadLC( R_SEND_MESSAGE_CONTAINER_TO_2 );
		iTo->SetTextL( text );
		CleanupStack::PopAndDestroy( text );
		}
	iLabelMessage = new ( ELeave ) CEikLabel;
	iLabelMessage->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_SEND_MESSAGE_CONTAINER_LABEL_MESSAGE );
		iLabelMessage->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
	iLabelTo = new ( ELeave ) CEikLabel;
	iLabelTo->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_SEND_MESSAGE_CONTAINER_LABEL_TO );
		iLabelTo->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
	iMessage = new ( ELeave ) CEikRichTextEditor;
	iMessage->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_SEND_MESSAGE_CONTAINER_MESSAGE );
		iMessage->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
		{
		HBufC* text = StringLoader::LoadLC( R_SEND_MESSAGE_CONTAINER_MESSAGE_2 );
		iMessage->SetTextL( text );
		CleanupStack::PopAndDestroy( text );
		}
	
	iTo->SetFocus( ETrue );
	iFocusControl = iTo;
	
	}
// ]]] end generated function

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CSendMessageContainer::HandleResourceChange(TInt aType)
	{
	CCoeControl::HandleResourceChange(aType);
	SetRect(
			iAvkonViewAppUi->View(TUid::Uid(ESendMessageContainerViewId))->ClientRect());
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]

	}

/**
 *	Draw container contents.
 */
void CSendMessageContainer::Draw(const TRect& aRect) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	
	// ]]] end generated region [Generated Contents]
	
	// Draw borders
	TGulBorder border = iTo->Border();
	TRect editorRect = iTo->Rect();
	border.Draw(gc, border.OuterRect(editorRect));
	editorRect = iMessage->Rect();
	border.Draw(gc, border.OuterRect(editorRect));

	}

void CSendMessageContainer::SetToFormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	
	// ]]] end generated region [Generated GlobalText formatting]

	}
void CSendMessageContainer::SetMessageFormattingL()
	{
	// [[[ begin generated region: do not modify [Generated GlobalText formatting]
	
	// ]]] end generated region [Generated GlobalText formatting]

	}

void CSendMessageContainer::GetMessageL(TDes& aMessage)
	{
	iMessage->GetText(aMessage);
	}

void CSendMessageContainer::GetToL(TDes& aTo)
	{
	iTo->GetText(aTo);
	}

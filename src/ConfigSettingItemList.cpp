/*
========================================================================
 Name        : ConfigSettingItemList.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of settings handler
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <avkon.hrh>
#include <avkon.rsg>
#include <eikmenup.h>
#include <aknappui.h>
#include <eikcmobs.h>
#include <barsread.h>
#include <stringloader.h>
#include <gdi.h>
#include <eikseced.h>
#include <eikenv.h>
#include <aknpopupfieldtext.h>
#include <eikappui.h>
#include <aknviewappui.h>
#include <SecureSMS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "ConfigSettingItemList.h"
#include "ConfigSettingItemListSettings.h"
#include "SecureSMS.hrh"
#include "MainListBox.hrh"
#include "SendMessageContainer.hrh"
#include "ReadListBox.hrh"
#include "ConfigSettingItemList.hrh"
#include "KeyExchangeContainer.hrh"
#include "ConfigSettingItemListView.h"
// ]]] end generated region [Generated User Includes]

// Constants
_LIT(KSettingsFile, "settings.dat");

// size for data descriptors
const TInt KBufSize = 100;

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * Construct the CConfigSettingItemList instance
 * @param aCommandObserver command observer
 */ 
CConfigSettingItemList::CConfigSettingItemList( 
		TConfigSettingItemListSettings& aSettings, 
		MEikCommandObserver* aCommandObserver )
	: iSettings( aSettings ), iCommandObserver( aCommandObserver )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
/** 
 * Destroy any instance variables
 */
CConfigSettingItemList::~CConfigSettingItemList()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Handle system notification that the container's size has changed.
 */
void CConfigSettingItemList::SizeChanged()
	{
	if ( ListBox() ) 
		{
		ListBox()->SetRect( Rect() );
		}
	}

/**
 * Create one setting item at a time, identified by id.
 * CAknSettingItemList calls this method and takes ownership
 * of the returned value.  The CAknSettingItem object owns
 * a reference to the underlying data, which EditItemL() uses
 * to edit and store the value.
 */
CAknSettingItem* CConfigSettingItemList::CreateSettingItemL( TInt aId )
	{
	switch ( aId )
		{
	// [[[ begin generated region: do not modify [Initializers]
		case EConfigSettingItemListViewApplication_password:
			{			
			CAknPasswordSettingItem* item = new ( ELeave ) 
				CAknPasswordSettingItem( 
					aId,
					CAknPasswordSettingItem::EAlpha,
					iSettings.Application_password() );
			return item;
			}
		case EConfigSettingItemListViewContactsPasswords:
			{			
			CAknBinaryPopupSettingItem* item = new ( ELeave ) 
				CAknBinaryPopupSettingItem( 
					aId,
					iSettings.ContactsPasswords() );
			return item;
			}
		case EConfigSettingItemListViewDelSentMessages:
			{			
			CAknBinaryPopupSettingItem* item = new ( ELeave ) 
				CAknBinaryPopupSettingItem( 
					aId,
					iSettings.DelSentMessages() );
			return item;
			}
		case EConfigSettingItemListViewDropInvalidGME:
			{			
			CAknBinaryPopupSettingItem* item = new ( ELeave ) 
				CAknBinaryPopupSettingItem( 
					aId,
					iSettings.DropInvalidGME() );
			return item;
			}
	// ]]] end generated region [Initializers]
	
		}
		
	return NULL;
	}
	
/**
 * Edit the setting item identified by the given id and store
 * the changes into the store.
 * @param aIndex the index of the setting item in SettingItemArray()
 * @param aCalledFromMenu true: a menu item invoked editing, thus
 *	always show the edit page and interactively edit the item;
 *	false: change the item in place if possible, else show the edit page
 */
void CConfigSettingItemList::EditItemL ( TInt aIndex, TBool aCalledFromMenu )
	{
	CAknSettingItem* item = ( *SettingItemArray() )[aIndex];
	switch ( item->Identifier() )
		{
	// [[[ begin generated region: do not modify [Editing Started Invoker]
	// ]]] end generated region [Editing Started Invoker]
	
		}
	
	CAknSettingItemList::EditItemL( aIndex, aCalledFromMenu );
	
	TBool storeValue = ETrue;
	switch ( item->Identifier() )
		{
	// [[[ begin generated region: do not modify [Editing Stopped Invoker]
	// ]]] end generated region [Editing Stopped Invoker]
	
		}
		
	if ( storeValue )
		{
		item->StoreL();
		SaveSettingValuesL();
		}	
	}
/**
 *	Handle the "Change" option on the Options menu.  This is an
 *	alternative to the Selection key that forces the settings page
 *	to come up rather than changing the value in place (if possible).
 */
void CConfigSettingItemList::ChangeSelectedItemL()
	{
	if ( ListBox()->CurrentItemIndex() >= 0 )
		{
		EditItemL( ListBox()->CurrentItemIndex(), ETrue );
		}
	}

/**
 *	Load the initial contents of the setting items.  By default,
 *	the setting items are populated with the default values from
 * 	the design.  You can override those values here.
 *	<p>
 *	Note: this call alone does not update the UI.  
 *	LoadSettingsL() must be called afterwards.
 */
void CConfigSettingItemList::LoadSettingValuesL()
	{
	// load values into iSettings
	RFs& fsSession = iEikonEnv->FsSession();
	TFileName settingsFile;
	User::LeaveIfError(fsSession.CreatePrivatePath(EDriveC));
	User::LeaveIfError(fsSession.PrivatePath(settingsFile));
	settingsFile += KSettingsFile;
	
	RFs& fs = iEikonEnv->FsSession();
	RFileReadStream readStream;
	TInt error = readStream.Open(fs, settingsFile, EFileRead);
	TInt internalizationError = KErrNone;
	// if file existed, try to read settings.
	if (error == KErrNone)
		{
		TRAP(internalizationError, DoLoadL(readStream);)
		}
	readStream.Release();
	
	// reading failed, settings file might be corrupted.    
	if (internalizationError != KErrNone)
		{
		User::LeaveIfError(fs.Delete(settingsFile));
		}
	}
	
void CConfigSettingItemList::DoLoadL(RFileReadStream& readStream)
	{
	TBuf<KBufSize> password;
	readStream >> password;
	TBool contactsPassword = readStream.ReadInt16L();
	TBool delSendMessages = readStream.ReadInt16L();
	TBool dropInvalidGME = readStream.ReadInt16L();
	iSettings.SetApplication_password(password);
	iSettings.SetContactsPasswords(contactsPassword);
	iSettings.SetDelSentMessages(delSendMessages);
	iSettings.SetDropInvalidGME(dropInvalidGME);
	}

/**
 *	Save the contents of the setting items.  Note, this is called
 *	whenever an item is changed and stored to the model, so it
 *	may be called multiple times or not at all.
 */
void CConfigSettingItemList::SaveSettingValuesL()
	{
	// store values from iSettings
	RFs& fsSession = iEikonEnv->FsSession();
	TFileName settingsFile;
	User::LeaveIfError(fsSession.CreatePrivatePath(EDriveC));
	User::LeaveIfError(fsSession.PrivatePath(settingsFile));
	settingsFile += KSettingsFile;
	
	RFs& fs = iEikonEnv->FsSession();
	RFileWriteStream writeStream;
	TInt error = writeStream.Open(fs, settingsFile, EFileWrite);
	// setting file did not exist, create one.
	if (error != KErrNone)
		{
		User::LeaveIfError(writeStream.Create(fs, settingsFile, EFileWrite));
		}
	writeStream.PushL();
	
	writeStream << iSettings.Application_password();
	writeStream.WriteInt16L(iSettings.ContactsPasswords());
	writeStream.WriteInt16L(iSettings.DelSentMessages());
	writeStream.WriteInt16L(iSettings.DropInvalidGME());
	
	writeStream.CommitL();
	writeStream.Pop();
	writeStream.Release();
	}


/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CConfigSettingItemList::HandleResourceChange( TInt aType )
	{
	CAknSettingItemList::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( EConfigSettingItemListViewId ) )->ClientRect() );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
				
/** 
 * Handle key event (override)
 * @param aKeyEvent key event
 * @param aType event code
 * @return EKeyWasConsumed if the event was handled, else EKeyWasNotConsumed
 */
TKeyResponse CConfigSettingItemList::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	if ( aKeyEvent.iCode == EKeyLeftArrow 
		|| aKeyEvent.iCode == EKeyRightArrow )
		{
		// allow the tab control to get the arrow keys
		return EKeyWasNotConsumed;
		}
	
	return CAknSettingItemList::OfferKeyEventL( aKeyEvent, aType );
	}
				

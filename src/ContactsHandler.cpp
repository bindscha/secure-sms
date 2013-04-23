/*
 ========================================================================
 Name        : ContactsHandler.cpp
 Author		 : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of contacts handler
 ========================================================================
 */
#include "ContactsHandler.h"

TDesC& CContactsHandler::ReadKeyLC(TDesC& phone)
	{
	HBufC* key = HBufC::NewLC(MAX_KEY_LENGTH);
	
	CContactDatabase* contactsDb = CContactDatabase::OpenL();
	CleanupStack::PushL(contactsDb);
	
	TBool done = EFalse;
	
	TContactIter iter(*contactsDb);
	TContactItemId itemId;
	while ((itemId = iter.NextL()) != KNullContactId && !done)
		{
		CContactItem* contactItem = contactsDb->ReadContactL(itemId);
		CleanupStack::PushL(contactItem);

		TInt phoneField = contactItem->CardFields().Find(KUidContactFieldPhoneNumber);
		TInt nameField = contactItem->CardFields().Find(KUidContactFieldFamilyName);
		if (phoneField != KErrNotFound)
			{
			TPtrC phoneText = contactItem->CardFields()[phoneField].TextStorage()->Text();
			TPtrC nameText = contactItem->CardFields()[nameField].TextStorage()->Text();
			if (phoneText == phone || nameText == phone)
				{
				TInt keyFieldIndex = contactItem->CardFields().Find(KUidContactFieldNote); 
					if(keyFieldIndex != KErrNotFound) 
					    {
					    CContactItemField& keyField = contactItem->CardFields()[keyFieldIndex];
					    TPtrC keyPtr = keyField.TextStorage()->Text();
					    key->Des().Append(keyPtr);
					    }
				done = ETrue;
				}
			}
		CleanupStack::PopAndDestroy(contactItem);
		}
	CleanupStack::PopAndDestroy(contactsDb);

	return *key;
	}

TBool CContactsHandler::WriteKeyL(TDesC& phone, TDesC& key)
	{
	CContactDatabase* contactsDb = CContactDatabase::OpenL(); // Connect to address book
	CleanupStack::PushL(contactsDb);

	TBool done = EFalse;
	
	TContactIter iter(*contactsDb); // Iterate over the contacts 
	TContactItemId itemId; 			// We are looking for a particular phone number 
	while ((itemId = iter.NextL()) != KNullContactId && !done)
		{
		CContactItem* contactItem = contactsDb->OpenContactLX(itemId);
		CleanupStack::PushL(contactItem);

		TInt phoneField = contactItem->CardFields().Find(KUidContactFieldPhoneNumber);
		TInt nameField = contactItem->CardFields().Find(KUidContactFieldFamilyName);
		if (phoneField != KErrNotFound && nameField != KErrNotFound)
			{
			TPtrC phoneText = contactItem->CardFields()[phoneField].TextStorage()->Text();
			TPtrC nameText = contactItem->CardFields()[nameField].TextStorage()->Text();
			if (phoneText == phone || nameText == phone) // Compare with the phone
				{
				TInt keyFieldIndex = contactItem->CardFields().Find(KUidContactFieldNote); 
				if(keyFieldIndex == KErrNotFound) 
				    { 
				    // The contact has no existing phone field, so add one. 
				    CContactItemField* addKeyField = CContactItemField::NewLC( 
				                            KStorageTypeText, KUidContactFieldNote);
				    addKeyField->SetMapping(KUidContactFieldVCardMapNOTE); 
				    addKeyField->TextStorage()->SetTextL(key); 
				    contactItem->AddFieldL(*addKeyField); // Takes ownership 
				    CleanupStack::Pop(addKeyField); 
				    } 
				else  
				    { 
				    // Modify the existing phone field’s contents. 
				    CContactItemField& keyField = contactItem->CardFields()[keyFieldIndex]; 
				    keyField.TextStorage()->SetTextL(key); 
				    }
				done = ETrue;
				contactsDb->CommitContactL(*contactItem);
				}
			}
		CleanupStack::PopAndDestroy(2);
		}
	CleanupStack::PopAndDestroy(contactsDb);
	
	return ETrue;
	}

/*
========================================================================
 Name        : SMSReceiver.cpp
 Author      : Laurent Bindschaedler
 Copyright   : Copyright (c) Laurent Bindschaedler 2009
 Description : Implementation of SMS receiver
========================================================================
*/

#include "SMSReceiver.h"
#include "ConfigSettingItemListView.h"
#include "ConfigSettingItemList.h"

CSMSReceiver* CSMSReceiver::NewL(MSMSRecCallBack* aSSMSObserver, MSMSRecCallBack* aKeyExchangeObserver)
	{
	CSMSReceiver* self = new (ELeave) CSMSReceiver(*aSSMSObserver, *aKeyExchangeObserver);
	self->ConstructL();
	return self;
	}

CSMSReceiver::CSMSReceiver(MSMSRecCallBack& aSSMSObserver, MSMSRecCallBack& aKeyExchangeObserver) :
	iSSMSObserver(aSSMSObserver), iKeyExchangeObserver(aKeyExchangeObserver)
	{
	}

CSMSReceiver::~CSMSReceiver()
	{
	delete iSmsMtm;
	iSmsMtm = NULL;
	
	delete iMtmRegistry;
	iMtmRegistry = NULL;

	delete iSession;
	iSession = NULL;
	}

void CSMSReceiver::ConstructL(void)
	{
	iSession = CMsvSession::OpenSyncL(*this);
	iMtmRegistry = CClientMtmRegistry::NewL(*iSession);
	iSmsMtm = iMtmRegistry->NewMtmL(KUidMsgTypeSMS);
	}

void CSMSReceiver::HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1,
		TAny* aArg2, TAny* /*aArg3*/)
	{
	switch (aEvent)
		{
		case EMsvEntriesChanged:
			{

			}
			break;
		case EMsvEntriesCreated:
		case EMsvEntriesMoved:
			{
			TMsvId* entryId;
			entryId = static_cast<TMsvId*> (aArg2); // entry id from the session event

			if (*entryId == KMsvGlobalInBoxIndexEntryId) // new entry has been created in Inbox folder
				{
				TMsvSelectionOrdering sort;
				sort.SetShowInvisibleEntries(EFalse); // we dont want to handle the invisible entries
				// Take a handle to the Inbox entry
				CMsvEntry* parentEntry = CMsvEntry::NewL(*iSession,
						KMsvGlobalInBoxIndexEntryId, sort);
				CleanupStack::PushL(parentEntry);

				CMsvEntrySelection* entries =
						static_cast<CMsvEntrySelection*> (aArg1);
				if (entries)
					{
					//Process each created entry, one at a time.
					for (TInt i = 0; i < entries->Count(); i++)
						{
						HandleEntryL(entries->At(i));
						}
					}

				CleanupStack::PopAndDestroy(1); //  parentEntry
				}
			else if (*entryId == KMsvSentEntryId)
				{
				TMsvSelectionOrdering selection;
				CMsvEntry* parentEntry = CMsvEntry::NewL( iSmsMtm->Session(), KMsvSentEntryId, selection );
				CleanupStack::PushL( parentEntry );              
				            
				TConfigSettingItemListSettings* settings2 = TConfigSettingItemListSettings::NewL();
				CConfigSettingItemList * configSettingItemList = new (ELeave) CConfigSettingItemList(*settings2, NULL);
				CleanupStack::PushL(settings2);
				CleanupStack::PushL(configSettingItemList);
				configSettingItemList->LoadSettingValuesL();
				if (settings2->DelSentMessages())
					{
					CMsvEntrySelection* entries =
							static_cast<CMsvEntrySelection*> (aArg1);
					if (entries)
						{
						//Process each created entry, one at a time.
						for (TInt i = 0; i < entries->Count(); i++)
							{
							// Delete message
							parentEntry->DeleteL(entries->At(i));
							}
						}
					
					}
				
				CleanupStack::PopAndDestroy(configSettingItemList);
				CleanupStack::PopAndDestroy(settings2);

				CleanupStack::PopAndDestroy(parentEntry);
				}
			}
			break;
		case EMsvCloseSession:
			iSession->CloseMessageServer();
			break;
		default:
			// All other events are ignored
			break;
		}

	}

void CSMSReceiver::HandleEntryL(TMsvId& aEntId)
	{
	CMsvEntry* entry = iSession->GetEntryL(aEntId);
	CleanupStack::PushL(entry);

	if (entry->Entry().iMtm == KUidMsgTypeSMS)
		{
		CBaseMtm* SmsMtm = iMtmRegistry->NewMtmL(KUidMsgTypeSMS);
		if (SmsMtm)
			{
			CleanupStack::Pop(1);//entry
			CleanupStack::PushL(SmsMtm);
			SmsMtm->SetCurrentEntryL(entry);
			SmsMtm->LoadMessageL();

			HBufC* BodyBuffer = HBufC::NewLC(SmsMtm->Body().DocumentLength());
			TPtr BodyPoint(BodyBuffer->Des());

			SmsMtm->Body().Extract(BodyPoint, 0,
					SmsMtm->Body().DocumentLength());

			if (CGMEMessage::IsGME(*BodyBuffer))
				{
				if (CGMEMessage::IsValidGME(*BodyBuffer))
					{
					if (CGMEMessage::ProtocolType(*BodyBuffer) == SECURE_SMS)
						{
						if (!CheckIfFolderExistsL())
							CreateFolderL();
						entry->MoveL(aEntId, iNewFolderId);
						iSSMSObserver.RecSMSMessageL(*BodyBuffer);
						}
					else if (CGMEMessage::ProtocolType(*BodyBuffer) == KEY_EXCHANGE_SMS)
						{
						entry->DeleteL(aEntId);
						iKeyExchangeObserver.RecSMSMessageL(*BodyBuffer);
						}
					}
				else
					{
					TConfigSettingItemListSettings* settings = TConfigSettingItemListSettings::NewL();
					CConfigSettingItemList * configSettingItemList = new (ELeave) CConfigSettingItemList(*settings, NULL);
					CleanupStack::PushL(settings);
					CleanupStack::PushL(configSettingItemList);
					configSettingItemList->LoadSettingValuesL();
					if(settings->DropInvalidGME())
						{
						entry->DeleteL(aEntId);
						}
					CleanupStack::PopAndDestroy(configSettingItemList);
					CleanupStack::PopAndDestroy(settings);
					}
				}

			CleanupStack::PopAndDestroy(2);//SmsMtm,BodyBuffer		
			}
		else
			{
			CleanupStack::PopAndDestroy(1);//entry
			}
		}
	else
		{
		CleanupStack::PopAndDestroy(1);//entry
		}
	}

TBool CSMSReceiver::CheckIfFolderExistsL()
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

TBool CSMSReceiver::CreateFolderL()
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

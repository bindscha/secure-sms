// MSVIDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//
// Modified by Laurent Bindschaedler - April 2009

#if !defined(__MSVIDS_H__)
#define __MSVIDS_H__
#if !defined(__MSVSTD_HRH__)
#include "msvstd.hrh"
#endif
#if !defined(__MSVSTD_H__)
#include "msvstd.h"
#endif

#define KMsvMyFoldersEntryIdValue 			0x1008 // TODO: this should not be here but the preprocessor fucks up bad...
// Predefined entry ids - values #defined in MSVSTD.HRH
/** A NULL ID. 

This is typically used to indicate that the ID has not yet been set. It can 
also be used to "park" a CMsvServerEntry so that it doesn't lock an index 
entry. */
const TMsvId KMsvNullIndexEntryId=KMsvNullIndexEntryIdValue;//0
const TMsvId KMsvTempIndexEntryId=KMsvTempIndexEntryIdValue;//1
/** ID of root entry of entire index */
const TMsvId KMsvRootIndexEntryId=KMsvRootIndexEntryIdValue;//0x1000
/** ID of local service (containing the standard folders) */
const TMsvId KMsvLocalServiceIndexEntryId=KMsvLocalServiceIndexEntryIdValue;//0x1001
/** ID of Inbox folder */
const TMsvId KMsvGlobalInBoxIndexEntryId=KMsvGlobalInBoxIndexEntryIdValue;//0x1002
/** ID of Outbox folder */
const TMsvId KMsvGlobalOutBoxIndexEntryId=KMsvGlobalOutBoxIndexEntryIdValue;//0x1003
/** ID of Draft folder */
const TMsvId KMsvDraftEntryId=KMsvDraftEntryIdValue; //0x1004
/** ID of Sent folder */
const TMsvId KMsvSentEntryId=KMsvSentEntryIdValue; //0x1005
const TMsvId KMsvDeletedEntryFolderEntryId=KMsvDeletedEntryFolderEntryIdValue;//0x1006
const TMsvId KMsvUnknownServiceIndexEntryId=KMsvUnkownServiceIndexEntryIdValue; //0x1007
const TMsvId KMsvMyFoldersEntryId=KMsvMyFoldersEntryIdValue;
const TMsvId KFirstFreeEntryId=0x100000;

#endif

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_DB_H__
#define __PALM_DB_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmDB
// ----- ------
class __DECLSPEC__ PalmDB
{
    private:
     DmOpenRef      Handle;
    public:
     // ctor/dtor
                    PalmDB();
     virtual       ~PalmDB();

     // access
     DmOpenRef      GetHandle() const;

     // operators
                    operator DmOpenRef ();

     // api
     Err            Init();

     // db
     Err            CreateDatabase(const char*, uint32 creator, uint32, bool = false, uint16 = 0);
     Err            CreateDatabaseFromImage(MemPtr);
     Err            DeleteDatabase(LocalID, uint16 = 0);

     void           OpenDatabase(LocalID, uint16, uint16 = 0);
     void           OpenDatabaseByTypeCreator(uint32, uint32, uint16);
     void           OpenDBNoOverlay(LocalID, uint16, uint16 = 0);
     Err            CloseDatabase();

     uint16         GetNumDatabases(uint16 = 0);
     LocalID        GetDatabase(uint16);
     LocalID        FindDatabase(const char*, uint16 = 0);
     Err            GetNextDatabaseByTypeCreator(bool, DmSearchStateType&, uint32, uint32, bool, uint16&, LocalID&);

     Err            GetDatabaseInfo(LocalID, char*, uint16&, uint16&, uint32&, uint32&, uint32&, uint32&, LocalID&, LocalID&, uint32&, uint32&, uint16 = 0);
     Err            SetDatabaseInfo(LocalID, const char*, uint16&, uint16&, uint32&, uint32&, uint32&, uint32&, LocalID&, LocalID&, uint32&, uint32&, uint16 = 0);

     Err            GetDatabaseSize(LocalID, uint32, uint32&, uint32&, uint16 = 0);

     Err            DatabaseProtect(LocalID, bool = true, uint16 = 0);

     static DmOpenRef
                    NextOpenDatabase(DmOpenRef);

     Err            OpenDatabaseInfo(LocalID&, uint16&, uint16&, uint16&, bool&);
     LocalID        GetAppInfoID();

     void           GetDatabaseLockState(uint8&, uint32&, uint32&);
     Err            ResetRecordStates();

     Err            GetLastErr();

     // record
     uint16         GetNumRecords();
     uint16	        GetNumRecordsInCategory(uint16);

     Err            RecordInfo(uint16, uint16&, uint32&, LocalID&);
     Err            SetRecordInfo(uint16, uint16&, uint32&);

     Err            AttachRecord(uint16&, MemHandle, MemHandle&);
     Err            DetachRecord(uint16, MemHandle&);

     Err            MoveRecord(uint16, uint16);

     MemHandle      NewRecord(uint16&, uint32);
     Err            RemoveRecord(uint16);
     Err            DeleteRecord(uint16);
     Err            ArchiveRecord(uint16);
     MemHandle      NewHandle(uint32);

     Err            RemoveSecretRecords();

     Err            FindRecordByID(uint32, uint16&);
     MemHandle      QueryRecord(uint16);
     MemHandle      GetRecord(uint16);
     MemHandle      QueryNextInCategory(uint16&, uint16);
     uint16         PositionInCategory(uint16, uint16);
     Err            SeekRecordInCategory(uint16&, uint16, int16, uint16);
     MemHandle      ResizeRecord(uint16, uint32);
     Err            ReleaseRecord(uint16, bool);

     static uint16  SearchRecord(MemHandle, DmOpenRef&);

     Err            MoveCategory(uint16, uint16, bool);
     Err            DeleteCategory(uint16);

     Err            WriteCheck(void*, uint32, uint32);
     Err            Write(void*, uint32, const void*, uint32);
     Err            StrCopy(void*, uint32, const char*);
     Err            Set(void*, uint32, uint32, uint8);

     // resource
     MemHandle      GetResource(DmResType, DmResID);
     MemHandle      Get1Resource(DmResType, DmResID);
     Err            ReleaseResource(MemHandle);
     MemHandle      ResizeResource(MemHandle, uint32);

     static DmOpenRef
                    DmNextOpenResDatabase(DmOpenRef);
     uint16         FindResourceType(DmResType, uint16);
     uint16         FindResource(DmResType, DmResID, MemHandle);

     static uint16  SearchResource(DmResType, DmResID, MemHandle, DmOpenRef&);

     uint16         GetNumResources();
     Err            GetResourceInfo(uint16, DmResType&, DmResID&, LocalID&);
     Err            SetResourceInfo(uint16, DmResType&, DmResID&);

     Err            AttachResource(MemHandle, DmResType, DmResID);
     Err            DetachResource(uint16, MemHandle&);

     MemHandle      NewResource(DmResType, DmResID, uint32);
     Err            RemoveResource(uint16);

     MemHandle		DmGetResourceIndex(uint16);

     Err            QuickSort(DmComparF*, int16);
     Err            InsertionSort(DmComparF*, int16);

     uint16         FindSortPosition(void*, SortRecordInfoType&, DmComparF*, int16);
     uint16         FindSortPositionV10(void*, DmComparF*, int16);

    public:

    class __DECLSPEC__ XPalmDB : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'pldb'
        };

        public: 
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmDB;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_DB_H__


////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_VFS_H__
#define __PALM_VFS_H__

#if (__PALM_OS__ >= 0x0400)

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmVFS
// ----- -------
class __DECLSPEC__ PalmVFS
{
    public:

    class __DECLSPEC__ File
    {
        private:
         FileRef    Ref;
        public:
         // ctor/dtor
                    File();
                   ~File();

         // access
         FileRef    GetRef()    const;

         // operators
                    operator FileRef ();

         // api
         // file
         static Err Create(const char*);
         static Err Delete(const char*);
         static Err Rename(const char*, const char*);

         Err        Open(const char*, uint16);
         Err        Close();

         Err        ReadData(uint32, void*, uint32, uint32&);
         Err        Read(uint32, void*, uint32&);
         Err        Write(uint32, const void*, uint32&);

         Err        Seek(FileOrigin, int32);
         Err        IsEOF();

         Err        Tell(uint32&);
         Err        Size(uint32&);
         Err        Resize(uint32);

#if (__PALM_OS__ >= 0x0400)
         Err        GetAttributes(uint32&);
         Err        SetAttributes(uint32);

         Err        GetDate(uint16, uint32&);
         Err        SetDate(uint16, uint32);
#endif

         // dir
         Err        DirEntryEnumerate(uint32&, FileInfoType&);

         static Err DirCreate(const char*);

#if (__PALM_OS__ >= 0x0400)
         static Err GetDefaultDirectory(const char*, char*, uint16&);

         static Err RegisterDefaultDirectory(const char*, uint32, const char*);
         static Err UnregisterDefaultDirectory(const char*, uint32);
#endif

         // db
         Err        DBGetResource(DmResType, DmResID, MemHandle&);
         Err        DBInfo(char*, uint16&, uint16&, uint32&, uint32&, uint32&, uint32&, MemHandle&, MemHandle&, uint32&, uint32&, uint16&);

         Err        DBGetRecord(uint16, MemHandle&, uint8&, uint32&);
    };

    class __DECLSPEC__ Volume
    {
        public:
         static uint16  GetRefNumber();

         // api
         static Err     Info(VolumeInfoType&);

         static Err     Enumerate(uint16&, uint32&);

#if (__PALM_OS__ >= 0x0400)
         static Err     GetLabel(char*, uint16);
         static Err     SetLabel(const char*);
#endif
         static Err     Size(uint32&, uint32&);

         static Err     Format(uint8, uint16, VFSAnyMountParamType&);

         static Err     Mount(uint8, uint16, VFSAnyMountParamType&);
         static Err     Unmount();
    };

    public:
     // ctor/dtor
                    PalmVFS();
                   ~PalmVFS();

     // api
     static Err     Init();
     static Err     CustomControl(uint32, uint32, uint16, void*, uint16&);

     // fslib
     Err            InstallFSLib(uint32, uint16&);
     Err            RemoveFSLib(uint16);

    public:

    class __DECLSPEC__ XPalmVFS : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'pvfs'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmVFS;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif
#endif // __PALM_VFS_H__


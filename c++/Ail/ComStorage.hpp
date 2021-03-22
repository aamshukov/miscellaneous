////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COM_STORAGE_H__
#define __COM_STORAGE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComStorage
// ----- ----------
class __DECLSPEC__ ComStorage
{
    typedef Synchronization::ThreadMutex<> _Mutex;

    public:

    //////////////////
    // class ComStream
    // ----- ---------
    class __DECLSPEC__ ComStream
    {
        private:
        _Mutex      Mutex;
         IStream*   Stream;
        protected:
         // internal
         HRESULT    Clone(IStream**);
        public:
         // ctor/dtor
                    ComStream(ComStorage&, const wchar*, bool = true, ulong = STGM_READWRITE);
                    ComStream(ComStream&);
                    ComStream(IStream*);
                   ~ComStream();

         // access
         IStream*   GetInstance()   const;

         // methods
         HRESULT    Read(void*, ulong, ulong* = null);
         HRESULT    Write(const void*, ulong, ulong* = null);
         HRESULT    Seek(LARGE_INTEGER, ulong = STREAM_SEEK_SET, ULARGE_INTEGER* = null);

         HRESULT    LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, ulong);
         HRESULT    UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, ulong);

         HRESULT    Commit(ulong);
         HRESULT    Revert();

         HRESULT    SetSize(ULARGE_INTEGER);
         HRESULT    CopyTo(ComStream&, ULARGE_INTEGER, ULARGE_INTEGER* = null, ULARGE_INTEGER* = null);
         HRESULT    Stat(STATSTG*, ulong);
    };

    friend class ComStream;

    private:
    _Mutex          Mutex;
     IStorage*      Storage;
    protected:
     // internal
     HRESULT        CreateStream(const wchar*, ulong, ulong, ulong, IStream**);
     HRESULT        OpenStream(const wchar*, void*, ulong, ulong, IStream**);

     HRESULT        CreateStorage(const wchar*, ulong, ulong, ulong, IStorage**);
     HRESULT        OpenStorage(const wchar*, IStorage*, ulong, SNB, ulong, IStorage**);

     ulong          AddRef();
     ulong          Release();
    public:
     // ctor/dtor
                    ComStorage(const wchar*, bool = true, ulong = STGM_READWRITE);
                    ComStorage(ILockBytes*, bool = true, ulong = STGM_READWRITE);
                    ComStorage(ComStorage&, const wchar*, bool = true, ulong = STGM_READWRITE);
                    ComStorage(IStorage*);
                   ~ComStorage();

     // access
     IStorage*      GetInstance()   const;

     // methods
     HRESULT        CopyTo(ulong, const IID*, SNB, ComStorage&);
     HRESULT        MoveElementTo(const wchar*, ComStorage&, const wchar*, ulong);
     HRESULT        EnumElements(ulong, void*, ulong, IEnumSTATSTG**);
     HRESULT        DestroyElement(const wchar*);
     HRESULT        RenameElement(const wchar*, const wchar*);

     HRESULT        SetElementTimes(const wchar*, const FILETIME*, const FILETIME*, const FILETIME*);
     HRESULT        SetClass(const IID&);

     HRESULT        Commit(ulong);
     HRESULT        Revert();

     HRESULT        Stat(STATSTG*, ulong);
     HRESULT        SetStateBits(ulong, ulong);

     HRESULT        SwitchToFile(const wchar*);

     static HRESULT IsStorageFile(const wchar*);
     static HRESULT IsStorageILockBytes(ILockBytes*);

     static HRESULT SetTimes(const wchar*, const FILETIME*, const FILETIME*, const FILETIME*);
};
////////////////////////////////////////////////////////////////////////////////////////
// class XStorage
// ----- --------
class __DECLSPEC__ XStorage : public XCOM
{
    public:

    enum EError
    {
        CreateStream  = 0x00000010,
        CreateStorage = 0x00000010,
    };

    public:
     // ctor/dtor
                  XStorage(HRESULT = 0, uint = X::Failure);

     // methods
     static void  xxassert(int, HRESULT = 0, uint = X::Failure);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COM_STORAGE_H__

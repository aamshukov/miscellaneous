////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __COM_STORAGE_INC__
#   include <ComStorage.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComStream
// ----- ---------
ComStorage::ComStream::ComStream(ComStorage& _storage, const wchar* _name, bool _create, ulong _mode)
{
    // Make sure that the transacted mode is off since streams don't support
    // this mode. Also make sure that the stream is opened in exclusive mode.
   _mode &= ~STGM_TRANSACTED;
   _mode |=  STGM_SHARE_EXCLUSIVE;

    HRESULT hr;

    if(_create)
    {
       _mode |= STGM_CREATE;
        hr = _storage.CreateStream(_name, _mode, 0, 0, &Stream);
    }
    else
    {
        hr = _storage.OpenStream(_name, 0, _mode, 0, &Stream);
    }

    XStorage::xxassert(SUCCEEDED(hr) && Stream != 0, hr, XStorage::CreateStream);
}

ComStorage::ComStream::ComStream(ComStorage::ComStream& _other)
{
    if(this != &_other)
    {
        _other.Clone(&Stream);
    }
}

ComStorage::ComStream::ComStream(IStream* _stream)
{
    Synchronization::Guard<Synchronization::ThreadMutex<> > guard(Mutex);
    //
    Stream = _stream;
}

ComStorage::ComStream::~ComStream()
{
    Synchronization::Guard<Synchronization::ThreadMutex<> > guard(Mutex);
    //
    if(Stream != null)
    {
        Stream->Release();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class ComStorage
// ----- ----------
ComStorage::ComStorage(const wchar* _name, bool _create, ulong _mode)
{
    // Fill in the sharing mode based on the access
    if((_mode & STGM_WRITE) || (_mode & STGM_READWRITE))
    {
        _mode |= STGM_SHARE_EXCLUSIVE;
    }
    else
    {
        _mode |= STGM_SHARE_DENY_NONE;
    }

    HRESULT hr;

    if(_create)
    {
        _mode |= STGM_CREATE;

        if(_name == null)
        {
            _mode |= STGM_DELETEONRELEASE;
        }

        hr = ::StgCreateDocfile(_name, _mode, 0, &Storage);
    }
    else
    {
        hr = ::StgOpenStorage(_name, 0, _mode, 0, 0, &Storage);
    }

    XStorage::xxassert(SUCCEEDED(hr) && Storage != 0, hr, XStorage::CreateStorage);
}

ComStorage::ComStorage(ILockBytes* _lock_byte, bool _create, ulong _mode)
{
    __x_assert__(_lock_byte != 0);

    // Fill in the sharing mode based on the access
    if((_mode & STGM_WRITE) || (_mode & STGM_READWRITE))
    {
        _mode |= STGM_SHARE_DENY_WRITE;
    }
    else
    {
        _mode |= STGM_SHARE_DENY_NONE;
    }

    HRESULT hr;

    if(_create)
    {
        _mode |= STGM_CREATE;
        
        hr = ::StgCreateDocfileOnILockBytes(_lock_byte, _mode, 0, &Storage);
    }
    else
    {
        hr = ::StgOpenStorageOnILockBytes(_lock_byte, 0, _mode, 0, 0, &Storage);
    }

    XStorage::xxassert(SUCCEEDED(hr) && Storage != 0, hr, XStorage::CreateStorage);
}

ComStorage::ComStorage(ComStorage& _parent, const wchar* _name, bool _create, ulong _mode)
{
    __x_assert__(_name != 0);

    _mode |= STGM_SHARE_EXCLUSIVE;

    HRESULT hr = _parent.OpenStorage(_name, 0, _mode, 0, 0, &Storage);

    if(Storage == null && _create)
    {
        hr = _parent.CreateStorage(_name, _mode, 0, 0, &Storage);
    }

    XStorage::xxassert(SUCCEEDED(hr) && Storage != 0, hr, XStorage::CreateStorage);
}

ComStorage::ComStorage(IStorage* _storage)
{
    Synchronization::Guard<Synchronization::ThreadMutex<> > guard(Mutex);
    //
    Storage = _storage;
}

ComStorage::~ComStorage()
{
    Synchronization::Guard<Synchronization::ThreadMutex<> > guard(Mutex);
    //
    if(Storage != null)
    {
        Storage->Release(), Storage = null;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class XStorage
// ----- --------
XStorage::XStorage(HRESULT _hr, uint _error) : XCOM(_hr, _error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

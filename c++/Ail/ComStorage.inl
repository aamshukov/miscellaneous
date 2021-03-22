////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COM_STORAGE_INL__
#define __COM_STORAGE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComStream
// ----- ---------
__INLINE__ IStream* ComStorage::ComStream::GetInstance() const
{
    return Stream;
}

__INLINE__ ULONG ComStorage::AddRef()
{
    return Storage != null ? Storage->AddRef() : 0;
}

__INLINE__ ULONG ComStorage::Release()
{
    return Storage != null ? Storage->Release() : 0;
}

__INLINE__ HRESULT ComStorage::ComStream::Read(void* _buffer, ulong _count, ulong* _read)
{
    __x_assert__(Stream != 0 && _buffer != 0);
    return Stream->Read(_buffer, _count, _read);
}

__INLINE__ HRESULT ComStorage::ComStream::Write(const void* _buffer, ulong _count, ulong* _written)
{
    __x_assert__(Stream != 0 && _buffer != 0);
    return Stream->Write(_buffer, _count, _written);
}

__INLINE__ HRESULT ComStorage::ComStream::Seek(LARGE_INTEGER _move, ulong _origin, ULARGE_INTEGER* _new_pos)
{
    __x_assert__(Stream != 0 && _new_pos != 0);
    return Stream->Seek(_move, _origin, _new_pos);
}

__INLINE__ HRESULT ComStorage::ComStream::LockRegion(ULARGE_INTEGER _offset, ULARGE_INTEGER _count, ulong _type)
{
    __x_assert__(Stream != 0);
    return Stream->LockRegion(_offset, _count, _type);
}

__INLINE__ HRESULT ComStorage::ComStream::UnlockRegion(ULARGE_INTEGER _offset, ULARGE_INTEGER _count, ulong _type)
{
    __x_assert__(Stream != 0);
    return Stream->UnlockRegion(_offset, _count, _type);
}

__INLINE__ HRESULT ComStorage::ComStream::Commit(ulong _flags)
{
    __x_assert__(Stream != 0);
    return Stream->Commit(_flags);
}

__INLINE__ HRESULT ComStorage::ComStream::Revert()
{
    __x_assert__(Stream != 0);
    return Stream->Revert();
}

__INLINE__ HRESULT ComStorage::ComStream::SetSize(ULARGE_INTEGER _new_size)
{
    __x_assert__(Stream != 0);
    return Stream->SetSize(_new_size);
}

__INLINE__ HRESULT ComStorage::ComStream::CopyTo(ComStorage::ComStream& _stream, ULARGE_INTEGER _count, ULARGE_INTEGER* _read, ULARGE_INTEGER* _written)
{
    __x_assert__(Stream != 0);
    return Stream->CopyTo(_stream.GetInstance(), _count, _read, _written);
}

__INLINE__ HRESULT ComStorage::ComStream::Stat(STATSTG* _statstg, ulong _flags)
{
    __x_assert__(Stream != 0 && _statstg != 0);
    return Stream->Stat(_statstg, _flags);
}

__INLINE__ HRESULT ComStorage::ComStream::Clone(IStream** _stream)
{
    __x_assert__(Stream != 0 && _stream != 0);
    return Stream->Clone(_stream);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ComStorage
// ----- ----------
__INLINE__ IStorage* ComStorage::GetInstance() const
{
    return Storage;
}

__INLINE__ HRESULT ComStorage::CreateStream(const wchar* _name, ulong _mode, ulong _rsrvd1, ulong _rsrvd2, IStream** _stream)
{
    __x_assert__(Storage != 0 && _name != 0 && _stream != 0);
    return Storage->CreateStream(_name, _mode, _rsrvd1, _rsrvd2, _stream);
}

__INLINE__ HRESULT ComStorage::OpenStream(const wchar* _name, void* _rsrvd1, ulong _mode, ulong _rsrvd2, IStream** _stream)
{
    __x_assert__(Storage != 0 && _name != 0 && _stream != 0);
    return Storage->OpenStream(_name, _rsrvd1, _mode, _rsrvd2, _stream);
}

__INLINE__ HRESULT ComStorage::CreateStorage(const wchar* _name, ulong _mode, ulong _rsrvd1, ulong _rsrvd2, IStorage** _storage)
{
    __x_assert__(Storage != 0 && _name != 0 && _storage != 0);
    return Storage->CreateStorage(_name, _mode, _rsrvd1, _rsrvd2, _storage);
}

__INLINE__ HRESULT ComStorage::OpenStorage(const wchar* _name, IStorage* _priority, ulong _mode, SNB _snb_exclude, ulong _rsrvd, IStorage** _storage)
{
    __x_assert__(Storage != 0 && _name != 0 && _storage != 0);
    return Storage->OpenStorage(_name, _priority, _mode, _snb_exclude, _rsrvd, _storage);
}

__INLINE__ HRESULT ComStorage::CopyTo(ulong _ciid_exclude, const IID* _rgiid_exclude, SNB _snb_exclude, ComStorage& _dest)
{
    __x_assert__(Storage != 0);
    return Storage->CopyTo(_ciid_exclude, _rgiid_exclude, _snb_exclude, _dest.GetInstance());
}

__INLINE__ HRESULT ComStorage::MoveElementTo(const wchar* _name, ComStorage& _dest, const wchar* _new_name, ulong _flags)
{
    __x_assert__(Storage != 0 && _name != 0 && _new_name != 0);
    return Storage->MoveElementTo(_name, _dest.GetInstance(), _new_name, _flags);
}

__INLINE__ HRESULT ComStorage::EnumElements(ulong _rsrvd1, void* _rsrvd2, ulong _rsrvd3, IEnumSTATSTG** _enum)
{
    __x_assert__(Storage != 0 && _enum != 0);
    return Storage->EnumElements(_rsrvd1, _rsrvd2, _rsrvd3, _enum);
}

__INLINE__ HRESULT ComStorage::DestroyElement(const wchar* _name)
{
    __x_assert__(Storage != 0 && _name != 0);
    return Storage->DestroyElement(_name);
}

__INLINE__ HRESULT ComStorage::RenameElement(const wchar* _name, const wchar* _new_name)
{
    __x_assert__(Storage != 0 && _name != 0 && _new_name != 0);
    return Storage->RenameElement(_name, _new_name);
}

__INLINE__ HRESULT ComStorage::SetElementTimes(const wchar* _name, const FILETIME* _ctime, const FILETIME* _atime, const FILETIME* _mtime)
{
    __x_assert__(Storage != 0);
    return Storage->SetElementTimes(_name, _ctime, _atime, _mtime);
}

__INLINE__ HRESULT ComStorage::SetClass(const IID& _clsid)
{
    __x_assert__(Storage != 0);
    return Storage->SetClass(_clsid);
}

__INLINE__ HRESULT ComStorage::Commit(ulong _flags)
{
    __x_assert__(Storage != 0);
    return Storage->Commit(_flags);
}

__INLINE__ HRESULT ComStorage::Revert()
{
    __x_assert__(Storage != 0);
    return Storage->Revert();
}

__INLINE__ HRESULT ComStorage::Stat(STATSTG* _statstg, ulong _flags)
{
    __x_assert__(Storage != 0 && _statstg != 0);
    return Storage->Stat(_statstg, _flags);
}

__INLINE__ HRESULT ComStorage::SetStateBits(ulong _bits, ulong _mask)
{
    __x_assert__(Storage != 0);
    return Storage->SetStateBits(_bits, _mask);
}

__INLINE__ HRESULT ComStorage::SwitchToFile(const wchar* _path)
{
    __x_assert__(Storage != 0 && _path != 0);

    IRootStorage* root_storage;

    HRESULT hr = Storage->QueryInterface(IID_IRootStorage, reinterpret_cast<void**>(&root_storage));

    if(SUCCEEDED(hr))
    {
        hr = root_storage->SwitchToFile(const_cast<wchar*>(_path));
        root_storage->Release();
    }

    return hr;
}

__INLINE__ HRESULT ComStorage::IsStorageFile(const wchar* _name)
{
    return ::StgIsStorageFile(_name);
}

__INLINE__ HRESULT ComStorage::IsStorageILockBytes(ILockBytes* _lock_byte)
{
    return ::StgIsStorageILockBytes(_lock_byte);
}

__INLINE__ HRESULT ComStorage::SetTimes(const wchar* _name, const FILETIME* _ctime, const FILETIME* _atime, const FILETIME* _mtime)
{
    return ::StgSetTimes(_name, _ctime, _atime, _mtime);
}
////////////////////////////////////////////////////////////////////////////////////////
// class XStorage
// ----- --------
__INLINE__ void XStorage::xxassert(int _expr, HRESULT _hr, uint _error)
{
    if(_expr == 0)
    {
        throw XStorage(_hr, _error);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COM_STORAGE_INL__

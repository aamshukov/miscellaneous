////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MEDIA_MANAGER_INL__
#define __MEDIA_MANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MediaManager
// ----- ------------
template <typename _Media, typename _Mutex> ushort MediaManager<_Media, _Mutex>::ConstMagicNumber = 1967;
template <typename _Media, typename _Mutex> ushort MediaManager<_Media, _Mutex>::ConstVersion     = 0100;
template <typename _Media, typename _Mutex> const tchar* MediaManager<_Media, _Mutex>::ConstSignature = _t("UI Soft, AA");
//
template <typename _Media, typename _Mutex>
MediaManager<_Media, _Mutex>::MediaManager(uint32 _flags, const tchar* _mutex_name, uint _timeout) : Flags(_flags), Mutex(_mutex_name, _timeout)
{
}

template <typename _Media, typename _Mutex>
MediaManager<_Media, _Mutex>::~MediaManager()
{
    Close();
}
//
template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::AdjustPointer(fpos_t_ _new_pos)
{
    if(_new_pos != -1)
    {
        Media.SetPosition(Header.OffsetToData+_new_pos);
    }
    else
    {
        fpos_t_ pos;

        Media.GetPosition(pos);

        if(pos < Header.OffsetToData)
        {
            Media.SetPosition(Header.OffsetToData);
        }
    }
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::xxassert(int _expr, uint _error)
{
    if(_expr == 0)
    {
        throw XMediaManager(_error);
    }
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::InitHeader()
{
    Header.MagicNumber = ConstMagicNumber;
    memcpy(Header.Signature, MediaManager::ConstSignature, sizeof(Header.Signature));

    Header.Version = MediaManager::ConstVersion;

    OSVERSIONINFO info;
    info.dwOSVersionInfoSize = sizeof(info);

    ::GetVersionEx(&info);

    if(info.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
        if(info.dwMinorVersion == 0)
        {
            Header.OS = MediaManager::Windows95;
        }
        else
        {
            Header.OS = MediaManager::Windows98;
        }

        Header.ByteOrder = MediaManager::LittleEndian;
    }
    else if(info.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        Header.OS = MediaManager::WindowsNT;
        Header.ByteOrder = MediaManager::LittleEndian;
    }
    else
    {
        Header.OS = MediaManager::Unknown;
    }

   _snprintf(reinterpret_cast<tchar*>(Header.DescOS), sizeof(Header.DescOS), _t("%04d.%04d.%04ld.%04ld %s"), info.dwMajorVersion, info.dwMinorVersion, info.dwBuildNumber, info.dwPlatformId, info.szCSDVersion);

    Header.LanguageId     = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
    Header.CreationTime   =
    Header.LastAccessTime =
    Header.LastWriteTime  = Time::GetCurrentTime().GetTime();
    Header.OffsetToData   = sizeof(Header);

    memcpy(Header.Signature, MediaManager::ConstSignature, sizeof(Header.Signature));
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::ReadHeader()
{
    MediaLock<_Media> lock(Media, 0, sizeof(Header));
    MediaPos<_Media>  pos(Media, 0);

    xxassert(Media.Read(&Header, sizeof(Header)) == sizeof(Header) && Header.MagicNumber == MediaManager::ConstMagicNumber && memcmp(Header.Signature, MediaManager::ConstSignature, sizeof(Header.Signature)) == 0, XMediaManager::InvalidHeader);
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::WriteHeader()
{
    MediaLock<_Media> lock(Media, 0, sizeof(Header));
    MediaPos<_Media>  pos(Media, 0);

    xxassert(Media.Write(&Header, sizeof(Header)) == sizeof(Header), X::Failure);
    Media.FlushBuffers();
}
//
template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ const _Media& MediaManager<_Media, _Mutex>::GetMedia() const
{
    return Media;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ const MediaManager<_Media, _Mutex>::_Header& MediaManager<_Media, _Mutex>::GetHeader() const
{
    return Header;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint16 MediaManager<_Media, _Mutex>::GetMagicNumber() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.MagicNumber;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetSignature(byte* _signature) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_signature, Header.Signature, sizeof(Header.Signature));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint16 MediaManager<_Media, _Mutex>::GetVersion() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.Version;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint16 MediaManager<_Media, _Mutex>::GetOS() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.OS;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetDescOS(byte* _desc) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_desc, Header.DescOS, sizeof(Header.DescOS));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetDescOS(const byte* _desc)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.DescOS, _desc, sizeof(Header.DescOS));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint16 MediaManager<_Media, _Mutex>::GetByteOrder() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.ByteOrder;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetByteOrder(uint16 _order)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Header.ByteOrder = _order;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetUUID(byte* _uuid) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_uuid, Header.UUID, sizeof(Header.UUID));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetUUID(const byte* _uuid)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.UUID, _uuid, sizeof(Header.UUID));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint32 MediaManager<_Media, _Mutex>::GetCRC32() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.CRC32;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetMD5(byte* _md5) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_md5, Header.MD5, sizeof(Header.MD5));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint32 MediaManager<_Media, _Mutex>::GetLanguageId() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.LanguageId;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetLanguageId(uint32 _id)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Header.LanguageId = _id;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetDesc(byte* _desc) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_desc, Header.Desc, sizeof(Header.Desc));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetDesc(const byte* _desc)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.Desc, _desc, sizeof(Header.Desc));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetUserInfo(byte * _info) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_info, Header.UserInfo, sizeof(Header.UserInfo));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetUserInfo(const byte* _info)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.UserInfo, _info, sizeof(Header.UserInfo));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetSearchCriteria(byte* _criteria) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_criteria, Header.SearchCriteria, sizeof(Header.SearchCriteria));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetSearchCriteria(const byte* _criteria)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.SearchCriteria, _criteria, sizeof(Header.SearchCriteria));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetCreateId(byte* _id) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_id, Header.CreateId, sizeof(Header.CreateId));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetCreateId(const byte* _id)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.CreateId, _id, sizeof(Header.CreateId));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetAccessId(byte* _id) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_id, Header.AccessId, sizeof(Header.AccessId));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetAccessId(const byte* _id)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.AccessId, _id, sizeof(Header.AccessId));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetCategory(byte* _category) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_category, Header.Category, sizeof(Header.Category));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetCategory(const byte* _category)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.Category, _category, sizeof(Header.Category));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetCreationTime(_time& _tm) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    _tm = Header.CreationTime;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetLifeTime(_time& _tm) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    _tm = Header.LifeTime;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetLifeTime(const _time& _tm)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Header.LifeTime = _tm;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetCreateLocation(byte* _loc) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_loc, Header.CreateLocation, sizeof(Header.CreateLocation));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetCreateLocation(const byte* _loc)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.CreateLocation, _loc, sizeof(Header.CreateLocation));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetAccessLocation(byte* _loc) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_loc, Header.AccessLocation, sizeof(Header.AccessLocation));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetAccessLocation(const byte* _loc)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.AccessLocation, _loc, sizeof(Header.AccessLocation));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetCreateReason(byte* _reason) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_reason, Header.CreateReason, sizeof(Header.CreateReason));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetCreateReason(const byte* _reason)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.CreateReason, _reason, sizeof(Header.CreateReason));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::GetAccessReason(byte* _reason) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(_reason, Header.AccessReason, sizeof(Header.AccessReason));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetAccessReason(const byte* _reason)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    memcpy(Header.AccessReason, _reason, sizeof(Header.AccessReason));
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint32 MediaManager<_Media, _Mutex>::GetOffsetToData() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.OffsetToData;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetOffsetToData(uint32 _offset)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Header.OffsetToData = Max(sizeof(Header), _offset);
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint32 MediaManager<_Media, _Mutex>::GetLinkCount() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.LinkCount;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetLinkCount(uint32 _count)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Header.LinkCount = _count;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint32 MediaManager<_Media, _Mutex>::IncreaseLinkCount()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return ++Header.LinkCount;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint32 MediaManager<_Media, _Mutex>::DecreaseLinkCount()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return --Header.LinkCount;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint32 MediaManager<_Media, _Mutex>::GetMediaFlags() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.Flags;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetMediaFlags(uint32 _flags)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Header.Flags = _flags;
}
//
template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ uint MediaManager<_Media, _Mutex>::GetFlags() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Flags;
}

template <typename _Media, typename _Mutex>
__INLINE_TEMPLATE__ void MediaManager<_Media, _Mutex>::SetFlags(uint _flags)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Flags = _flags;
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::Create(const tchar* _filename, uint _mode)
{
    Open(_filename, _mode);
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::Open(const tchar* _filename, uint _mode)
{
    assert(_filename != null);
    //
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Media.Create(_filename, _mode);

    if(!(_mode & _Media::CreateNew))
    {
        ReadHeader();
    }
    else
    {
        InitHeader();
        WriteHeader();
    }
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::Close()
{
    if(Media.IsValid())
    {
        Synchronization::Guard<_Mutex> guard(Mutex);

        if(Media.IsValid())
        {
            WriteHeader();
            Media.FlushBuffers();
            Media.Close();
        }
    }
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::LockRange(fpos_t_ _pos, fsize_t_ _count)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    AdjustPointer(_pos);
    Media.LockRange(_pos, _count);
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::UnlockRange(fpos_t_ _pos, fsize_t_ _count)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    AdjustPointer(_pos);
    Media.UnlockRange(_pos, _count);
}

template <typename _Media, typename _Mutex>
ulong MediaManager<_Media, _Mutex>::Read(void* _buffer, ulong _count, fpos_t_ _pos)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Header.LastAccessTime = Time::GetCurrentTime().GetTime();

    AdjustPointer(_pos);
    return Media.Read(_buffer, _count);
}

template <typename _Media, typename _Mutex>
ulong MediaManager<_Media, _Mutex>::Write(const void* _buffer, ulong _count, fpos_t_ _pos)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Header.LastAccessTime = Time::GetCurrentTime().GetTime();
    Header.LastWriteTime  = Time::GetCurrentTime().GetTime();

    AdjustPointer(_pos);
    return Media.Write(_buffer, _count);
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::Flush()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    WriteHeader();
    Media.FlushBuffers();
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::CalculateCRC32()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    MediaLock<_Media> lock(Media);
    MediaPos<_Media>  pos(Media, Header.OffsetToData);
    //
    const uint _buffer_size_ = 16384; // 16K
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    //
    CRC32 c;

   uint32 count;
   uint32 crc = 0;

    while((count = Media.Read(buffer, _buffer_size_)) != 0 && ::GetLastError() != ERROR_HANDLE_EOF)
    {
        crc = c.UpdateCRC32(crc, buffer, count);
    }

    //
    Header.CRC32 = crc;
}

template <typename _Media, typename _Mutex>
void MediaManager<_Media, _Mutex>::CalculateMD5()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    MediaLock<_Media> lock(Media);
    MediaPos<_Media>  pos(Media, Header.OffsetToData);
    //
    const uint _buffer_size_ = 16384; // 16K
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    AutoPtrArray<byte> md5 = new byte[sizeof(Header.MD5)];

    bool  ok = false;
   uint32  count;

    MD5_CTX context;

    InitMemory(&context, sizeof(context));

    MD5Init(&context);

    while((count = Media.Read(buffer, _buffer_size_)) != 0 && ::GetLastError() != ERROR_HANDLE_EOF)
    {
        MD5Update(&context, buffer, count);
        ok = true;
    }
    
    if(ok)
    {
        MD5Final(&context, md5);
    }

    //
    memcpy(Header.MD5, md5, sizeof(Header.MD5));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MEDIA_MANAGER_INL__

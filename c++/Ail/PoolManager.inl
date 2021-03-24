////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __POOL_MANAGER_INL__
#define __POOL_MANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PoolManager
// ----- -----------
template <typename _Media, typename _Mutex, typename _Allocator>
PoolManager<_Media, _Mutex, _Allocator>::PoolManager(uint _flags, const tchar* _mutex_name, uint _timeout, uint _slot_count, uint _alignment)
    : AheadCount(0),
      CacheSize(0),
      Flags(_flags),
      Mutex(_mutex_name, _timeout),
      PageAllocator(sizeof(PoolManager::_Page), _slot_count, _alignment, (_flags & PoolManager::ZeroFill) ? Allocator<_Mutex, _Allocator>::ZeroFill : 0),
      PageManager(KeyExtractor, Comparator),
      LRU_Manager(KeyExtractor, Comparator)
{
}

template <typename _Media, typename _Mutex, typename _Allocator>
PoolManager<_Media, _Mutex, _Allocator>::~PoolManager()
{
    Close();
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void PoolManager<_Media, _Mutex, _Allocator>::AdjustPointer(fpos_t _new_pos)
{
    if(_new_pos != -1)
    {
        Media.SetPosition(sizeof(Header)+_new_pos);
    }
    else
    {
        fpos_t pos;

        Media.GetPosition(pos);

        if(pos < sizeof(Header))
        {
            Media.SetPosition(sizeof(Header));
        }
    }
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void PoolManager<_Media, _Mutex, _Allocator>::assert(int _expr, uint _error)
{
    if(_expr == 0)
    {
        throw XPoolManager(_error);
    }
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::ReadHeader()
{
    MediaLock<_Media> lock(Media, 0, sizeof(Header));
    MediaPos<_Media>  pos(Media, 0);
    //
    assert(Media.Read(&Header, sizeof(Header)) == sizeof(Header), XPoolManager::InvalidHeader);
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::WriteHeader()
{
    MediaLock<_Media> lock(Media, 0, sizeof(Header));
    MediaPos<_Media>  pos(Media, 0);
    //
    assert(Media.Write(&Header, sizeof(Header)) == sizeof(Header), X::Failure);
    Media.FlushBuffers();
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ PoolManager<_Media, _Mutex, _Allocator>::_Page* PoolManager<_Media, _Mutex, _Allocator>::ConstructPage(_ulong _id)
{
    void*  ptr  = PageAllocator.Allocate();
   _Page*  page = new (ptr) _Page(_id);
    return page;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void PoolManager<_Media, _Mutex, _Allocator>::DestroyPage(_Page* _page)
{
    if(_page != null)
    {
       _page->~_Page();
        PageAllocator.Deallocate(_page);
    }
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const _Media& PoolManager<_Media, _Mutex, _Allocator>::GetMedia() const
{
    return Media;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const PoolManager<_Media, _Mutex, _Allocator>::_Header& PoolManager<_Media, _Mutex, _Allocator>::GetHeader() const
{
    return Header;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ _uint PoolManager<_Media, _Mutex, _Allocator>::GetPageSize() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.PageSize;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ _ulong PoolManager<_Media, _Mutex, _Allocator>::GetPageCount() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Header.PageCount;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ ulong PoolManager<_Media, _Mutex, _Allocator>::GetAheadCount() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return AheadCount;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void PoolManager<_Media, _Mutex, _Allocator>::SetAheadCount(uint _count)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    AheadCount = _count;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ uint PoolManager<_Media, _Mutex, _Allocator>::GetCacheSize() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return CacheSize;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void PoolManager<_Media, _Mutex, _Allocator>::SetCacheSize(uint _size)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    CacheSize = _size;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ uint PoolManager<_Media, _Mutex, _Allocator>::GetFlags() const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    return Flags;
}

template <typename _Media, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void PoolManager<_Media, _Mutex, _Allocator>::SetFlags(uint _flags)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Flags = _flags;
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::Create(const tchar* _filename, uint _mode, uint _cache_size, uint _ahead_count, uint _page_size, uint _alignment)
{
    assert(_filename != null);
    //
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Media.Create(_filename, _mode);

    /////////////////////////////////
    #define POWER2(_x)              \
            if(!IsPowerOfTwo(_x))   \
            {                       \
                uint x = 0x00000001;\
                                    \
                while(x < _x)       \
                {                   \
                    x <<= 1;        \
                }                   \
                                    \
               _x = x;              \
            }                       \
    /////////////////////////////////

    if(_mode & _Media::CreateNew)
    {
        // setup page size as power of two
        if(_page_size == -1)
        {
            _page_size = PAGE_SIZE;
        }
        else if(_page_size == 0)
        {
            SYSTEM_INFO si;
          ::GetSystemInfo(&si);
           _page_size = si.dwPageSize;
        }
        else
        {
            POWER2(_page_size)
        }

        Header.PageSize = _page_size;
        WriteHeader();
    }
    else // open
    {
        ReadHeader();

        if(_page_size > 0)
        {
            // page size is power of two, so it's possible to change that
            // if page size was 512, it's possible, for example, to read
            // as either 16 or 64 or 256 bytes block
            POWER2(_page_size)
            Header.PageSize = _page_size;
        }
    }

    // cache size
    CacheSize = ALIGN(_cache_size, _alignment);

    // setup read ahead
    AheadCount = _ahead_count == -1 ? READ_AHEAD : _ahead_count == 0 ? 0 : ALIGN(_ahead_count, 16);
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::Open(const tchar* _filename, uint _mode, uint _cache_size, uint _ahead_count, uint _page_size, uint _alignment)
{
    Create(_filename, _mode, _page_size, _ahead_count, _alignment);
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::Close()
{
    if(Media.IsValid())
    {
        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        if(Media.IsValid())
        {
            Flush();
            Media.Close();
        }
    }
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::LockRange(fpos_t _pos, fsize_t _count)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Media.LockRange(_pos, _count);
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::UnlockRange(fpos_t _pos, fsize_t _count)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Media.UnlockRange(_pos, _count);
}

template <typename _Media, typename _Mutex, typename _Allocator>
ulong PoolManager<_Media, _Mutex, _Allocator>::Read(void* _buffer, ulong _count, fpos_t _pos)
{
    assert(_buffer);
    Synchronization::Guard<_Mutex> guard(Mutex);
    //

/*
	esli budm chitat' mnogo pages, to more efficient
	get current time and increase it for every next page !

    if(last operation was write seek(0, curr)
    else seek(n, ...)

    while(neccessary read)
      naiti nuzhnuu page

      if page in memory
        copy data from it to a buffer
      else 
        if CasheCount >= limit
          walk through all pages and unload least used page

        create page

        if AheadCount > 0
          read AheadCount*PageSize bytes, rearrange

        load data from media

      nuzhno li read?

*/

    return 0;
}

template <typename _Media, typename _Mutex, typename _Allocator>
ulong PoolManager<_Media, _Mutex, _Allocator>::Write(const void* _buffer, ulong _count, fpos_t _pos)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    return 0;
}

template <typename _Media, typename _Mutex, typename _Allocator>
void PoolManager<_Media, _Mutex, _Allocator>::Flush()
{
    WriteHeader();

    // write all dirty pages back
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __POOL_MANAGER_INL__

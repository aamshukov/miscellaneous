////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __POOL_MANAGER_H__
#define __POOL_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, before, 2)
////////////////////////////////////////////////////////////////////////////////////////
// class PoolManager
// ----- -----------
template <typename _Media = File<>, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class PoolManager
{
    private:

    enum EDefConst
    {
        PageSize   = 512, // size of page
        CacheSize  = 32,  // how many pages in cache
        AheadCount = 4    // how many pages read/write ahead
    };

    /////////////////////
    // class KeyExtractor
    // ----- ------------
    template <typename _T, typename _Key> struct KeyExtractor
    {
        const _Key& operator () (const _T& _val) const { return _val.GetKey(); }
    };

    ///////////////////
    // class Comparator
    // ----- ----------
    template <typename _Key> struct Comparator
    {
        int operator () (const _Key& _k1, const _Key& _k2) const { return _k1 < _k2 ? -1 : _k1 == _k2 ? 0 : 1; }
    };

    //////////////
    // class _Page
    // ----- -----
    class _Page : public TreeNodeBase<_Page, uint>, public ListNodeBase<_Page, uint>
    {
        friend class PoolManager<_Media, _Mutex, _Allocator>;

        private:

        enum EPageState
        {
            PageFree   = 0x00, // page is free
            PageDirty  = 0x01, // page was modified
            PageBusy   = 0x02, // page is reading/writing from/to storage
            PageWait   = 0x04, // some tasks are waiting for page
            PageLocked = 0x08  // do not remove page from memory
        };

        private:
         uint   Id;         // number of page
         uint   State;      // dirty, busy, wait
        _time   TimeStamp;  // time stamp of page
         uint   UsageCount; // least used page will be deleted
         byte*  Data;       // actual data
        public:
               _Page(uint _id) : Id(_id),
                                 State(PoolManager::PageFree),
                                 TimeStamp(Time::GetCurrentTime().GetTime()),
                                 Count(0),
                                 Data(this+sizeof(*this))
                {
                }

              ~_Page()
                {
                }

         const uint& GetKey() const { return Id; }
    };
    //
    typedef Synchronization::NullThreadMutex<>                                           _NullMutex;
    typedef Synchronization::Event<>                                                     _Event;
    typedef KeyExtractor<_Page, uint>                                                    _KeyExtractor;
    typedef Comparator<uint>                                                             _Comparator;
    typedef Allocator<_NullMutex, _Allocator>                                            _PageAllocator;
    typedef AVLTree<_Page, uint, _KeyExtractor, _Comparator, _NullMutex, _PageAllocator> _PageManager;
    typedef List<_Page, uint, _KeyExtractor, _Comparator, _NullMutex, _PageAllocator>    _LRU_Manager;
    //
    private:
     uint               PageSize;       // size of page
     uint               PageCount;      // how many pages now in memory (-1 in memory database)
     uint               CacheSize;      // how many pages in memory (-1 in memory database)
     uint               AheadCount;     // how many pages read/write ahead
     uint               Flags;          // flags
    _Media              Media;          // media (file, memory or whatever)
    _Mutex              Mutex;          // synchronization monitor
    _Event              Event;          // prevent concurrent reading/writing of page
    _PageAllocator      PageAllocator;  // allocates continuous memory block and places pages in it
    _PageManager        PageManager;    // AVL tree
    _LRU_Manager        LRU_Manager;    // LRU/MRU discipline (head-MRU, tail-LRU)
    _KeyExtractor       KeyExtractor;   // key extractor for ADT
    _Comparator         Comparator;     // key comparator for ADT
    private:
    _Page*              ConstructPage(uint);
     void               DestroyPage(_Page*);
    public:

    enum EFlag
    {
        ZeroOut          = 0x00000001,  // page is filled out with zero (create/destroy)
        ReadAhead        = 0x00000002,  // mechanism read ahead (round up to system disk page)
        WriteAhead       = 0x00000004,  // mechanism write ahead (round up to system disk page)
        WriteBehind      = 0x00000008,  // on  - mechanism write behind (lazy flush)
                                        // off - mechanism write through (immediately flush)
        WriteSorting     = 0x00000010,  // reorder writes to minimize rotational delays
        SequentialAccess = 0x00000020,  // optimization for sequential access
        RandowAccess     = 0x00000040,  // optimization for random access
    };
    public:
     // ctor/dtor
                        PoolManager(uint = PoolManager::ReadAhead|PoolManager::WriteAhead|PoolManager::WriteBehind,
                                    const tchar* = null,
                                    uint   = Synchronization::TimeoutNoLimit,
                                    uint = 0,
                                    uint = 64);
     virtual           ~PoolManager();

     // access
     uint               GetPageSize()               const;
     void               SetPageSize(uint);

     uint               GetPageCount()              const;

     uint               GetCacheSize()              const;
     void               SetCacheSize(uint);

     uint               GetAheadCount()             const;
     void               SetAheadCount(uint);

     uint               GetFlags()                  const;
     void               SetFlags(uint);
     //
     const _Media&      GetMedia()                  const;

     // protocol
     void               Create(const tchar*, uint = _Media::CreateNew|_Media::AccessReadWrite|_Media::ShareExclusive|_Media::WriteThrough, uint = -1, uint = -1, uint = -1, uint = 64);
     void               Open(const tchar*, uint = _Media::AccessReadWrite|_Media::ShareExclusive, uint = -1, uint = -1, uint = -1, uint = 64);
     void               Close();

     void               LockPage(uint);

     void               LockRange(_fpos_t, _fsize_t);
     void               UnlockRange(_fpos_t, _fsize_t);

     uint               Read(void*, ulong, _fpos_t = -1);
     uint               Write(const void*, ulong, _fpos_t = -1);

     void               Flush();
};
////////////////////////////////////////////////////////////////////////////////////////
// class XPoolManager
// ----- ------------
class XPoolManager : public X
{
    public:
        XPoolManager(uint = X::Failure);
       ~XPoolManager();
};
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(pop, before)
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __POOL_MANAGER_H__


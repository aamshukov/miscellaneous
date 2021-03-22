////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ALLOCATOR_H__
#define __ALLOCATOR_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, before, 8)
////////////////////////////////////////////////////////////////////////////////////////
// class Allocator
// ----- ---------
template <typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class Allocator
{
    public:

    enum EMask
    {
        Mask = 0x00000001
    };

    enum EFlags
    {
        ZeroFill  = 0x00000001, // zero out allocate/deallocate
        FreeExtra = 0x00000002, // release chunk if all its slots are not in use
        FlagsMask = 0x0000000F
    };

    private:

    /////////////////////
    // class KeyExtractor
    // ----- ------------
    template <typename _T, typename _Key> struct KeyExtractor
    {
        const _Key& operator () (const _T& _val) const { return _val; }
    };
    ///////////////////
    // class Comparator
    // ----- ----------
    template <typename _Key> struct Comparator
    {
        int operator () (const _Key& _k1, const _Key& _k2) const { return 0; }
    };
    ///////////////
    // class _Chunk
    // ----- ------
    class _Chunk : public ListNodeBase<_Chunk, pvoid>
    {
        public:
               _Chunk() {};
              ~_Chunk() {};
    };
    //
    typedef KeyExtractor<_Chunk, pvoid>                     _KeyExtractor;
    typedef Comparator<pvoid>                               _Comparator;
    typedef List<_Chunk, pvoid, _KeyExtractor, _Comparator> _List;

    private:
     uint               Flags;
     uint               SlotSize;
     uint               SlotCount;
     byte*              FreeList;
    _Mutex              Mutex;
    _List               Chunks;
    _KeyExtractor       KeyExtractor;
    _Comparator         Comparator;
    private:
                        Allocator(const Allocator&);
     const Allocator&   operator = (const Allocator&);
    public:
     // ctor/dtor
                        Allocator(uint, uint = 64, uint = 64, uint = Allocator::ZeroFill, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
                       ~Allocator();

     // access
     uint               GetFlags()  const;

     // protocol
     void*              Allocate(uint = 0);
     void               Deallocate(void*);

     void               Compact();
};
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(pop, before)
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ALLOCATOR_H__

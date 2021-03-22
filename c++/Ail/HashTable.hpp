////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HashTable
// ----- ---------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class HashTable : public ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef HashTableNodeBase<_T, _Key>                                          _Node;
    typedef Array<_Node*, Synchronization::NullThreadMutex<>, _Allocator>        _Buckets;
    typedef HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>  _Table;

    private:
                                HashTable(const _Table&);
     const _Table&              operator = (const _Table&);
     //
    _Node*                      ConstructNode(const _T&);
     void                       DestroyNode(_Node*);
    protected:
     ulong                      Count;
    _Buckets                    Buckets;

     static ulong               HashFunc(const tchar*);
    protected:
     static ulong               AdjustSize(ulong);
    public:
     // ctor/dtor
                                HashTable(const _KeyExtractor&, const _Comparator&, ulong = 0, bool = true, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual                   ~HashTable();

     //
     void                       Create(ulong = 0);
     void                       Destroy();

     // info
     ulong                      GetCount()                  const;

     // access
     const _T&                  operator [] (const _Key&)   const;

     //
     bool                       HasEntry(const _Key&)       const;
     const _Node*               Search(const _Key&)         const;

     void                       Insert(_Node*);
     void                       Insert(const _T&);

     void                       Remove(const _Key&, bool = true);

     void                       Rehash();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HASH_TABLE_H__

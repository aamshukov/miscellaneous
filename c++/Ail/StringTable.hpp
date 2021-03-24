////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __STRING_TABLE_H__
#define __STRING_TABLE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class StringTableEntry
// ----- ----------------
template <typename _T = tchar> class StringTableEntry
{
    typedef StringTableEntry<_T> _Entry;

    public:
    _T          Data;
    _Entry*     Left;

    union
    {
       _Entry*  Middle;
        void*   PData;
    };

    _Entry*     Right;
    public:
     // ctor/dtor
     explicit   StringTableEntry(const _T&);
     virtual   ~StringTableEntry();
};
////////////////////////////////////////////////////////////////////////////////////////
// class StringTable
// ----- -----------
template <typename _T = tchar, typename _Mutex = Synchronization::NullThreadMutex<>, typename _Allocator = Allocator<Synchronization::NullThreadMutex<> > > class StringTable
{
    typedef StringTableEntry<_T> _Entry;

    private:
     bool       Cleanup;
    _Entry*     Root;
    _Mutex      Mutex;
    _Allocator  Allocator;
    protected:
     void       DoCleanup(_Entry*);
    public:
     // ctor/dtor
                StringTable(uint = 16, uint = 8, bool = false, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual   ~StringTable();

     // access
    _Entry*     GetRoot()                                               const;

     // protocol
     bool       HasString(const tchar*)                                 const;
     bool       Search(const tchar*, void** = null)                     const;
     void       PartialMatchSearch(const _Entry*, const tchar*, ...)    const;
     void       NearSearch(const _Entry*, const tchar*, int, ...)       const;

     void       Insert(const tchar*, void* = null);
     void       Destroy();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __STRING_TABLE_H__

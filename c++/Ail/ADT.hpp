////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ADT_H__ // abstract data type
#define __ADT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ADT
// ----- ---
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class ADT : protected StateObject
{
    typedef StateObject::EState _State;

    protected:
    _Mutex          Mutex;
    _KeyExtractor   ExtractKey;
    _Comparator     CompareKey;
    protected:
     const _Key&    GetKey(const NodeBase<_T, _Key>*);
    public:
     // ctor/dtor
                    ADT(const _KeyExtractor&, const _Comparator&, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~ADT();

     // access
     bool           ShouldDelete()                              const;
    _State          SetState(_State = StateObject::eDelete);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ADT_H__

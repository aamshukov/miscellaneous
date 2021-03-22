////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LIST_H__
#define __LIST_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
//  ATTENTION:
//   This implementation of List supports two different schemas for holding objects:
//      1. new ListNodeBase<_T, _Key> - IsShouldDelete() & ListBaseNode::StandardAllocator -> delete (default)
//      2. new ListNode<_T, _Key>     - _Allocator::Deallocate()
////////////////////////////////////////////////////////////////////////////////////////
template <typename _T, typename _Key, typename _Mutex> class ListIterator;
////////////////////////////////////////////////////////////////////////////////////////
// class List
// ----- ----
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class List : public ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef ListNodeBase<_T, _Key> _Node;

    friend class ListIterator<_T, _Key, _Mutex>;

    public:

    enum EFlag
    {
        UniqueKey     = 0x0001,
        DirectSearch  = 0x0002,
        SmartAccess   = 0x0004,
        SelfOrganized = 0x0008,
        Compound      = DirectSearch|SmartAccess,
    };

    private:
                        List(const List&);
     const List&        operator = (const List&);
    protected:
     // core
    _Node*              Head;
    _Node*              Tail;

     uint               Flags;
     uint               Count;

     // as an array
     int                LowerBound;
     int                UpperBound;

     // smart access
     mutable int        CurrentIndex;
     mutable _Node*     Current;
    private:
    _Node*              ConstructNode(const _T&);
     void               DestroyNode(_Node*);

     void               Init();
     void               InitCurrent();

     void               AssertRange(int)                const;

     int                GetCurrentIndex()               const;
    protected:
     virtual void      _Destroy();
    public:
     // ctor/dtor
                        List(const _KeyExtractor&, const _Comparator&, uint = List::Compound, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
                        List(const _KeyExtractor&, const _Comparator&, int, int, uint = List::Compound, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual           ~List();

     // access
     uint               GetCount()                      const;

     bool               IsEmpty()                       const;

     bool               IsUniqueKey()                   const;
     bool               IsDirectSearch()                const;
     bool               IsSmartAccess()                 const;

     void               ModifyFlags(uint, uint);

     // protocol (as a list)
     const _Node*       GetNode(int)                    const;
     uint               GetIndex(const _Node*)          const;

     const _Node*       GetHead()                       const;
     const _Node*       GetTail()                       const;
     const _Node*       GetCurrent()                    const;

     bool               HasNode(const _Node*)           const;
     bool               HasData(const _Key&)            const;

     const _Node*       Search(const _Key&);

     void               LinkHead(_Node*);
     void               LinkHead(const _T&);

     void               UnlinkHead(bool = true);

     void               LinkTail(_Node*);
     void               LinkTail(const _T&);

     void               UnlinkTail(bool = true);

     void               Link(_Node*, bool = true);
     void               Link(const _T&, bool = true);
     void               Link(_Node*, int, bool, bool = false);
     void               Link(const _T&, int, bool, bool = false);
     void               Link(_Node*, _Node*, bool = true);
     void               Link(const _T&, const _Key&, bool = true);

     void               Unlink(_Node*, bool = true);
     void               Unlink(const _Key&, bool = true);

     void               Swap(_Node*, _Node*);

     void               MoveHead(_Node*);
     void               MoveTail(_Node*);
     void               MoveForward(_Node*);
     void               MoveBackward(_Node*);

     void               Sort(bool = true);
     void               Unique();
     void               Destroy();

     // protocol (as an array)
     int                GetLowerBound()                 const;
     void               SetLowerBound(int);

     int                GetUpperBound()                 const;
     void               SetUpperBound(int);

    _T&                 operator [] (int);
    _T&                 operator [] (const _Key&);
};
////////////////////////////////////////////////////////////////////////////////////////
// class XList
// ----- -----
class __DECLSPEC__ XList : public X
{
    public:

    enum EError
    {
        NotUnique  = 0x00000100
    };

    public:
        XList(uint = X::Failure);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ListIterator
// ----- ------------
template <typename _T, typename _Key, typename _Mutex = Synchronization::ThreadMutex<> > class ListIterator
{
    typedef ListNodeBase<_T, _Key> _Node;

    protected:
    _Mutex                  Mutex;
     mutable _Node*         CurrentNode;
    public:
     // ctor/dtor
                            ListIterator(const _Node*, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
                            ListIterator(const ListIterator&, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual               ~ListIterator();

     // operators
     const ListIterator&    operator = (const ListIterator&);

    _T&                     operator *   ();
                            operator int ();

    _Node*                  operator ++ (int);
    _Node*                  operator ++ ();
    _Node*                  operator -- (int);
    _Node*                  operator -- ();

     // access
     const _Node*           GetCurrentNode();
    _T&                     Current();

     // protocol
     void                   Restart(const _Node*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __LIST_H__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LIST_INL__
#define __LIST_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class List
// ----- ----
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::List(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _mutex_name, _timeout)
{
    Init();
    //
    Flags = _flags;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::List(const _KeyExtractor& _kx, const _Comparator& _cmp, int _lb, int _ub, uint _flags, const tchar* _mutex_name, uint _timeout) : ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _mutex_name, _timeout)
{
    Init();
    //
    Flags      = _flags;
    LowerBound = _lb;
    UpperBound = _ub;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~List()
{
    Destroy();              
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Init()
{
    Head         = null;
    Tail         = null;
    Flags        = 0;
    Count        = 0;
    LowerBound   = 0;
    UpperBound   = INT_MAX,
    CurrentIndex = 0;
    Current      = null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::InitCurrent()
{
    Current      = IsDirectSearch() ? Head : Tail;
    CurrentIndex = IsDirectSearch() ? 0 : Count-1;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ ListNodeBase<_T, _Key>* List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ConstructNode(const _T& _data)
{
    void* p = _Allocator::Allocate(sizeof(ListNode<_T, _Key>));
    ListNode<_T, _Key>* node = new (p) ListNode<_T, _Key>(_data);
    node->ModifyFlags(NodeBase<_T, _Key>::StandardAlloc, 0);
    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::DestroyNode(ListNodeBase<_T, _Key>* _node)
{
    if(_node != null && ShouldDelete())
    {
        if(_node->GetFlags() & ListNodeBase<_T, _Key>::StandardAlloc)
        {
            delete _node;
        }
        else
        {
            _node->~ListNodeBase<_T, _Key>(); // virtual dtor OK
            _Allocator::Deallocate(static_cast<ListNode<_T, _Key>*>(_node)); // casting
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::AssertRange(int _i) const
{
    if(_i < LowerBound || _i > UpperBound)
    {
        throw XList(XList::OutOfRange);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ uint List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetCount() const
{
    return Count;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::IsEmpty() const
{
    return Head == null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::IsUniqueKey() const
{
    return (Flags & List<_T, _Key, _KeyExtractor, _Comparator>::UniqueKey) != 0;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::IsDirectSearch() const
{
    return (Flags & List<_T, _Key, _KeyExtractor, _Comparator>::DirectSearch) != 0;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::IsSmartAccess() const
{
    return (Flags & List<_T, _Key, _KeyExtractor, _Comparator>::SmartAccess) != 0;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ModifyFlags(uint _remove, uint _add)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    Flags = (Flags & ~_remove) | _add);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
const ListNodeBase<_T, _Key>* List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetNode(int _i) const
{
    AssertRange(_i);
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    int index = IsDirectSearch() ? LowerBound : Count;

    ListNodeBase<_T, _Key>* start = IsDirectSearch() ? Head : Tail;

    if(Current != null && IsSmartAccess())
    {
        if(_i == CurrentIndex)
        {
            return reinterpret_cast<const ListNodeBase<_T, _Key>*>(Current);
        }
        else if(_i < CurrentIndex)
        {
            if(IsDirectSearch())
            {
                start = Head;
            }
            else
            {
                start = Current;
                index = CurrentIndex;
            }
        }
        else if(_i > CurrentIndex)
        {
            if(IsDirectSearch())
            {
                start = Current;
                index = CurrentIndex;
            }
            else
            {
                start = Tail;
            }
        }
    }

    for(ListNodeBase<_T, _Key>* i = start; i != null; i = IsDirectSearch() ? i->Next : i->Prev, index += IsDirectSearch() ? 1 : -1)
    {
        if(index == _i)
        {
            CurrentIndex = index, Current = i;
            return reinterpret_cast<const ListNodeBase<_T, _Key>*>(i);
        }
    }

    return reinterpret_cast<const ListNodeBase<_T, _Key>*>(null);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
uint List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetIndex(const ListNodeBase<_T, _Key>* _node) const
{
    uint index = 0;

    for(ListNodeBase<_T, _Key>* i = Head; i != null; i = i->Next, index++)
    {
        if(i == _node)
        {
            return index;
        }
    }

    return -1;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const ListNodeBase<_T, _Key>* List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHead() const
{
    return reinterpret_cast<const ListNodeBase<_T, _Key>*>(Head);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const ListNodeBase<_T, _Key>* List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetTail() const
{
    return reinterpret_cast<const ListNodeBase<_T, _Key>*>(Tail);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const ListNodeBase<_T, _Key>* List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetCurrent() const
{
    return reinterpret_cast<const ListNodeBase<_T, _Key>*>(Current);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ int List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetCurrentIndex() const
{
    return CurrentIndex;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
bool List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::HasNode(const ListNodeBase<_T, _Key>* _node) const
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(Current == _node)
    {
        return true;
    }

    for(ListNodeBase<_T, _Key>* i = Head; i != null; i = i->Next)
    {
        if(i == _node)
        {
            return true;
        }
    }

    return false;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
bool List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::HasData(const _Key& _key) const
{
    return Search(_key) != null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
const ListNodeBase<_T, _Key>* List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Search(const _Key& _key)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(Current != null && CompareKey(GetKey(Current), _key) == 0)
    {
        return Current;
    }

    for(ListNodeBase<_T, _Key>* i = Head; i != null; i = i->Next)
    {
        if(CompareKey(GetKey(i), _key) == 0)
        {
            if(Flags & List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SelfOrganized)
            {
                MoveHead(i);
            }

            return i;
        }
    }

    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LinkHead(ListNodeBase<_T, _Key>* _node)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ++Count;

    if(Head == null)
    {
        Head = Tail = _node;
    }
    else
    {
        _node->Next = Head, Head->Prev = _node, Head = _node;
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LinkHead(const _T& _data)
{
    ListNodeBase<_T, _Key>* node = ConstructNode(_data);
    LinkHead(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UnlinkHead(bool _destroy)
{
    if(Head == null)
    {
        throw XList(XList::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListNodeBase<_T, _Key>* node = Head;

    if(--Count == 0)
    {
        Head = Tail = null;
    }
    else
    {
        Head = Head->Next, Head->Prev = null;
    }

    node->Next = node->Prev = null;

    if(_destroy)
    {
        DestroyNode(node);
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LinkTail(ListNodeBase<_T, _Key>* _node)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ++Count;

    if(Tail == null)
    {
        Head = Tail = _node;
    }
    else
    {
        _node->Prev = Tail, Tail->Next = _node, Tail = _node;
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LinkTail(const _T& _data)
{
    ListNodeBase<_T, _Key>* node = ConstructNode(_data);
    LinkTail(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UnlinkTail(bool _destroy)
{
    if(Tail == null)
    {
        throw XList(XList::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListNodeBase<_T, _Key>* node = Tail;

    if(--Count == 0)
    {
        Head = Tail = null;
    }
    else
    {
        Tail = Tail->Prev, Tail->Next = null;
    }

    node->Next = node->Prev = null;

    if(_destroy)
    {
        DestroyNode(node);
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Link(ListNodeBase<_T, _Key>* _node, bool _ascending)
{
    ListNodeBase<_T, _Key>* tmp = Head;

    if(_node == null)
    {
        throw XList(XList::InvalidArg);
    }

    if(IsUniqueKey() && HasNode(_node))
    {
        throw XList(XList::NotUnique);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    const _Key& key = GetKey(_node);

    if(_ascending)
    {
        while(tmp != null)
        {
            if(CompareKey(key, GetKey(tmp)) < 0)
            {
                Link(_node, tmp);
                return;
            }
            
            tmp = tmp->Next;
        }

        LinkTail(_node);
    }
    else
    {
        while(tmp != null)
        {
            if(CompareKey(GetKey(tmp), key) < 0)
            {
                Link(_node, tmp);
                return;
            }

            tmp = tmp->Next;
        }

        LinkHead(_node);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Link(const _T& _data, bool _ascending)
{
    ListNodeBase<_T, _Key>* node = ConstructNode(_data);
    Link(node, _ascending);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Link(ListNodeBase<_T, _Key>* _node, int _i, bool _before, bool _tohead)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListNodeBase<_T, _Key>* tmp = const_cast<ListNodeBase<_T, _Key>*>(GetNode(_i));

    if(tmp != null)
    {
        Link(_node, tmp, _before);
    }
    else
    {
        if(_tohead)
        {
            LinkHead(_node);
        }
        else
        {
            LinkTail(_node);
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Link(const _T& _data, int _i, bool _before, bool _tohead)
{
    ListNodeBase<_T, _Key>* node = ConstructNode(_data);
    return Link(node, _i, _before, _tohead);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Link(ListNodeBase<_T, _Key>* _node, ListNodeBase<_T, _Key>* _node_old, bool _before)
{
    if(_node == null || _node_old == null)
    {
        throw XList(XList::InvalidArg);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ++Count;

    if(_before)
    {
        if(_node_old == Head)
        {
            _node->Next = Head, Head->Prev = _node, Head = _node;
        }
        else
        {
            _node_old->Prev->Next = _node, _node->Prev = _node_old->Prev, _node->Next = _node_old, _node_old->Prev = _node;
        }
    }
    else
    {
        if(_node_old == Tail)
        {
            _node->Prev = Tail, Tail->Next = _node, Tail = _node;
        }
        else
        {
            _node_old->Next->Prev = _node, _node->Prev = _node_old, _node->Next = _node_old->Next, _node_old->Next = _node;
        }
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Link(const _T& _data, const _Key& _key_old, bool _before)
{
    ListNodeBase<_T, _Key>* old_node = GetNode(_data_old);

    if(node != null)
    {
        ListNodeBase<_T, _Key>* node = ConstructNode(_data);
        Link(node, old_node, _before);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Unlink(ListNodeBase<_T, _Key>* _node, bool _destroy)
{
    if(Head == null)
    {
        throw XList(XList::OutOfRange);
    }

    if(_node == null)
    {
        throw XList(XList::InvalidArg);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(--Count == 0)
    {
        Head = Tail = null;
    }
    else
    {
        if(_node == Head)
        {
            Head = Head->Next, Head->Prev = null;
        }
        else if(_node == Tail)
        {
            Tail = Tail->Prev, Tail->Next = null;
        }
        else
        {
            _node->Prev->Next = _node->Next, _node->Next->Prev = _node->Prev;
        }
    }

    _node->Next = _node->Prev = null;

    if(_destroy)
    {
        DestroyNode(_node);
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Unlink(const _Key& _key, bool _destroy)
{
    ListNodeBase<_T, _Key>* node = GetNode(_key);

    if(node != null)
    {
        Unlink(node, _destroy);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Swap(ListNodeBase<_T, _Key>* _node1, ListNodeBase<_T, _Key>* _node2)
{
    if(_node1 == null || _node2 == null || _node1 == _node2)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    static ListNodeBase<_T, _Key> tmp;
    //
    if(_node1 == Head)
    {
        Head = _node2;
    }
    else if(_node2 == Head)
    {
        Head = _node1;
    }

    if(_node1 == Tail)
    {
        Tail = _node2;
    }
    else if(_node2 == Tail)
    {
        Tail = _node1;
    }

    // phase I (tmp <--> 1)
    if(_node1->Prev != null)
    {
        _node1->Prev->Next = &tmp;
    }

    tmp.Prev = _node1->Prev;
    tmp.Next = _node1->Next;

    if(_node1->Next != null)
    {
        _node1->Next->Prev = &tmp;
    }

    // phase II (1 <--> 2)
    if(_node2->Prev != null)
    {
        _node2->Prev->Next = _node1;
    }

    _node1->Prev = _node2->Prev;
    _node1->Next = _node2->Next;

    if(_node2->Next != null)
    {
        _node2->Next->Prev = _node1;
    }
    
    // phase III (2 <--> tmp)
    if(tmp.Prev != null)
    {
        tmp.Prev->Next = _node2;
    }

    _node2->Prev = tmp.Prev;
    _node2->Next = tmp.Next;

    if(tmp.Next != null)
    {
        tmp.Next->Prev = _node2;
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveHead(ListNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        throw XList(XList::InvalidArg);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(_node == Head)
    {
        InitCurrent();
        return;
    }
    else if(_node == Tail && Head != Tail)
    {
        Tail = Tail->Prev, Tail->Next = null;
        Head->Prev = _node, _node->Next = Head, _node->Prev = null, Head = _node;
    }
    else
    {
        _node->Prev->Next = _node->Next, _node->Next->Prev = _node->Prev, Head->Prev = _node;
        _node->Next = Head, _node->Prev = null, Head = _node;
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveTail(ListNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        throw XList(XList::InvalidArg);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(_node == Head && Head != Tail)
    {
        Head = Head->Next, Head->Prev = null;
        Tail->Next = _node, _node->Prev = Tail, _node->Next = null, Tail = _node;
    }
    else if(_node == Tail)
    {
        InitCurrent();
        return;
    }
    else
    {
        _node->Prev->Next = _node->Next, _node->Next->Prev = _node->Prev;
        _node->Next = null, _node->Prev = Tail, Tail->Next = _node, Tail = _node;
    }

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveForward(ListNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        throw XList(XList::InvalidArg);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Swap(_node, _node->Next);
    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveBackward(ListNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        throw XList(XList::InvalidArg);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Swap(_node, _node->Prev);
    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Sort(bool _ascending)
{
    if(Count < 2)
    {
        return;
    }
    //
    Synchronization::Guard<_Mutex> guard(Mutex);
    // straight merge sort algorithm ~O(n log n)
    // mozhno luchshe, no kuda ?!
    // I do not use natural merge, because it requires more compares to deternine
    // the end of each serie and I do not know in advance what is the Key ! ...
    typedef ListNodeBase<_T, _Key> _Node;
    typedef List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator> _List;
    //
   _List list(ExtractKey, CompareKey);  // aux list
   _List list1(ExtractKey, CompareKey); // contains first sub-list
   _List list2(ExtractKey, CompareKey); // contains second sub-list
    //
    StateObject::EState prev_state = SetState(StateObject::NoDelete);
    list.SetState(StateObject::NoDelete);
    list1.SetState(StateObject::NoDelete);
    list2.SetState(StateObject::NoDelete);
    //
    uint size  = 1; // size of sub-lists
    uint count = Count;;
    uint n;
    
    // context
   _List* list_in  = this;
   _List* list_out = &list;

   _Node* p;
   _Node* tmp;

    // merge sub-lists of size 'size'
    while(size < count)
    {
        n = 0;
        p = const_cast<_Node*>(list_in->GetHead());

        // check to see if there are two sub-lists to merge
        while(n < count)
        {
            // setup sub-lists
            for(uint i = 0; i < size && !list_in->IsEmpty(); i++)
            {
                tmp = const_cast<_Node*>(list_in->GetHead());
                list_in->Unlink(tmp);
                list1.LinkTail(tmp);
            }

            for(i = 0; i < size && !list_in->IsEmpty(); i++)
            {
                tmp = const_cast<_Node*>(list_in->GetHead());
                list_in->Unlink(tmp);
                list2.LinkTail(tmp);
            }

            p = const_cast<_Node*>(list_in->GetHead());

            // proceed through the two sub-lists (merge)
            while(!list1.IsEmpty() && !list2.IsEmpty())
            {
                if(_ascending ? (CompareKey(GetKey(list1.GetHead()), GetKey(list2.GetHead())) <= 0) : (CompareKey(GetKey(list2.GetHead()), GetKey(list1.GetHead())) <= 0))
                {
                    tmp = const_cast<_Node*>(list1.GetHead());
                    list1.Unlink(tmp);
                }
                else
                {
                    tmp = const_cast<_Node*>(list2.GetHead());
                    list2.Unlink(tmp);
                }
                
                list_out->LinkTail(tmp);
            }

            // at this point, one of the sub-lists has been exhausted
            // proceed any remaining portions of the other sub-list
            while(!list1.IsEmpty())
            {
                tmp = const_cast<_Node*>(list1.GetHead());
                list1.Unlink(tmp);
                list_out->LinkTail(tmp);
            }

            while(!list2.IsEmpty())
            {
                tmp = const_cast<_Node*>(list2.GetHead());
                list2.Unlink(tmp);
                list_out->LinkTail(tmp);
            }

            n += 2*size;
        }

        // proceed any ramaining single sub-list
        while(!list_in->IsEmpty())
        {
            tmp = const_cast<_Node*>(list_in->GetHead());
            list_in->Unlink(tmp);
            list_out->LinkTail(tmp);
        }

        // switch context
        list_in  = list_in  == this  ? &list : this;
        list_out = list_out == &list ? this  : &list;

        // adust size
        size *= 2;
    }

    // copy the aux list to the list
    if(list_out == this)
    {
        while(!list_in->IsEmpty())
        {
            tmp = const_cast<_Node*>(list_in->GetHead());
            list_in->Unlink(tmp);
            LinkTail(tmp);
        }
    }

    SetState(prev_state);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Unique()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListNodeBase<_T, _Key>* head = Head;
    ListNodeBase<_T, _Key>* tail = Tail;
    ListNodeBase<_T, _Key>* node;

    if(head == tail)
    {
        return;
    }

    for(node = head; (node = node->Next) != tail; node = head)
    {
        if(*head == *node)
        {
            Unlink(node);
        }
        else
        {
            head = node;
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Destroy()
{
    _Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::_Destroy()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListNodeBase<_T, _Key>* node;
    ListNodeBase<_T, _Key>* tmp = Head;

    while(tmp)
    {
        node = tmp, tmp = tmp->Next, node->Next = node->Prev = null;
        DestroyNode(node);
    }

    Head = Tail = null;
    Count = 0;

    InitCurrent();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ int List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLowerBound() const
{
    return LowerBound;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SetLowerBound(int _lb)
{
    LowerBound = _lb;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ int List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetUpperBound() const
{
    return UpperBound;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SetUpperBound(int _ub)
{
    UpperBound = _ub;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
_T& List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator [] (int _i)
{
    AssertRange(_i);

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    ListNodeBase<_T, _Key>* node_base = const_cast<ListNodeBase<_T, _Key>*>(GetNode(_i));
    Node<_T>* node = dynamic_cast<Node<_T>*>(node_base);

    if(node != null)
    {
        return const_cast<_T&>(node->GetData());
    }
    else
    {
        return *(reinterpret_cast<_T*>(dynamic_cast<void*>(node_base)));
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
_T& List<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator [] (const _Key& _key)
{
    ListNodeBase<_T, _Key>* node = Search(_key);

    if(node == null)
    {
        throw XList(XList::OutOfRange);
    }

    return *(reinterpret_cast<_T*>(dynamic_cast<void*>(node)));
}
////////////////////////////////////////////////////////////////////////////////////////
// class ListIterator
// ----- ------------
template <typename _T, typename _Key, typename _Mutex>
ListIterator<_T, _Key, _Mutex>::ListIterator(const ListNodeBase<_T, _Key>* _node, const tchar* _mutex_name, uint _timeout) : CurrentNode(const_cast<ListNodeBase<_T, _Key>*>(_node)), Mutex(_mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _Mutex>
ListIterator<_T, _Key, _Mutex>::ListIterator(const ListIterator& _other, const tchar* _mutex_name, uint _timeout) : Mutex(_mutex_name, _timeout)
{
    operator = (_other);
}

template <typename _T, typename _Key, typename _Mutex>
ListIterator<_T, _Key, _Mutex>::~ListIterator()
{
}

template <typename _T, typename _Key, typename _Mutex>
const ListIterator<_T, _Key, _Mutex>& ListIterator<_T, _Key, _Mutex>::operator = (const ListIterator& _other)
{
    if(this != &_other)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);

        CurrentNode = _other.CurrentNode;
    }

    return *this;
}

template <typename _T, typename _Key, typename _Mutex>
void ListIterator<_T, _Key, _Mutex>::Restart(const ListNodeBase<_T, _Key>* _node)
{
    Synchronization::Guard<_Mutex> guard(Mutex);

    CurrentNode = const_cast<ListNodeBase<_T, _Key>*>(_node);
}

template <typename _T, typename _Key, typename _Mutex>
_T& ListIterator<_T, _Key, _Mutex>::Current()
{
    if(static_cast<int>(*this) == 0)
    {
        throw XList(XList::OutOfRange);
    }

    //
    Node<_T>* node = dynamic_cast<Node<_T>*>(CurrentNode);

    if(node != null)
    {
        return const_cast<_T&>(node->GetData());
    }
    else
    {
        return *(reinterpret_cast<_T*>(dynamic_cast<void*>(CurrentNode)));
    }
}

template <typename _T, typename _Key, typename _Mutex>
_T& ListIterator<_T, _Key, _Mutex>::operator * ()
{
    return Current();
}

template <typename _T, typename _Key, typename _Mutex>
const ListNodeBase<_T, _Key>* ListIterator<_T, _Key, _Mutex>::GetCurrentNode()
{
    return CurrentNode;
}

template <typename _T, typename _Key, typename _Mutex>
ListIterator<_T, _Key, _Mutex>::operator int ()
{
    return CurrentNode != null;
}

template <typename _T, typename _Key, typename _Mutex>
ListNodeBase<_T, _Key>* ListIterator<_T, _Key, _Mutex>::operator ++ (int)
{
    ListNodeBase<_T, _Key>* node;

    if(CurrentNode == null)
    {
        throw XList(XList::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    node = CurrentNode, CurrentNode = CurrentNode->Next;
    return node;
}

template <typename _T, typename _Key, typename _Mutex>
ListNodeBase<_T, _Key>* ListIterator<_T, _Key, _Mutex>::operator ++ ()
{
    if(CurrentNode == null)
    {
        throw XList(XList::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    return (CurrentNode = CurrentNode->Next);
}

template <typename _T, typename _Key, typename _Mutex>
ListNodeBase<_T, _Key>* ListIterator<_T, _Key, _Mutex>::operator -- (int)
{
    if(CurrentNode == null)
    {
        throw XList(XList::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    ListNodeBase<_T, _Key>* node;
    node = CurrentNode, CurrentNode = CurrentNode->Prev;
    return node;
}

template <typename _T, typename _Key, typename _Mutex>
ListNodeBase<_T, _Key>* ListIterator<_T, _Key, _Mutex>::operator -- ()
{
    if(CurrentNode == null)
    {
        throw XList(XList::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    return (CurrentNode = CurrentNode->Prev);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __LIST_INL__

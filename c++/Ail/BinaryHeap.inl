////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BINARY_HEAP_INL__
#define __BINARY_HEAP_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryHeap
// ----- ----------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::BinaryHeap(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::~BinaryHeap()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::SwapNode(TreeNodeBase<_T, _Key>* _n1, TreeNodeBase<_T, _Key>* _n2)
{
    if(_n1 == null || _n2 == null || _n1 == _n2)
    {
        return;
    }

    TreeNodeBase<_T, _Key>* tmp;

    if(_n2 == Root)
    {
        Root = _n1;
    }

    // papa
    if(_n2->Parent != null)
    {
        if(_n2->Parent->Child == _n2)
        {
            _n2->Parent->Child = _n1;
        }
        else
        {
            _n2->Parent->Brother = _n1;
        }
    }

    // children
    if(_n1->Child != null)
    {
        _n1->Child->Parent = _n2;
    }         

    if(_n1->Brother != null)
    {
        _n1->Brother->Parent = _n2;
    }

    // nodes
    bool left = _n1->Parent->Child == _n1;

    _n1->Parent = _n2->Parent;
    _n2->Parent = _n1;

    tmp = _n1->Child,   _n1->Child   = left ?  _n2 : _n2->Child,   _n2->Child   = tmp;
    tmp = _n1->Brother, _n1->Brother = !left ? _n2 : _n2->Brother, _n2->Brother = tmp;

    if(_n1->Child != null)
    {
        _n1->Child->Parent = _n1;
    }         

    if(_n1->Brother != null)
    {
        _n1->Brother->Parent = _n1;
    }         
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::PromoteNode(TreeNodeBase<_T, _Key>* _node)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    while(_node != Root)
    {
        int rc = CompareKey(GetKey(_node), GetKey(_node->Parent));

        if((_MaxHeap && rc <= 0) || (!_MaxHeap && rc >= 0))
        {
            break;
        }
        
        SwapNode(_node, _node->Parent);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const TreeNodeBase<_T, _Key>* BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::Search(const _Key& _key)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    // linear search
    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(Root);

    while(node != null)
    {
        if(CompareKey(GetKey(node), _key) == 0)
        {
            return reinterpret_cast<const TreeNodeBase<_T, _Key>*>(node);
        }
        node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(node);
    }
    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
void BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::AlterNode(TreeNodeBase<_T, _Key>* _node)
{
    // do nothing,
    // but if this operation will violate heap property you should restore the last!
    Synchronization::Guard<_Mutex> guard(Mutex);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::Insert(TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(Root == null)
    {
        Root = _node, ++Count;
        return;
    }

    // phase I (locate)
    //
    const ushort _pivot_      = 16;
    const ushort _queue_size_ = static_cast<ushort>(2+(GetCount() < _pivot_ ? _pivot_ : log(GetCount())));
    //
    uint n    = _queue_size_+1;
    uint head = n;
    uint tail = 0;

    Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(n, 0, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init);
    array.SetState(StateObject::eNoDelete);

    TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(Root);

    // enqueue root
    array[tail++] = node, tail %= n;

    while(head % n != tail)
    {
        // dequeue
        head %= n, node = array[head++];
        array[head-1] = null;

        if(!IsNodeComplete(node))
        {
            break;
        }
        
        // enqueue left
        if(node->Child != null)
        {
            array[tail++] = node->Child, tail %= n;
        }

        // enqueue right
        if(node->Brother != null)
        {
            array[tail++] = node->Brother, tail %= n;
        }
    }

    // phase II (insert)
    _node->Parent = node;

    if(node->Child == null)
    {
        node->Child = _node;
    }
    else
    {
        node->Brother = _node;
    }

    ++Count;

    // phase III (heapify)
    PromoteNode(_node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::Insert(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::Remove(TreeNodeBase<_T, _Key>* _node, bool _destroy)
{
    if(_node == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    TreeNodeBase<_T, _Key>* node = GetLastNode();

    if(node == null)
    {
        return;
    }

    // phase I (swap & relink)
    if(--Count == 0)
    {
        Root = null;
    }
    else if(_node == Root)
    {
        Root = node;
    }

    if(_node->Parent != null)
    {
        if(_node->Parent->Child == _node)
        {
            _node->Parent->Child = node;
        }
        else
        {
            _node->Parent->Brother = node;
        }
    }

    if(_node->Child != null)
    {
        _node->Child->Parent = node;
    }

    if(_node->Brother != null)
    {
        _node->Brother->Parent = node;
    }

    if(node->Parent != null)
    {
        if(node->Parent->Child == node)
        {
            node->Parent->Child = null;
        }
        else
        {
            node->Parent->Brother = null;
        }
    }

    node->Parent = _node->Parent;
    
    if(_node->Child != node)
    {
        node->Child = _node->Child;
    }

    if(_node->Brother != node)
    {
        node->Brother = _node->Brother;
    }

    _node->Child = _node->Brother = null;

    // phase III (heapify)
    for(;;)
    {
        int rc;

        TreeNodeBase<_T, _Key>* tmp = null;

        if(node->Brother == null)
        {
            tmp = node->Child;
        }
        else
        {
            if(node->Child != null)
            {
                rc = CompareKey(GetKey(node->Child), GetKey(node->Brother));

                if((_MaxHeap && rc >= 0) || (!_MaxHeap && rc <= 0))
                {
                    tmp = node->Child;
                }
                else
                {
                    tmp = node->Brother;
                }
            }
        }

        if(tmp == null)
        {
            break;
        }

        rc = CompareKey(GetKey(node), GetKey(tmp));

        if((_MaxHeap && rc >= 0) || (!_MaxHeap && rc <= 0))
        {
            break;
        }

        SwapNode(tmp, node);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::IsNodeComplete(const TreeNodeBase<_T, _Key>* _node) const
{
    if(_node == null)
    {
        return false;
    }
    return _node->Child != null && _node->Brother != null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ TreeNodeBase<_T, _Key>* BinaryHeap<_T, _Key, _KeyExtractor, _Comparator, _MaxHeap, _Mutex, _Allocator>::GetLastNode() const
{
    //
    const short  _pivot_      = 16;
    const ushort _queue_size_ = static_cast<ushort>(2+(GetCount() < _pivot_ ? _pivot_ : log(GetCount())));
    //
    uint count = 0;
    uint n     = _queue_size_+1;
    uint head  = n;
    uint tail  = 0;

    int level = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelIter(BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(Root));

    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetFirstNodeOfLevel(level, Root);
    TreeNodeBase<_T, _Key>* prev = null;

    if(node == null)
    {
        return null;
    }

    Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(n, 0, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init);
    array.SetState(StateObject::eNoDelete);

    node = node != Root ? node->Parent : node;

    // enqueue root
    array[tail++] = node, tail %= n;

    while(head % n != tail)
    {
        // dequeue
        head %= n, node = array[head++];
        array[head-1] = 0;

        prev = node;

        // enqueue left
        if(node->Child != null)
        {
            array[tail++] = node->Child, tail %= n;
        }

        // enqueue right
        if(node->Brother != null)
        {
            array[tail++] = node->Brother, tail %= n;
        }
    }

    return prev;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __BINARY_HEAP_INL__

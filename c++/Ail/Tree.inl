////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TREE_INL__
#define __TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Tree
// ----- ----
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Tree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : Root(null), ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _mutex_name, _timeout)
{
    Count = 0;
    Flags = _flags;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~Tree()
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ TreeNodeBase<_T, _Key>* Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ConstructNode(const _T& _data)
{
    void* p = _Allocator::Allocate(sizeof(TreeNode<_T, _Key>));
    TreeNode<_T, _Key>* node = new (p) TreeNode<_T, _Key>(_data);
    node->ModifyFlags(NodeBase<_T, _Key>::StandardAlloc, 0);
    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::DestroyNode(TreeNodeBase<_T, _Key>* _node)
{
    if(_node != null)
    {
        if(_node->GetFlags() & TreeNodeBase<_T, _Key>::StandardAlloc)
        {
            if(IsShouldDelete())
            {
                delete _node;
            }
        }
        else
        {
            _node->~TreeNodeBase<_T, _Key>(); // virtual dtor OK
            _Allocator::Deallocate(static_cast<TreeNode<_T, _Key>*>(_node)); // casting
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ uint Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetCount() const
{
    return Count;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ uint Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetFlags() const
{
    return Flags;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ModifyFlags(uint _remove, uint _add)
{
    Flags = (Flags & ~_remove) | _add;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::IsEmpty() const
{
    return Root == null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const TreeNodeBase<_T, _Key>* Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetRoot() const
{
    return Root;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TREE_INL__

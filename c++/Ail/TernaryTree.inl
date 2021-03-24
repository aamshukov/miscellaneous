////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TERNARY_TREE_INL__
#define __TERNARY_TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TernaryTree
// ----- -----------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TernaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TernaryTree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TernaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~TernaryTree()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const TreeNodeBase<_T, _Key>* TernaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Search(const _Key& _key)
{
    const TreeNodeBase<_T, _Key>* node;
    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void TernaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(TreeNodeBase<_T, _Key>* _node)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void TernaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void TernaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Remove(TreeNodeBase<_T, _Key>* _node, bool _destroy)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void TernaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Destroy()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TERNARY_TREE_INL__

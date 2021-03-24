////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __T_TREE_INL__
#define __T_TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TTree
// ----- -----
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, uint _PageSize, typename _Mutex, typename _Allocator>
TTree<_T, _Key, _KeyExtractor, _Comparator, _PageSize, _Mutex, _Allocator>::TTree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
    Flags &= ~Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SelfOrganized;
    Flags |= Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, uint _PageSize, typename _Mutex, typename _Allocator>
TTree<_T, _Key, _KeyExtractor, _Comparator, _PageSize, _Mutex, _Allocator>::~TTree()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, uint _PageSize, typename _Mutex, typename _Allocator>
const TreeNodeBase<_T, _Key>* TTree<_T, _Key, _KeyExtractor, _Comparator, _PageSize, _Mutex, _Allocator>::Search(const _Key& _key)
{
    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, uint _PageSize, typename _Mutex, typename _Allocator>
void TTree<_T, _Key, _KeyExtractor, _Comparator, _PageSize, _Mutex, _Allocator>::Add(const _T& _data)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, uint _PageSize, typename _Mutex, typename _Allocator>
void TTree<_T, _Key, _KeyExtractor, _Comparator, _PageSize, _Mutex, _Allocator>::Remove(const _Key& _key)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __T_TREE_INL__

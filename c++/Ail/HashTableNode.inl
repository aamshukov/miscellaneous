////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HASH_TABLE_NODE_INL__
#define __HASH_TABLE_NODE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HashTableNodeBase
// ----- -----------------
template <typename _T, typename _Key> HashTableNodeBase<_T, _Key>::HashTableNodeBase(uint _flags) : NodeBase<_T, _Key>(_flags), Next(null)
{
}

template <typename _T, typename _Key> HashTableNodeBase<_T, _Key>::~HashTableNodeBase()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class HashTableNode
// ----- -------------
template <typename _T, typename _Key> HashTableNode<_T, _Key>::HashTableNode(const _T& _data, uint _flags) : Node<_T>(_data), HashTableNodeBase<_T, _Key>(_flags)
{
}

template <typename _T, typename _Key> HashTableNode<_T, _Key>::~HashTableNode()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HASH_TABLE_NODE_INL__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LIST_NODE_INL__
#define __LIST_NODE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ListNodeBase
// ----- ------------
template <typename _T, typename _Key> ListNodeBase<_T, _Key>::ListNodeBase(uint _flags) : NodeBase<_T, _Key>(_flags), Next(null), Prev(null)
{
}

template <typename _T, typename _Key> ListNodeBase<_T, _Key>::~ListNodeBase()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class ListNode
// ----- --------
template <typename _T, typename _Key> ListNode<_T, _Key>::ListNode(const _T& _data, uint _flags) : Node<_T>(_data), ListNodeBase<_T, _Key>(_flags)
{
}

template <typename _T, typename _Key> ListNode<_T, _Key>::~ListNode()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __LIST_NODE_INL__

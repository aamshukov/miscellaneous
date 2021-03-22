////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NODE_INL__
#define __NODE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class NodeBase
// ----- --------
template <typename _T, typename _Key> NodeBase<_T, _Key>::NodeBase(uint _flags) : Flags(_flags)
{
}

template <typename _T, typename _Key> NodeBase<_T, _Key>::~NodeBase()
{
}

template <typename _T, typename _Key> __INLINE_TEMPLATE__ uint NodeBase<_T, _Key>::GetFlags() const
{
    return Flags;
}

template <typename _T, typename _Key> __INLINE_TEMPLATE__ void NodeBase<_T, _Key>::ModifyFlags(uint _remove, uint _add)
{
    Flags = (Flags & ~_remove) | _add;
}

template <typename _T, typename _Key> bool NodeBase<_T, _Key>::operator < (const _Key&)
{
    return true;
}

template <typename _T, typename _Key> bool NodeBase<_T, _Key>::operator == (const _Key&)
{
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
// class Node
// ----- ----
template <typename _T> Node<_T>::Node(const _T& _data) : Data(_data)
{
}

template <typename _T> Node<_T>::~Node()
{
}

template <typename _T> __INLINE_TEMPLATE__ const _T& Node<_T>::GetData() const
{
    return Data;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __NODE_INL__

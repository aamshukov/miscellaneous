////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TREE_NODE_INL__
#define __TREE_NODE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TreeNodeBase
// ----- ------------
template <typename _T, typename _Key> TreeNodeBase<_T, _Key>::TreeNodeBase(uint _flags) : NodeBase<_T, _Key>(_flags), Parent(null), Brother(null), Child(null)
{
}

template <typename _T, typename _Key> TreeNodeBase<_T, _Key>::~TreeNodeBase()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class TreeNode
// ----- --------
template <typename _T, typename _Key> TreeNode<_T, _Key>::TreeNode(const _T& _data, uint _flags) : Node<_T>(_data), TreeNodeBase<_T, _Key>(_flags)
{
}

template <typename _T, typename _Key> TreeNode<_T, _Key>::~TreeNode()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class TreeNodeDupKey
// ----- --------------
template <typename _T, typename _Key> TreeNodeDupKey<_T, _Key>::TreeNodeDupKey(uint _flags) : TreeNodeBase<_T, _Key>(_flags), Next(null)
{
}

template <typename _T, typename _Key> TreeNodeDupKey<_T, _Key>::~TreeNodeDupKey()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class AATreeNode
// ----- ----------
template <typename _T, typename _Key> AATreeNode<_T, _Key>::AATreeNode(uint _flags) : TreeNodeBase<_T, _Key>(_flags)
{
    Level = 1;
}

template <typename _T, typename _Key> AATreeNode<_T, _Key>::~AATreeNode()
{
}

template <typename _T, typename _Key> uint AATreeNode<_T, _Key>::GetLevel() const
{
    return Level;
}

template <typename _T, typename _Key> void AATreeNode<_T, _Key>::SetLevel(uint _level)
{
    Level = _level;
}
////////////////////////////////////////////////////////////////////////////////////////
// class TTreeNode
// ----- ---------
template <typename _T, typename _Key, uint _PageSize> TTreeNode<_T, _Key, _PageSize>::TTreeNode(uint _flags) : TreeNodeBase<_T, _Key>(_flags)
{
}

template <typename _T, typename _Key, uint _PageSize> TTreeNode<_T, _Key, _PageSize>::~TTreeNode()
{
}

template <typename _T, typename _Key, uint _PageSize> uint TTreeNode<_T, _Key, _PageSize>::GetCount() const
{
    return Count;
}

template <typename _T, typename _Key, uint _PageSize> uint TTreeNode<_T, _Key, _PageSize>::GetThreshold() const
{
    return _PageSize-2;
}

template <typename _T, typename _Key, uint _PageSize> const _T& TTreeNode<_T, _Key, _PageSize>::GetPage() const
{
    return reinterpret_cast<const _T&>(Page);
}

template <typename _T, typename _Key, uint _PageSize> const _T& TTreeNode<_T, _Key, _PageSize>::GetLeft() const
{
    return reinterpret_cast<const _T&>(Page[0]);
}

template <typename _T, typename _Key, uint _PageSize> const _T& TTreeNode<_T, _Key, _PageSize>::GetRight() const
{
    return reinterpret_cast<const _T&>(Page[_PageSize-1]);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TREE_NODE_INL__

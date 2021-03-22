////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HASH_TABLE_NODE_H__
#define __HASH_TABLE_NODE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HashTableNodeBase
// ----- -----------------
template <typename _T, typename _Key> class HashTableNodeBase : virtual public NodeBase<_T, _Key>
{
    typedef HashTableNodeBase<_T, _Key> _Node;

    public:
    _Node*      Next;
    public:
     // ctor/dtor
     explicit   HashTableNodeBase(uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~HashTableNodeBase();
};
////////////////////////////////////////////////////////////////////////////////////////
// class HashTableNode
// ----- -------------
template <typename _T, typename _Key> class HashTableNode : public Node<_T>, public HashTableNodeBase<_T, _Key>
{
    public:
     // ctor/dtor
     explicit   HashTableNode(const _T&, uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~HashTableNode();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HASH_TABLE_NODE_H__

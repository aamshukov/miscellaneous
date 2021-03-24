////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LIST_NODE_H__
#define __LIST_NODE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ListNodeBase
// ----- ------------
template <typename _T, typename _Key> class ListNodeBase : virtual public NodeBase<_T, _Key>
{
    typedef ListNodeBase<_T, _Key> _Node;

    public:
    _Node*      Next;
    _Node*      Prev;
    public:
     // ctor/dtor
     explicit   ListNodeBase(uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~ListNodeBase();
};
////////////////////////////////////////////////////////////////////////////////////////
// class ListNode
// ----- --------
template <typename _T, typename _Key> class ListNode : public ListNodeBase<_T, _Key>, private Node<_T>
{
    public:
     // ctor/dtor
     explicit   ListNode(const _T&, uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~ListNode();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __LIST_NODE_H__

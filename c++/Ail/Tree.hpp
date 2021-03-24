////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TREE_H__
#define __TREE_H__

#include <map>
#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
//  ATTENTION:
//   This implementation of Tree supports two different schemas for holding objects:
//      1. new TreeNodeBase<K> - IsShouldDelete() & TreeBaseNode::StandardAlloc -> delete (default)
//      2. new TreeNode<K>     - _Allocator::Deallocate()
////////////////////////////////////////////////////////////////////////////////////////
// class Tree
// ----- ----
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class Tree : public ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    public:

    enum EFlag
    {
        SelfOrganized = 0x00000001,
        UniqueKey     = 0x00000002,
        LazyRemove    = 0x00000004
    };

    protected:
     uint           Count;
     uint           Flags;
    _Node*          Root;
    protected:
    _Node*          ConstructNode(const _T&);
     void           DestroyNode(_Node*);
    public:
     // ctor/dtor
                    Tree(const _KeyExtractor&, const _Comparator&, uint = 0, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~Tree();

     // access
     uint           GetCount()                  const;

     uint           GetFlags()                  const;
     void           ModifyFlags(uint, uint = 0);

     bool           IsEmpty()                   const;
     const _Node*   GetRoot()                   const;
};
////////////////////////////////////////////////////////////////////////////////////////
// class XTree
// ----- -----
class __DECLSPEC__ XTree : public X
{
    public:

    enum EError
    {
        Failure     = 0x0001,
        OutOfRange  = 0x0002,
        NotUnique   = 0x0004
    };

    public:
        XTree(uint = XTree::Failure);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TREE_H__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class AVLTree
// ----- -------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class AVLTree
        : public BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    protected:
     int            GetBalance(const _Node*);
     void           SetBalance(_Node*, int);
    public:
     // ctor/dtor
                    AVLTree(const _KeyExtractor&, const _Comparator&, uint = Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~AVLTree();

     // protocol
     const _Node*   Search(const _Key&);

     void           Insert(_Node*);
     void           Insert(const _T&);

     void           Remove(_Node*, bool = true);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AVL_TREE_H__

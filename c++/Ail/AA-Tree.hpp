////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AA_TREE_H__
#define __AA_TREE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class AATree
// ----- ------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class AATree : public BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    public:
     // ctor/dtor
                    AATree(const _KeyExtractor&, const _Comparator&, uint = Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~AATree();

     // protocol
     const _Node*   Search(const _Key&);

     void           Insert(_Node*);
     void           Insert(const _T&);

     void           Remove(_Node*, bool = true);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AA_TREE_H__

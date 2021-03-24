////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RedBlackTree
// ----- ------------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown = true, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class RedBlackTree : public BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    private:
     bool           IsRed(const _Node*) const;
     void           SetColor(_Node*, bool);
    public:
     // ctor/dtor
                    RedBlackTree(const _KeyExtractor&, const _Comparator&, uint = Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~RedBlackTree();

     // protocol
     const _Node*   Search(const _Key&);

     void           Insert(_Node*);
     void           Insert(const _T&);

     void           Remove(_Node*, bool = true);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RED_BLACK_TREE_H__

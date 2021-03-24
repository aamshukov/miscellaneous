////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __T_TREE_H__
#define __T_TREE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TTree
// ----- -----
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, uint _PageSize = 256, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class TTree : public AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    public:
     // ctor/dtor
                    TTree(const _KeyExtractor&, const _Comparator&, uint = Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~TTree();

     // protocol
     const _Node*   Search(const _Key&);

     void           Add(const _T&);
     void           Remove(const _Key&);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __T_TREE_H__

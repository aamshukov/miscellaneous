////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SPLAY_TREE_H__
#define __SPLAY_TREE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SplayTree
// ----- ---------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown = true, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class SplayTree : public BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    private:
     static _Node   _Nil_;
    private:
     void           InitNil();
     void           Splay(_Node*);
    protected:
     virtual void   TopDownSplay(_Node*);
     virtual void   BottomUpSplay(_Node*);
    public:
     // ctor/dtor
                    SplayTree(const _KeyExtractor&, const _Comparator&, uint = Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~SplayTree();

     // protocol
     const _Node*   Search(const _Key&);

     void           Insert(_Node*);
     void           Insert(const _T&);

     void           Remove(_Node*, bool = true);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SPLAY_TREE_H__

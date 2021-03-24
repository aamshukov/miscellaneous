////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BINARY_HEAP_H__
#define __BINARY_HEAP_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryHeap
// ----- ----------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _MaxHeap = true, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class BinaryHeap : public BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    private:
     void           SwapNode(_Node*, _Node*);
    protected:
     virtual void   AlterNode(_Node*);  
    public:
     // ctor/dtor
                    BinaryHeap(const _KeyExtractor&, const _Comparator&, uint = 0, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual       ~BinaryHeap();

     // protocol
     const _Node*   Search(const _Key&);

     void           Insert(_Node*);
     void           Insert(const _T&);

     void           Remove(_Node*, bool = true);
     
     bool           IsNodeComplete(const _Node*)  const;
    _Node*          GetLastNode()                 const;

     void           PromoteNode(_Node*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __BINARY_HEAP_H__

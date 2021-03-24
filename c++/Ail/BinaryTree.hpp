////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
typedef void (*__VisitFunc__)(void*);
////////////////////////////////////////////////////////////////////////////////////////
//  Binary (Search) trees:
//      Representation:
//          Linked [Left(Child) & Right(Brother)]
//              Threaded
//          Sequential [Array]
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryTreeBase
// ----- --------------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class BinaryTreeBase : public Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    protected:
     virtual const _Node* Search(const _Key&)           = 0;
     virtual void         Insert(_Node*)                = 0;
     virtual void         Remove(_Node*, bool = true)   = 0;
    public:
     // ctor/dtor
                          BinaryTreeBase(const _KeyExtractor&, const _Comparator&, uint = Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual             ~BinaryTreeBase();
};
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryTree
// ----- ----------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class BinaryTree : public BinaryTreeBase<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    public:

    enum EConst
    {
        ConstStackSize = 256
    };

    enum EForEach
    {
        General          = 0x0001,
        PreOrderRecur    = 0x0002,
        InOrderRecur     = 0x0004,
        PostOrderRecur   = 0x0008,
        PreOrderIter     = 0x0010,
        InOrderIter      = 0x0020,
        PostOrderIter    = 0x0040,
        ThreadedIter     = 0x0080,
        ParentLinkIter   = 0x0100,
        BreadthFirstIter = 0x0200,
        DepthFirstIter   = 0x0400
    };

    protected:
     static int         Compare(const _Node*, const _Node*);
     //
     virtual void      _Destroy();
    public:
     // ctor/dtor
                        BinaryTree(const _KeyExtractor&, const _Comparator&, uint = Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual           ~BinaryTree();

     // access
     bool               IsFull(const _Node*);

     static _Node*      GetLeftMostRecur(const _Node*);
     static _Node*      GetLeftMostIter(const _Node*);

     static _Node*      GetRightMostRecur(const _Node*);
     static _Node*      GetRightMostIter(const _Node*);

     static int         GetHeightRecur(const _Node*);
     static int         GetHeightIter(const _Node*);

     static int         GetWidthRecur(const _Node*);
     static int         GetWidthIter(const _Node*);

     static int         GetDynamicCountRecur(const _Node*);
     static int         GetDynamicCountIter(const _Node*);

     static int         GetLevelRecur(const _Node*);
     static int         GetLevelIter(const _Node*);

     static int         GetLevelCount(int, uint = ConstStackSize); // just iter

     static _Node*      GetFirstNodeOfLevel(int, const _Node*);
     static _Node*      GetNextNodeOfLevel(int, const _Node*, const _Node*, uint = ConstStackSize);
     static _Node*      GetPrevNodeOfLevel(int, const _Node*, const _Node*, uint = ConstStackSize);

     static _Node*      GetPreOrderPredecessor(const _Node*);
     static _Node*      GetPreOrderSuccessor(const _Node*);

     static _Node*      GetPredecessor(const _Node*);
     static _Node*      GetSuccessor(const _Node*);

     static _Node*      GetPostOrderPredecessor(const _Node*);
     static _Node*      GetPostOrderSuccessor(const _Node*);

     // protocol
     bool               HasNode(const _Node*);
     bool               HasData(const _Key&);

     const _Node*       Search(const _Key&);
     //
     void               Insert(_Node*);
     void               Insert(const _T&);

     void               InsertRoot(_Node*);
     void               InsertRoot(const _T&);

     void               MoveToRoot(_Node*);
     void               MoveToRoot(const _Key&);

     void               MoveTo(_Node*, _Node*);
     void               MoveTo(const _Key&, const _Key&);

     void               Remove(_Node*, bool = true);
     void               Remove(const _Key&, bool = true);

     void               RemoveTree(_Node*, bool = false);

     void               Unique(const _Node* = null);
     void               Unique(const _Key&);

     void               Destroy();
     //
     void               RotateLeft(_Node*);
     void               RotateLeft(const _Key&);

     void               RotateRight(_Node*);
     void               RotateRight(const _Key&);
     //
     void               ForEach(__VisitFunc__, ushort = General);

     void               TraversalGeneral(const _Node*, __VisitFunc__);

     void               TraversalPreOrderRecur(const _Node*, __VisitFunc__);
     void               TraversalInOrderRecur(const _Node*, __VisitFunc__);
     void               TraversalPostOrderRecur(const _Node*, __VisitFunc__);

     void               TraversalPreOrderIter(const _Node*, __VisitFunc__, uint = ConstStackSize);
     void               TraversalInOrderIter(const _Node*, __VisitFunc__, uint = ConstStackSize);
     void               TraversalPostOrderIter(const _Node*, __VisitFunc__, uint = ConstStackSize);

     void               TraversalParentLinkInOrderIter(const _Node*, __VisitFunc__);

     void               TraversalBreadthFirstIter(const _Node*, __VisitFunc__, uint = ConstStackSize);
     void               TraversalDepthFirstIter(const _Node*, __VisitFunc__, uint = ConstStackSize);
};
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryTreeIterator
// ----- ------------------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class BinaryTreeIterator
{
    typedef TreeNodeBase<_T, _Key> _Node;

    protected:
    _Mutex                      Mutex;
     mutable _Node*             CurrentNode;
    public:
     // ctor/dtor
                                BinaryTreeIterator(const _Node*, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
                                BinaryTreeIterator(const BinaryTreeIterator&, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual                   ~BinaryTreeIterator();

     const BinaryTreeIterator&  operator = (const BinaryTreeIterator&);

    _T&                         operator * ();

                                operator int ();

    _Node*                      operator ++ (int);
    _Node*                      operator ++ ();
    _Node*                      operator -- (int);
    _Node*                      operator -- ();

     // access
     const _Node*               GetCurrentNode();
    _T&                         Current();

     // protocol
     void                       Restart(const _Node*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __BINARY_TREE_H__

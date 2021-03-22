////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __TREE_NODE_H__
#define __TREE_NODE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class TreeNodeBase
// ----- ------------
template <typename _T, typename _Key> class TreeNodeBase : virtual public NodeBase<_T, _Key>
{
    typedef TreeNodeBase<_T, _Key> _Node;

    public:

    enum EFlag
    {
        Thread     = 0x00000010, // threaded tree
        Red        = 0x00000020, // Red-Black tree (0 - black)
        Removed    = 0x00000040, // lazy remove schema
        AVLBalance = 0x00000300  // AVL balance factor
    };

    public:
    _Node*      Parent;
    _Node*      Brother;
    _Node*      Child;
    public:
     // ctor/dtor
     explicit   TreeNodeBase(uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~TreeNodeBase();
};
////////////////////////////////////////////////////////////////////////////////////////
// class TreeNode
// ----- --------
template <typename _T, typename _Key> class TreeNode : public Node<_T>, public TreeNodeBase<_T, _Key>
{
    public:
     // ctor/dtor
     explicit   TreeNode(const _T&, uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~TreeNode();
};
////////////////////////////////////////////////////////////////////////////////////////
// class TreeNodeDupKey
// ----- --------------
template <typename _T, typename _Key> class TreeNodeDupKey : public TreeNodeBase<_T, _Key>
{
    typedef TreeNodeDupKey<_T, _Key> _Node;

    public:
    _Node*      Next; // single linked list
    public:
     // ctor/dtor
     explicit   TreeNodeDupKey(uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~TreeNodeDupKey();
};
////////////////////////////////////////////////////////////////////////////////////////
// class AATreeNode
// ----- ----------
template <typename _T, typename _Key> class AATreeNode : public TreeNodeBase<_T, _Key>
{
    private:
     uint       Level;
    public:
     // ctor/dtor
     explicit   AATreeNode(uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~AATreeNode();

     // access
     uint       GetLevel()          const;
     void       SetLevel(uint);
};
////////////////////////////////////////////////////////////////////////////////////////
// class TTreeNode
// ----- ---------
template <typename _T, typename _Key, uint _PageSize> class TTreeNode : public TreeNodeBase<_T, _Key>
{
    private:
     uint       Count;                      // how many occupied

    _T          Page[_PageSize];
    public:
     // ctor/dtor
     explicit   TTreeNode(uint = NodeBase<_T, _Key>::StandardAlloc);
     virtual   ~TTreeNode();

     // access
     uint       GetCount()          const;
     uint       GetThreshold()      const;  // min number of keys in a node (just for internal nodes)

     const _T&  GetPage()           const;
     const _T&  GetLeft()           const;
     const _T&  GetRight()          const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __TREE_NODE_H__

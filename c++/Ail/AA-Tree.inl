////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AA_TREE_INL__
#define __AA_TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class AATree
// ----- ------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
AATree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::AATree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
AATree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~AATree()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const TreeNodeBase<_T, _Key>* AATree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Search(const _Key& _key)
{
    const TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Search(_key);

    if(Flags & Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LazyRemove)
    {
        if(node != null)
        {
            return  (node->GetFlags() & TreeNodeBase<_T, _Key>::Removed) ? null : node;
        }
    }

    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void AATree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(Flags & AATree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LazyRemove)
    {
        if(HasNode(_node) && (_node->GetFlags() & TreeNodeBase<_T, _Key>::Removed))
        {
            _node->ModifyFlags(TreeNodeBase<_T, _Key>::Removed, 0);
            return;
        }
    }

    BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(_node);

    TreeNodeBase<_T, _Key>* node = _node;
    TreeNodeBase<_T, _Key>* tmp;

    while(node != null)
    {
        tmp = node->Parent;

        if(node->Parent != null)
        {
            // skew
            if(node->Parent->Child == node && dynamic_cast<AATreeNode<_T, _Key>*>(node)->GetLevel() == dynamic_cast<AATreeNode<_T, _Key>*>(node->Parent)->GetLevel())
            {
                RotateRight(node->Parent);
            }

            // split
            if(node->Parent->Parent != null && dynamic_cast<AATreeNode<_T, _Key>*>(node)->GetLevel() == dynamic_cast<AATreeNode<_T, _Key>*>(node->Parent->Parent)->GetLevel())
            {
                RotateLeft(node->Parent->Parent);
                dynamic_cast<AATreeNode<_T, _Key>*>(node->Parent)->SetLevel(dynamic_cast<AATreeNode<_T, _Key>*>(node->Parent)->GetLevel()+1);
            }
        }

        node = tmp;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void AATree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void AATree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Remove(TreeNodeBase<_T, _Key>* _node, bool _destroy)
{
    if(_node == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(Flags & Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LazyRemove)
    {
        TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(Search(GetKey(_node)));

        if(node != null)
        {
            node->ModifyFlags(0, TreeNodeBase<_T, _Key>::Removed);
        }
    }
    else
    {
        // not implemented
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AA_TREE_INL__

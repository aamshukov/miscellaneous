////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AVL_TREE_INL__
#define __AVL_TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class AVLTree
// ----- -------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::AVLTree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~AVLTree()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ int AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetBalance(const TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return 0;
    }
    
    uint balance = (_node->GetFlags() & TreeNodeBase<_T, _Key>::AVLBalance) >> 8;

    if(balance == 3)
    {
        return -1;
    }
    else if(balance == 1)
    {
        return +1;
    }
    else
    {
        return 0;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SetBalance(TreeNodeBase<_T, _Key>* _node, int _balance)
{
    if(_node != null)
    {
        _node->ModifyFlags(TreeNodeBase<_T, _Key>::AVLBalance, 0);

        if(_balance != 0)
        {
            _node->ModifyFlags(0, (_balance == -1 ? 3 : 1) << 8);
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const TreeNodeBase<_T, _Key>* AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Search(const _Key& _key)
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
__INLINE_TEMPLATE__ void AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(Flags & AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::LazyRemove)
    {
        if(HasNode(_node) && (_node->GetFlags() & TreeNodeBase<_T, _Key>::Removed))
        {
            _node->ModifyFlags(TreeNodeBase<_T, _Key>::Removed, 0);
            return;
        }
    }

    BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(_node);

    if(_node == Root)
    {
        return;
    }

    TreeNodeBase<_T, _Key>* node = _node->Parent;

    bool left = _node->Parent->Child == _node;

    while(node != null)
    {
        if(Abs(GetBalance(node)+(left ? -1 : +1)) > 1)
        {
            // rebalance
            if(GetBalance(node) < 0) // left imbalance
            {
                if(GetBalance(node->Child) == +1)
                {
                    // update balance
                    if(GetBalance(node->Child->Brother) == +1)
                    {
                        SetBalance(node->Child, -1);
                    }
                    else
                    {
                        SetBalance(node->Child, 0);
                    }

                    if(GetBalance(node->Child->Brother) == -1)
                    {
                        SetBalance(node, +1);
                    }
                    else
                    {
                        SetBalance(node, 0);
                    }

                    SetBalance(node->Child->Brother, 0);

                    // RL rotation
                    RotateLeft(node->Child);
                    RotateRight(node);
                }
                else
                {
                    // update balance
                    SetBalance(node, 0);
                    SetBalance(node->Child, 0);

                    // LL rotation
                    RotateRight(node);
                }
            }
            else // right imbalance
            {
                if(GetBalance(node->Brother) == -1)
                {
                    // update balance
                    if(GetBalance(node->Brother->Child) == -1)
                    {
                        SetBalance(node->Brother, +1);
                    }
                    else
                    {
                        SetBalance(node->Brother, 0);
                    }

                    if(GetBalance(node->Brother->Child) == +1)
                    {
                        SetBalance(node, -1);
                    }
                    else
                    {
                        SetBalance(node, 0);
                    }

                    SetBalance(node->Brother->Child, 0);

                    // LR rotation
                    RotateRight(node->Brother);
                    RotateLeft(node);
                }
                else
                {
                    // update balance
                    SetBalance(node, 0);
                    SetBalance(node->Brother, 0);

                    // RR rotation
                    RotateLeft(node);
                }
            }

            break;
        }
        else
        {
            SetBalance(node, GetBalance(node)+(left ? -1 : +1));

            if(GetBalance(node) == 0)
            {
                break;
            }
        }

        if(node != Root)
        {
            left = node->Parent->Child == node;
        }

        node = node->Parent;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void AVLTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Remove(TreeNodeBase<_T, _Key>* _node, bool _destroy)
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
        TreeNodeBase<_T, _Key>* entry;
        TreeNodeBase<_T, _Key>* node;
        TreeNodeBase<_T, _Key>* tmp;

        // phase I (locate & remove)
        if(_node->Child == null || _node->Brother == null)
        {
            // node has at most 1 child
            node  = _node;
            entry = node->Parent;
        }
        else
        {
            // node has 2 children
            entry = node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(_node->Brother);

            SetBalance(entry, GetBalance(_node));

            if(entry->Parent != _node)
            {
                entry = entry->Parent;
            }
        }

        // splice out
        if(node->Child != null)
        {
            tmp = node->Child;
        }
        else
        {
            tmp = node->Brother;
        }

        if(tmp != null)
        {
            tmp->Parent = node->Parent;
        }

        if(node->Parent == null)
        {
            Root = tmp;
            SetBalance(Root, 0);
        }
        else if(node == node->Parent->Child)
        {
            node->Parent->Child = tmp;
        }
        else
        {
            node->Parent->Brother = tmp;
        }

        // relink
        //if(!(_node->GetKey() == node->GetKey())) // !=
        if(_node != node)
        {
            // it's more efficient to relink the node than copy out ! ...
            node->Parent  = _node->Parent;
            node->Child   = _node->Child;
            node->Brother = _node->Brother;

            if(_node->Parent != null)
            {
                if(_node == _node->Parent->Child)
                {
                    _node->Parent->Child = node;
                }
                else
                {
                    _node->Parent->Brother = node;
                }
            }
            else
            {
                Root = node;
            }

            if(_node->Child != null)
            {
                _node->Child->Parent = node;
            }

            if(_node->Brother != null)
            {
                _node->Brother->Parent = node;
            }
        }

        --Count;

        bool left;
        bool height;

        if(entry != null)
        {
            left = CompareKey(GetKey(node), GetKey(entry)) < 0;
        }

        // destroy
        if(_destroy)
        {
            DestroyNode(_node);
        }

        // phase II (rebalance)
        while(entry != null)
        {
            node = entry->Parent; // get next parent

            if(Abs(GetBalance(entry)+(!left ? -1 : +1)) > 1)
            {
                // rebalance
                if(GetBalance(entry) < 0) // left imbalance
                {
                    if(GetBalance(entry->Child) == +1)
                    {
                        // update balance
                        if(GetBalance(entry->Child->Brother) == +1)
                        {
                            SetBalance(entry->Child, -1);
                        }
                        else
                        {
                            SetBalance(entry->Child, 0);
                        }

                        if(GetBalance(entry->Child->Brother) == -1)
                        {
                            SetBalance(entry, +1);
                        }
                        else
                        {
                            SetBalance(entry, 0);
                        }

                        SetBalance(entry->Child->Brother, 0);

                        // RL rotation
                        RotateLeft(entry->Child);
                        RotateRight(entry);

                        height = true; // always
                    }
                    else
                    {
                        // see if left subtree is balanced
                        if(GetBalance(entry->Child) == 0)
                        {
                            height = false;
                        }
                        else
                        {
                            height = true;
                        }

                        // update balance
                        SetBalance(entry, 0);
                        SetBalance(entry->Child, 0);

                        // LL rotation
                        RotateRight(entry);
                    }
                }
                else // right imbalance
                {
                    if(GetBalance(entry->Brother) == -1)
                    {
                        // update balance
                        if(GetBalance(entry->Brother->Child) == -1)
                        {
                            SetBalance(entry->Brother, +1);
                        }
                        else
                        {
                            SetBalance(entry->Brother, 0);
                        }

                        if(GetBalance(entry->Brother->Child) == +1)
                        {
                            SetBalance(entry, -1);
                        }
                        else
                        {
                            SetBalance(entry, 0);
                        }

                        SetBalance(entry->Brother->Child, 0);

                        // LR rotation
                        RotateRight(entry->Brother);
                        RotateLeft(entry);

                        height = true; // always
                    }
                    else
                    {
                        // see if right subtree is balanced
                        if(GetBalance(entry->Brother) == 0)
                        {
                            height = false;
                        }
                        else
                        {
                            height = true;
                        }

                        // update balance
                        SetBalance(entry, 0);
                        SetBalance(entry->Brother, 0);

                        // RR rotation
                        RotateLeft(entry);
                    }
                }
            }
            else
            {
                height = GetBalance(entry) != 0;

                SetBalance(entry, GetBalance(entry)+(!left ? -1 : +1));
            }

            if(!height || node == null)
            {
                break;
            }

            left  = CompareKey(GetKey(entry), GetKey(node)) < 0;
            entry = node;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AVL_TREE_INL__

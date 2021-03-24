////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RED_BLACK_TREE_INL__
#define __RED_BLACK_TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class RedBlackTree
// ----- ------------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::RedBlackTree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::~RedBlackTree()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::IsRed(const TreeNodeBase<_T, _Key>* _node) const
{
    if(_node != null)
    {
        return (_node->GetFlags() & TreeNode<_T, _Key>::Red) != 0;
    }
    return false;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::SetColor(TreeNodeBase<_T, _Key>* _node, bool _color)
{
    if(_node != null)
    {
        _node->ModifyFlags(TreeNode<_T, _Key>::Red, 0);
        _node->ModifyFlags(0, _color ? TreeNode<_T, _Key>::Red : 0);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const TreeNodeBase<_T, _Key>* RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Search(const _Key& _key)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
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

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Insert(TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return;
    }

    if(_TopDown)
    {
    }
    else
    {
        TreeNodeBase<_T, _Key>* tmp;

        // phase I (insert)
        BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(_node);

        // phase II (fixup)
        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        SetColor(_node, true);

        while(_node != Root && IsRed(_node->Parent))
        {
            if(_node->Parent == _node->Parent->Parent->Child)
            {
                tmp = _node->Parent->Parent->Brother;

                if(IsRed(tmp))
                {
                    SetColor(_node->Parent, false);
                    SetColor(tmp, false);
                    SetColor(_node->Parent->Parent, true);
                    _node = _node->Parent->Parent;
                }
                else
                {
                    if(_node == _node->Parent->Brother)
                    {
                        _node = _node->Parent;
                        RotateLeft(_node);
                    }

                    SetColor(_node->Parent, false);
                    SetColor(_node->Parent->Parent, true);
                    RotateRight(_node->Parent->Parent);
                }
            }
            else
            {
                tmp = _node->Parent->Parent->Child;

                if(IsRed(tmp))
                {
                    SetColor(_node->Parent, false);
                    SetColor(tmp, false);
                    SetColor(_node->Parent->Parent, true);
                    _node = _node->Parent->Parent;
                }
                else
                {
                    if(_node == _node->Parent->Child)
                    {
                        _node = _node->Parent;
                        RotateRight(_node);
                    }

                    SetColor(_node->Parent, false);
                    SetColor(_node->Parent->Parent, true);
                    RotateLeft(_node->Parent->Parent);
                }
            }
        }

        SetColor(Root, false);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Insert(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void RedBlackTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Remove(TreeNodeBase<_T, _Key>* _node, bool _destroy)
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
        if(_TopDown)
        {
        }
        else
        {
            //
            static TreeNodeBase<_T, _Key> _nil_;
            //
            TreeNodeBase<_T, _Key>* node;
            TreeNodeBase<_T, _Key>* tmp;

            // phase I (find out node to splice out)
            if(_node->Child == null || _node->Brother == null)
            {
                node = _node; // node has at most 1 child
            }
            else
            {
                node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(_node); // node has 2 children
            }

            // phase II (splice out)
            if(node == null)
            {
                return;
            }

            if(node->Child != null)
            {
                tmp = node->Child;
            }
            else if(node->Brother != null)
            {
                tmp = node->Brother;
            }
            else
            {
                tmp = &_nil_;
            }

            tmp->Parent = node->Parent;

            if(node->Parent == null)
            {
                Root = tmp != &_nil_ ? tmp : null;
            }
            else if(node == node->Parent->Child)
            {
                node->Parent->Child = tmp;
            }
            else
            {
                node->Parent->Brother = tmp;
            }

            bool prev_color = IsRed(node);

            // phase III (relink)
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

                SetColor(node, IsRed(_node));
            }

            // phase IV (fixup)
            if(Root != null && !prev_color)//!IsRed(prev_color/*node*/))
            {
                TreeNodeBase<_T, _Key>* sibling;

                while(tmp != Root && !IsRed(tmp))
                {
                    if(tmp == tmp->Parent->Child)
                    {
                        sibling = tmp->Parent->Brother;

                        if(IsRed(sibling))
                        {
                            SetColor(tmp->Parent, true);
                            SetColor(sibling, false);
                            RotateLeft(tmp->Parent);

                            sibling = tmp->Parent->Brother;
                        }

                        if(!IsRed(sibling->Child) && !IsRed(sibling->Brother))
                        {
                            SetColor(sibling, true);

                            tmp = tmp->Parent;
                        }
                        else
                        {
                            if(!IsRed(sibling->Brother))
                            {
                                SetColor(sibling->Child, false);
                                SetColor(sibling, true);
                                RotateRight(sibling);

                                sibling = tmp->Parent->Brother;
                            }

                            SetColor(sibling, IsRed(tmp->Parent));
                            SetColor(tmp->Parent, false);
                            SetColor(sibling->Brother, false);
                            RotateLeft(tmp->Parent);

                            tmp = Root;
                        }
                    }
                    else
                    {
                        sibling = tmp->Parent->Child;

                        if(IsRed(sibling))
                        {
                            SetColor(tmp->Parent, true);
                            SetColor(sibling, false);
                            RotateRight(tmp->Parent);

                            sibling = tmp->Parent->Child;
                        }

                        if(!IsRed(sibling->Brother) && !IsRed(sibling->Child))
                        {
                            SetColor(sibling, true);

                            tmp = tmp->Parent;
                        }
                        else
                        {
                            if(!IsRed(sibling->Child))
                            {
                                SetColor(sibling->Brother, false);
                                SetColor(sibling, true);
                                RotateLeft(sibling);

                                sibling = tmp->Parent->Child;
                            }

                            SetColor(sibling, IsRed(tmp->Parent));
                            SetColor(tmp->Parent, false);
                            SetColor(sibling->Child, false);
                            RotateRight(tmp->Parent);

                            tmp = Root;
                        }
                    }
                }

                SetColor(tmp, false);
            }
            // remove _nil_ links
            if(_nil_.Parent != null)
            {
                if(_nil_.Parent->Child == &_nil_)
                {
                    _nil_.Parent->Child = null;
                }
                else if(_nil_.Parent->Brother == &_nil_)
                {
                    _nil_.Parent->Brother = null;
                }

                _nil_.Parent = null;
            }

            // phase V (destroy node) eventually ! ...
            if(_destroy)
            {
                DestroyNode(_node);
            }

            --Count;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RED_BLACK_TREE_INL__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SPLAY_TREE_INL__
#define __SPLAY_TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SplayTree
// ----- ---------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key> SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::_Nil_;
//
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::SplayTree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
    Flags &= ~Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SelfOrganized;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::~SplayTree()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::InitNil()
{
    _Nil_.Parent = _Nil_.Child = _Nil_.Brother = null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Splay(TreeNodeBase<_T, _Key>* _node)
{
    if(_TopDown)
    {
        TopDownSplay(_node);
    }
    else
    {
        BottomUpSplay(_node);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::TopDownSplay(TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null || Root == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    TreeNodeBase<_T, _Key>* lt; // left tree max
    TreeNodeBase<_T, _Key>* rt; // right tree min

    InitNil();

    lt = rt = &_Nil_;

    for(;;)
    {
        int rc = CompareKey(GetKey(_node), GetKey(Root));

        if(rc < 0)
        {
            if(Root->Child != null && CompareKey(GetKey(_node), GetKey(Root->Child)) < 0)
            {
                RotateRight(Root);
            }

            if(Root->Child == null)
            {
                break;
            }

            rt->Child = Root;

            if(rt != null)
            {
                Root->Parent = rt;
            }

            rt = Root;

            Root = Root->Child;
        }
        else if(rc > 0)
        {
            if(Root->Brother != null && CompareKey(GetKey(Root->Brother), GetKey(_node)) < 0)
            {
                RotateLeft(Root);
            }

            if(Root->Brother == null)
            {
                break;
            }

            lt->Brother = Root;

            if(lt != null)
            {
                Root->Parent = lt;
            }

            lt = Root;

            Root = Root->Brother;
        }
        else
        {
            break;
        }

        if(Root == null)
        {
            break;
        }
    }

    lt->Brother = Root->Child;

    if(lt != null && Root->Child != null)
    {
        Root->Child->Parent = lt;
    }

    rt->Child = Root->Brother;

    if(rt != null && Root->Brother != null)
    {
        Root->Brother->Parent = rt;
    }

    Root->Child = _Nil_.Brother;

    if(_Nil_.Brother != null)
    {
        _Nil_.Brother->Parent = Root;
    }

    Root->Brother = _Nil_.Child;

    if(_Nil_.Child != null)
    {
        _Nil_.Child->Parent = Root;
    }

    Root->Parent = null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::BottomUpSplay(TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null || Root == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    while(_node != Root)
    {
        if(_node->Parent->Parent == null)
        {
            // zig
            if(CompareKey(GetKey(_node), GetKey(_node->Parent)) < 0)
            {
                RotateRight(_node->Parent);
            }
            else
            {
                RotateLeft(_node->Parent);
            }
        }
        else
        {
            if(CompareKey(GetKey(_node), GetKey(_node->Parent->Parent)) < 0)
            {
                if(CompareKey(GetKey(_node), GetKey(_node->Parent)) < 0)
                {
                    // zig-zig (left)
                    RotateRight(_node->Parent->Parent);
                    RotateRight(_node->Parent);
                }
                else
                {
                    // zig-zag (left)
                    RotateLeft(_node->Parent);
                    RotateRight(_node->Parent);
                }
            }
            else
            {
                if(CompareKey(GetKey(_node->Parent), GetKey(_node)) < 0)
                {
                    // zig-zig (right)
                    RotateLeft(_node->Parent->Parent);
                    RotateLeft(_node->Parent);
                }
                else
                {
                    // zig-zag (right)
                    RotateRight(_node->Parent);
                    RotateLeft(_node->Parent);
                }
            }
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const TreeNodeBase<_T, _Key>* SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Search(const _Key& _key)
{
    if(Root == null)
    {
        return null;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(_TopDown)
    {
        TreeNodeBase<_T, _Key>* lt; // left tree max
        TreeNodeBase<_T, _Key>* rt; // right tree min

        InitNil();

        lt = rt = &_Nil_;

        for(;;)
        {
            int rc = CompareKey(GetKey(Root), _key);

            if(rc > 0)
            {
                if(Root->Child != null && CompareKey(GetKey(Root->Child), _key) > 0)
                {
                    RotateRight(Root);
                }

                if(Root->Child == null)
                {
                    break;
                }

                rt->Child = Root;

                if(rt != null)
                {
                    Root->Parent = rt;
                }

                rt = Root;

                Root = Root->Child;
            }
            else if(rc < 0)
            {
                if(Root->Brother != null && CompareKey(GetKey(Root->Brother), _key) < 0)
                {
                    RotateLeft(Root);
                }

                if(Root->Brother == null)
                {
                    break;
                }

                lt->Brother = Root;

                if(lt != null)
                {
                    Root->Parent = lt;
                }

                lt = Root;

                Root = Root->Brother;
            }
            else
            {
                break;
            }
        }

        lt->Brother = Root->Child;

        if(lt != null && Root->Child != null)
        {
            Root->Child->Parent = lt;
        }

        rt->Child = Root->Brother;

        if(rt != null && Root->Brother != null)
        {
            Root->Brother->Parent = rt;
        }

        Root->Child = _Nil_.Brother;

        if(_Nil_.Brother != null)
        {
            _Nil_.Brother->Parent = Root;
        }

        Root->Brother = _Nil_.Child;

        if(_Nil_.Child != null)
        {
            _Nil_.Child->Parent = Root;
        }

        Root->Parent = null;

        return CompareKey(GetKey(Root), _key) == 0 ? Root : null;
    }
    else
    {
        TreeNodeBase<_T, _Key>* node = Root;
        TreeNodeBase<_T, _Key>* tmp  = null;

        // phase I (locate)
        while(node != null)
        {
            tmp = node;

            int rc = CompareKey(GetKey(node), _key);

            if(rc == 0)
            {
                break;
            }
            else if(rc < 0) // opposite, because Compare compares node->Key & _key
            {
                node = node->Brother;
            }
            else
            {
                node = node->Child;
            }
        }

        // phase II (splay)
        BottomUpSplay(tmp);
    
        return node;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Insert(TreeNodeBase<_T, _Key>* _node)
{
    if(_TopDown)
    {
        if(_node == null)
        {
            return;
        }

        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        if(Root == null)
        {
            Root = _node;
        }
        else
        {
            Splay(_node);

            int rc = CompareKey(GetKey(_node), GetKey(Root));

            if(rc < 0)
            {
                _node->Child = Root->Child;

                if(Root->Child != null)
                {
                    Root->Child->Parent = _node;
                }

                _node->Brother = Root;
                Root->Parent   = _node;
                Root->Child    = null;
                Root           = _node;
            }
            else if(rc > 0)
            {
                _node->Brother = Root->Brother;

                if(Root->Brother != null)
                {
                    Root->Brother->Parent = _node;
                }

                _node->Child  = Root;
                Root->Parent  = _node;
                Root->Brother = null;
                Root          = _node;
            }
            else
            {
                if(Flags & Tree<_Key, _KeyExtractor, _Comparator, _Allocator>::UniqueKey)
                {
                    throw XTree(XTree::NotUnique);
                }

                return; // or create linked list ...
            }
        }

        ++Count;
    }
    else
    {
        BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(_node);
        Splay(_node);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Insert(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, bool _TopDown, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void SplayTree<_T, _Key, _KeyExtractor, _Comparator, _TopDown, _Mutex, _Allocator>::Remove(TreeNodeBase<_T, _Key>* _node, bool _destroy)
{
    Splay(_node);
    BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Remove(_node, _destroy);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SPLAY_TREE_INL__

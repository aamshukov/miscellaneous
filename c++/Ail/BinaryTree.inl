////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BINARY_TREE_INL__
#define __BINARY_TREE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryTreeBase
// ----- --------------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTreeBase<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::BinaryTreeBase(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTreeBase<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~BinaryTreeBase()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryTree
// ----- ----------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::BinaryTree(const _KeyExtractor& _kx, const _Comparator& _cmp, uint _flags, const tchar* _mutex_name, uint _timeout) : BinaryTreeBase<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _flags, _mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~BinaryTree()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Compare(const TreeNodeBase<_T, _Key>* _node1, const TreeNodeBase<_T, _Key>* _node2)
{
    if(_node1 == null || _node2 == null)
    {
        return 0;
    }

    return CompareKey(GetKey(_node1), GetKey(_node2));
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
bool BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::IsFull(const TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return true;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    // count == 2^(h+1)-1
    int count = _node == Root ? GetCount() : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetDynamicCountIter(_node);
    return count == static_cast<int>(pow(2, BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHeightIter(_node)+1)-1);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostRecur(const TreeNodeBase<_T, _Key>* _node)
{
    return _node == null ? null : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostRecur(_node->Child);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(const TreeNodeBase<_T, _Key>* _node)
{
    TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_node);

    if(node != null)
    {
        while(node->Child != null)
        {
            node = node->Child;
        }
    }

    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetRightMostRecur(const TreeNodeBase<_T, _Key>* _node)
{
    return _node == null ? null : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetRightMostRecur(_node->Brother);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetRightMostIter(const TreeNodeBase<_T, _Key>* _node)
{
    TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_node);

    if(node != null)
    {
        while(node->Brother != null)
        {
            node = node->Brother;
        }
    }

    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHeightRecur(const TreeNodeBase<_T, _Key>* _node)
{
    return _node == null ? -1 : Max(BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHeightRecur(_node->Child), BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHeightRecur(_node->Brother))+1;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHeightIter(const TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return 0;
    }

    int height = 0;

    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(_node);

    while(node != null)
    {
        int tmp = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelIter(node);

        if(tmp > height)
        {
            height = tmp;
        }

        node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(node);
    }

    return height;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetWidthRecur(const TreeNodeBase<_T, _Key>* _node)
{
    if(_node != null)
    {
        int lw = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetWidthRecur(_node->Child);     // left diameter
        int rw = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetWidthRecur(_node->Brother);   // right diameter
        int lh = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHeightRecur(_node->Child);    // left height
        int rh = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetHeightRecur(_node->Brother);  // right height

        // longest path through root
        int path = lh+rh+1;

        return Max(lw, Max(rw, path));
    }

    return 0;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetWidthIter(const TreeNodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        return 0;
    }

    int width = 0;

    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(_node);

    while(node != null)
    {
        int tmp = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelCount(BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelIter(node));

        if(tmp > width)
        {
            width = tmp;
        }

        width = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(node);
    }

    return width;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetDynamicCountRecur(const _Node* _node)
{
    return _node == null ? 0 : BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetDynamicCountRecur(_node->Child)+BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetDynamicCountRecur(_node->Brother)+1;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetDynamicCountIter(const _Node* _node)
{
    if(_node == null)
    {
        return 0;
    }

    uint count = 0;

    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(_node);

    while(node != null)
    {
        node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(node);
        ++count;
    }

    return count;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelRecur(const _Node* _node)
{
    if(_node == Root)
    {
        return 0;
    }
    return BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelRecur(_node->Parent)+1;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelIter(const _Node* _node)
{
    if(_node == null)
    {
        return 0;
    }

    int level = 0;

    TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_node);

    while(node != null)
    {
        node = node->Parent, ++level;
    }

    return level > 0 ? level-1 : 0;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
int BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelCount(int _level, uint _queue_size)
{
    //
    const short _delta_      = 16;
    const uint  _queue_size_ = _queue_size == 0 ? Count : _queue_size;
    //
    uint count = 0;
    uint n     = _queue_size_+1;
    uint head  = n;
    uint tail  = 0;

    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetFirstNodeOfLevel(_level);

    if(node == null)
    {
        return 0;
    }

    Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(n, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init);
    array.SetState(StateObject::NoDelete);

    // enqueue root
    array[tail++] = node, tail %= n;

    while(head % n != tail)
    {
        // dequeue
        head %= n, node = array[head++];
        array[head-1] = 0;

        if(BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelIter(node) != _level)
        {
            break;
        }

        ++count;

        // enqueue left
        if(node->Child != null)
        {
            array[tail++] = node->Child, tail %= n;
        }

        // enqueue right
        if(node->Brother != null)
        {
            array[tail++] = node->Brother, tail %= n;
        }
    }

    return count;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetFirstNodeOfLevel(int _level, const TreeNodeBase<_T, _Key>* _root)
{
    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(_root);

    while(node != null)
    {
        if(BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLevelIter(node) == _level)
        {
            return node;
        }

        node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(node);
    }

    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetNextNodeOfLevel(int _level, const TreeNodeBase<_T, _Key>* _root, const TreeNodeBase<_T, _Key>* _node, uint _queue_size)
{
    if(_node == null)
    {
        return null;
    }

    //
    const short _delta_      = 16;
    const uint  _queue_size_ = _queue_size == 0 ? Count : _queue_size;
    //
    uint count = 0;
    uint n     = _queue_size_+1;
    uint head  = n;
    uint tail  = 0;

    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetFirstNodeOfLevel(_level, _root);
    TreeNodeBase<_T, _Key>* prev = null;

    if(node == null)
    {
        return null;
    }

    Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(n, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init);
    array.SetState(StateObject::NoDelete);

    node = node->Parent != null ? node->Parent : node;

    // enqueue root
    array[tail++] = node, tail %= n;

    while(head % n != tail)
    {
        // dequeue
        head %= n, node = array[head++];
        array[head-1] = 0;

        if(prev == _node)
        {
            return node;
        }

        prev = node;

        // enqueue left
        if(node->Child != null)
        {
            array[tail++] = node->Child, tail %= n;
        }

        // enqueue right
        if(node->Brother != null)
        {
            array[tail++] = node->Brother, tail %= n;
        }
    }

    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPrevNodeOfLevel(int _level, const TreeNodeBase<_T, _Key>* _root, const TreeNodeBase<_T, _Key>* _node, uint _queue_size)
{
    if(_node == null)
    {
        return null;
    }

    //
    const short _delta_      = 16;
    const uint  _queue_size_ = _queue_size == 0 ? Count : _queue_size;
    //
    uint count = 0;
    uint n     = _queue_size_+1;
    uint head  = n;
    uint tail  = 0;

    TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetFirstNodeOfLevel(_level, _root);
    TreeNodeBase<_T, _Key>* prev = null;

    if(node == null)
    {
        return null;
    }

    Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(n, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init);
    array.SetState(StateObject::NoDelete);

    node = node->Parent != null ? node->Parent : node;

    // enqueue root
    array[tail++] = node, tail %= n;

    while(head % n != tail)
    {
        // dequeue
        head %= n, node = array[head++];
        array[head-1] = 0;

        if(prev == _node)
        {
            return prev;
        }

        prev = node;

        // enqueue left
        if(node->Child != null)
        {
            array[tail++] = node->Child, tail %= n;
        }

        // enqueue right
        if(node->Brother != null)
        {
            array[tail++] = node->Brother, tail %= n;
        }
    }

    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPreOrderPredecessor(const TreeNodeBase<_T, _Key>* _node)
{
    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPreOrderSuccessor(const TreeNodeBase<_T, _Key>* _node)
{
    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPredecessor(const TreeNodeBase<_T, _Key>* _node)
{
    // NOTICE: return inorder predecessor
    if(_node != null)
    {
        if(_node->Child != null)
        {
            return BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetRightMostIter(_node->Child);
        }

        TreeNodeBase<_T, _Key>* node = _node->Parent;
        TreeNodeBase<_T, _Key>* tmp  = const_cast<TreeNodeBase<_T, _Key>*>(_node);

        while(node != null && tmp == node->Child)
        {
            tmp  = node;
            node = node->Parent;
        }

        return node;
    }

    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(const TreeNodeBase<_T, _Key>* _node)
{
    // NOTICE: return inorder successor
    if(_node != null)
    {
        if(_node->Brother != null)
        {
            return BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(_node->Brother);
        }

        TreeNodeBase<_T, _Key>* node = _node->Parent;
        TreeNodeBase<_T, _Key>* tmp  = const_cast<TreeNodeBase<_T, _Key>*>(_node);

        while(node != null && tmp == node->Brother)
        {
            tmp  = node;
            node = node->Parent;
        }

        return node;
    }

    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPostOrderPredecessor(const TreeNodeBase<_T, _Key>* _node)
{
    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPostOrderSuccessor(const TreeNodeBase<_T, _Key>* _node)
{
    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
bool BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::HasNode(const TreeNodeBase<_T, _Key>* _node)
{
    if(_node != null)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, Synchronization::NullThreadMutex<> > iter(BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(Root));

        for(; iter; iter++)
        {
            if(iter.GetCurrentNode() == _node)
            {
                return true;
            }
        }
    }
    return false;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
bool BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::HasData(const _Key& _key)
{
    return Search(_key) != null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
const TreeNodeBase<_T, _Key>* BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Search(const _Key& _key)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    TreeNodeBase<_T, _Key>* node = Root;

    while(node != null)
    {
        GetKey(node);

        int rc = CompareKey(GetKey(node), _key);

        if(rc == 0)
        {
            if(Flags & Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SelfOrganized)
            {
                MoveToRoot(node);
            }
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

    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(TreeNodeBase<_T, _Key>* _node)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    TreeNodeBase<_T, _Key>* node = null;
    TreeNodeBase<_T, _Key>* tmp  = Root;

    bool left;

    // phase I (locate)
    while(tmp != null)
    {
        node = tmp;

        int rc = CompareKey(GetKey(_node), GetKey(tmp));

        if(rc < 0)
        {
            tmp  = tmp->Child;
            left = true;
        }
        else if(rc == 0)
        {
            if(Flags & Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::UniqueKey)
            {
                throw XTree(XTree::NotUnique);
            }

            return; // or create linked list ...
        }
        else
        {
            tmp  = tmp->Brother;
            left = false;
        }
    }

    // phase II (insert)
    _node->Parent = node;

    if(node == null)
    {
        Root = _node;
    }
    else
    {
        if(left)
        {
            node->Child = _node;
        }
        else
        {
            node->Brother = _node;
        }
    }

    ++Count;

    if(Flags & Tree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SelfOrganized)
    {
        MoveToRoot(_node);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::InsertRoot(TreeNodeBase<_T, _Key>* _new_root)
{
    if(_new_root == null || _new_root == Root)
    {
        return;
    }

    Insert(_new_root);
    MoveToRoot(_new_root);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::InsertRoot(const _T& _data)
{
    TreeNodeBase<_T, _Key>* node = ConstructNode(_data);
    InsertRoot(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveToRoot(TreeNodeBase<_T, _Key>* _new_root)
{
    if(_new_root == null || Root == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    while(_new_root != Root)
    {
        if(_new_root->Parent->Child == _new_root)
        {
            RotateRight(_new_root->Parent);
        }
        else
        {
            RotateLeft(_new_root->Parent);
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveToRoot(const _Key& _key)
{
    MoveToRoot(const_cast<TreeNodeBase<_T, _Key>*>(Search(_key)));
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveTo(TreeNodeBase<_T, _Key>* _new_root, TreeNodeBase<_T, _Key>* _old_root)
{
    if(_new_root == null || _old_root == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    while(_new_root != null && _old_root->Parent != _new_root)
    {
        if(_new_root->Parent->Child == _new_root)
        {
            tree.RotateRight(_new_root->Parent);
        }
        else
        {
            tree.RotateLeft(_new_root->Parent);
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::MoveTo(const _Key& _new_key, const _Key& _old_key)
{
    MoveTo(const_cast<TreeNodeBase<_T, _Key>*>(Search(_new_key)), const_cast<TreeNodeBase<_T, _Key>*>(Search(_old_key)));
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Remove(TreeNodeBase<_T, _Key>* _node, bool _destroy)
{
    if(_node != null)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);
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
        }
        else if(node == node->Parent->Child)
        {
            node->Parent->Child = tmp;
        }
        else
        {
            node->Parent->Brother = tmp;
        }

        // phase III (relink)
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

        if(_destroy)
        {
            DestroyNode(_node);
        }

        --Count;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Remove(const _Key& _key, bool _destroy)
{
    Remove(const_cast<TreeNodeBase<_T, _Key>*>(Search(_key)), _destroy);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::RemoveTree(TreeNodeBase<_T, _Key>* _node, bool _destroy)
{
    static TreeNodeBase<_T, _Key>* _tmp_;
    //
    while(_node != null)
    {
        RemoveTree(_node->Brother, _destroy);
        
        _tmp_ = _node->Child;
        
        if(_destroy)
        {
            DestroyNode(_node);
        }
        else
        {
            Remove(_node);
        }

        _node = _tmp_;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Unique(const TreeNodeBase<_T, _Key>* _node)
{
    if(Root == null)
    {
        return;
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    TreeNodeBase<_T, _Key>* node;
    TreeNodeBase<_T, _Key>* tmp = _node != null ? const_cast<TreeNodeBase<_T, _Key>*>(_node) : GetLeftMostIter(Root);

    for(node = tmp; (node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(node)) != null; node = tmp)
    {
        if(_node != null ? _node->GetKey() : tmp->GetKey() == node->GetKey())
        {
            Remove(node);
        }
        else
        {
            tmp = node;
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Unique(const _Key& _key)
{
    Unique(const_cast<TreeNodeBase<_T, _Key>*>(Search(_key)));
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Destroy()
{
    _Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::_Destroy()
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    RemoveTree(Root, true);
    //
    Count = 0;
    Root  = null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::RotateLeft(TreeNodeBase<_T, _Key>* _node)
{
    if(_node != null)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        TreeNodeBase<_T, _Key>* tmp = _node->Brother;

        if(tmp == null)
        {
            return;
        }

        _node->Brother = tmp->Child;

        if(tmp->Child != null)
        {
            tmp->Child->Parent = _node;
        }

        tmp->Parent = _node->Parent;

        if(_node == Root)
        {
            Root = tmp;
        }
        else if(_node == _node->Parent->Child)
        {
            _node->Parent->Child = tmp;
        }
        else
        {
            _node->Parent->Brother = tmp;
        }

        tmp->Child = _node, _node->Parent = tmp;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::RotateLeft(const _Key& _key)
{
    RotateLeft(const_cast<TreeNodeBase<_T, _Key>*>(Search(_key)));
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::RotateRight(TreeNodeBase<_T, _Key>* _node)
{
    if(_node != null)
    {
        Synchronization::Guard<_Mutex> guard(Mutex);
        //
        TreeNodeBase<_T, _Key>* tmp = _node->Child;

        if(tmp == null)
        {
            return;
        }

        _node->Child = tmp->Brother;

        if(tmp->Brother != null)
        {
            tmp->Brother->Parent = _node;
        }

        tmp->Parent = _node->Parent;

        if(_node == Root)
        {
            Root = tmp;
        }
        else if(_node == _node->Parent->Brother)
        {
            _node->Parent->Brother = tmp;
        }
        else
        {
            _node->Parent->Child = tmp;
        }

        tmp->Brother = _node, _node->Parent = tmp;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::RotateRight(const _Key& _key)
{
    RotateRight(const_cast<TreeNodeBase<_T, _Key>*>(Search(_key)));
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ForEach(__VisitFunc__ _func, ushort _for_each)
{
    switch(_for_each)
    {
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::General:
            TraversalGeneral(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::PreOrderRecur:
            TraversalPreOrderRecur(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::InOrderRecur:
            TraversalInOrderRecur(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::PostOrderRecur:
            TraversalPostOrderRecur(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::PreOrderIter:
            TraversalPreOrderIter(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::InOrderIter:
            TraversalInOrderIter(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::PostOrderIter:
            TraversalPostOrderIter(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ParentLinkIter:
            TraversalParentLinkInOrderIter(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::BreadthFirstIter:
            TraversalBreadthFirstIter(Root, _func);
            break;
        case BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::DepthFirstIter:
            TraversalDepthFirstIter(Root, _func);
            break;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalGeneral(const TreeNodeBase<_T, _Key>* _root, __VisitFunc__ _func)
{
    if(_root != null)
    {
        TreeNodeBase<_T, _Key>* node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(_root);

        while(node != null)
        {
           _func(node);
            node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(node);
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalPreOrderRecur(const TreeNodeBase<_T, _Key>* _node, __VisitFunc__ _func)
{
    if(_node != null)
    {
       _func(const_cast<TreeNodeBase<_T, _Key>*>(_node));
        TraversalPreOrderRecur(_node->Child, _func);
        TraversalPreOrderRecur(_node->Brother, _func);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalInOrderRecur(const TreeNodeBase<_T, _Key>* _node, __VisitFunc__ _func)
{
    if(_node != null)
    {
        TraversalInOrderRecur(_node->Child, _func);
       _func(const_cast<TreeNodeBase<_T, _Key>*>(_node));
        TraversalInOrderRecur(_node->Brother, _func);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalPostOrderRecur(const TreeNodeBase<_T, _Key>* _node, __VisitFunc__ _func)
{
    if(_node != null)
    {
        TraversalPostOrderRecur(_node->Child, _func);
        TraversalPostOrderRecur(_node->Brother, _func);
       _func(const_cast<TreeNodeBase<_T, _Key>*>(_node));
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalPreOrderIter(const TreeNodeBase<_T, _Key>* _root, __VisitFunc__ _func, uint _stack_size)
{
    if(_root != null)
    {
        //
        const short _delta_      = 16;
        const uint  _stack_size_ = _stack_size == 0 ? Count : _stack_size;
        //
        uint count = 0;

        Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(_stack_size_, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init|Array<TreeNodeBase<_T, _Key>*>::AutoResize);
        array.SetState(StateObject::NoDelete);

        TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_root);

        // push root
        array[count++] = node;

        while(count > 0)
        {
            // pop
            node = array[count-1];
            array[--count] = null;

           _func(node);

            // push left
            if(node->Child != null)
            {
                array[count++] = node->Child;
            }

            // push right
            if(node->Brother != null)
            {
                array[count++] = node->Brother;
            }
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalInOrderIter(const TreeNodeBase<_T, _Key>* _root, __VisitFunc__ _func, uint _stack_size)
{
    if(_root != null)
    {
        //
        const short _delta_      = 16;
        const uint  _stack_size_ = _stack_size == 0 ? Count : _stack_size;
        //
        uint count = 0;

        Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(_stack_size_, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init|Array<TreeNodeBase<_T, _Key>*>::AutoResize);
        array.SetState(StateObject::NoDelete);

        TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_root);

        // push root
        array[count++] = node;

        while(count > 0)
        {
            // push left
            if(node->Child != null)
            {
                array[count++] = node->Child;
            }

            // pop
            node = array[count-1];
            array[--count] = null;

            _func(node);

            // push right
            if(node->Brother != null)
            {
                array[count++] = node->Brother;
            }
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalPostOrderIter(const TreeNodeBase<_T, _Key>* _root, __VisitFunc__ _func, uint _stack_size)
{
    if(_root != null)
    {
        //
        const short _delta_      = 16;
        const uint  _stack_size_ = _stack_size == 0 ? Count : _stack_size;
        //
        uint count = 0;

        Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(_stack_size_, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init|Array<TreeNodeBase<_T, _Key>*>::AutoResize);
        array.SetState(StateObject::NoDelete);

        TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_root);

        // push root
        array[count++] = node;

        while(count > 0)
        {
            // push left
            if(node->Child != null)
            {
                array[count++] = node->Child;
            }

            // push right
            if(node->Brother != null)
            {
                array[count++] = node->Brother;
            }

            // pop
            node = array[count-1];
            array[--count] = null;

            _func(node);
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalParentLinkInOrderIter(const TreeNodeBase<_T, _Key>* _root, __VisitFunc__ _func)
{
    // NOTICE:
    //  this is inorder traversal (preorder & postorder are not implemented)
    //  in inorder traversal, a node is visited when its left son is recognized as NULL
    //  or when it is reached after backing up from its left son
    //  in preorder traversal, a node is visited only when it is reached
    //  on the way down the tree
    //  in postorder, a node is visited only when its right son is recognized as NULL
    //  or when it is reached after backing up from its right son
    //  postorder implementation produces invert sequence
    //  see "Data Structures Using C++" second edition by Y.Langsam, M.J.Augenstein, A.M.Tenenbaum
    if(_root != null)
    {
        TreeNodeBase<_T, _Key>* node = null;
        TreeNodeBase<_T, _Key>* tmp  = const_cast<TreeNodeBase<_T, _Key>*>(_root);

        do
        {
            node = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetLeftMostIter(tmp);

            if(node != null)
            {
               _func(node);
                tmp = node->Brother;
            }

            while(node != null && tmp == null)
            {
                do
                {
                    tmp  = node;
                    node = node->Parent;
                }
                while(node != null && tmp->Parent->Child != tmp);

                if(node != null)
                {
                   _func(node);
                    tmp = node->Brother;
                }
            }

        }
        while(node != null);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalBreadthFirstIter(const TreeNodeBase<_T, _Key>* _root, __VisitFunc__ _func, uint _queue_size)
{
    if(_root != null)
    {
		// enqueue the source vertex;
		//	repeat
		//		dequeue u;
		//		perform any relevant operations on u;
		//		enqueue all the neighbors of u;
		//	until the queue is empty
        const short _delta_      = 16;
        const uint  _queue_size_ = _queue_size == 0 ? Count : _queue_size;
        //
        uint n    = _queue_size_+1;
        uint head = n;
        uint tail = 0;

        Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(n, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init);
        array.SetState(StateObject::NoDelete);

        TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_root);

        // enqueue root
        array[tail++] = node, tail %= n;

        while(head % n != tail)
        {
            // dequeue
            head %= n, node = array[head++];
            array[head-1] = 0;

            _func(node);

            // enqueue left
            if(node->Child != null)
            {
                array[tail++] = node->Child, tail %= n;
            }

            // enqueue right
            if(node->Brother != null)
            {
                array[tail++] = node->Brother, tail %= n;
            }

            // NOTICE: if now sort queue it will be Best First algorithm
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::TraversalDepthFirstIter(const TreeNodeBase<_T, _Key>* _root, __VisitFunc__ _func, uint _stack_size)
{
    if(_root != null)
    {
        //
        const short _delta_      = 16;
        const uint  _stack_size_ = _stack_size == 0 ? Count : _stack_size;
        //
        uint count = 0;

        Array<TreeNodeBase<_T, _Key>*, Synchronization::NullThreadMutex<>, _Allocator> array(_stack_size_, _delta_, 0, Array<TreeNodeBase<_T, _Key>*, _Mutex, _Allocator>::Init|Array<TreeNodeBase<_T, _Key>*>::AutoResize);
        array.SetState(StateObject::NoDelete);

        TreeNodeBase<_T, _Key>* node = const_cast<TreeNodeBase<_T, _Key>*>(_root);

        // push root
        array[count++] = node;

        while(count > 0)
        {
            // pop
            node = array[count-1];
            array[--count] = null;

            _func(node);

            if((node->Child != null && node->Brother != null) && node->Brother->GetKey() < node->Child->GetKey()) // >= ! ...
            {
                array[count++] = node->Child;   // worse
                array[count++] = node->Brother; // better
            }
            else
            {
                if(node->Brother != null)
                {
                    array[count++] = node->Brother; // worse
                }

                if(node->Child != null)
                {
                    array[count++] = node->Child;   // better
                }
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class BinaryTreeIterator
// ----- ------------------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::BinaryTreeIterator(const TreeNodeBase<_T, _Key>* _node, const tchar* _mutex_name, uint _timeout) : CurrentNode(const_cast<TreeNodeBase<_T, _Key>*>(_node)), Mutex(_mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::BinaryTreeIterator(const BinaryTreeIterator& _other, const tchar* _mutex_name, uint _timeout) : Mutex(_mutex_name, _timeout)
{
    operator = (_other);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~BinaryTreeIterator()
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
const BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>& BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator = (const BinaryTreeIterator& _other)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    if(this != &_other)
    {
        CurrentNode = _other.CurrentNode;
    }

    return *this;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
void BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Restart(const TreeNodeBase<_T, _Key>* _node)
{
    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    CurrentNode = const_cast<TreeNodeBase<_T, _Key>*>(_node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
_T& BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Current()
{
    if(static_cast<int>(*this) == 0)
    {
        throw XTree(XTree::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    Node<_T>* node = dynamic_cast<Node<_T>*>(CurrentNode);

    if(node != null)
    {
        return const_cast<_T&>(node->GetData());
    }
    else
    {
        return *(reinterpret_cast<_T*>(dynamic_cast<void*>(CurrentNode)));
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
_T& BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator * ()
{
    return Current();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
const TreeNodeBase<_T, _Key>* BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetCurrentNode()
{
    return CurrentNode;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator int ()
{
    return CurrentNode != null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator ++ (int)
{
    if(CurrentNode == null)
    {
        throw XTree(XTree::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    TreeNodeBase<_T, _Key>* tmp = CurrentNode;
    CurrentNode = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(CurrentNode);
    return tmp;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator ++ ()
{
    if(CurrentNode == null)
    {
        throw XTree(XTree::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    return (CurrentNode = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetSuccessor(CurrentNode));
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator -- (int)
{
    if(CurrentNode == null)
    {
        throw XTree(XTree::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    TreeNodeBase<_T, _Key>* tmp = CurrentNode;
    CurrentNode = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPredecessor(CurrentNode);
    return tmp;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
TreeNodeBase<_T, _Key>* BinaryTreeIterator<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator -- ()
{
    if(CurrentNode == null)
    {
        throw XTree(XTree::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);
    //
    return (CurrentNode = BinaryTree<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetPredecessor(CurrentNode));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __BINARY_TREE_INL__

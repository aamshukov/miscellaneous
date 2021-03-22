////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ADT_INL__
#define __ADT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ADT
// ----- ---
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ADT(const _KeyExtractor& _kx, const _Comparator& _cmp, const tchar* _mutex_name, uint _timeout) : ExtractKey(_kx), CompareKey(_cmp), Mutex(_mutex_name, _timeout)
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~ADT()
{
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
const _Key& ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetKey(const NodeBase<_T, _Key>* _node)
{
    if(_node == null)
    {
        throw X(X::InvalidArg);
    }

    Node<_T>* node = dynamic_cast<Node<_T>*>(const_cast<NodeBase<_T, _Key>*>(_node));

    if(node != null)
    {
        return ExtractKey(const_cast<_T&>(node->GetData()));
    }
    else
    {
        // this is very dangerous ! ... (don't try at home)
        // dynamic_cast<void*>(_T) returns actual address of the object,
        // I can not use the following state,
        // because it's impossible use non polymorhic objects with dynamic_cast<>
        // for example List<int> or AVLTree<long> ! ...
        // return ExtractKey(*(dynamic_cast<_T*>(const_cast<NodeBase<_T, _Key>*>(_node))));

        return ExtractKey(*(reinterpret_cast<_T*>(dynamic_cast<void*>(const_cast<NodeBase<_T, _Key>*>(_node)))));
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
bool ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ShouldDelete() const
{
    return StateObject::ShouldDelete();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
StateObject::EState ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::SetState(StateObject::EState _state)
{
    return StateObject::SetState(_state);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ADT_INL__

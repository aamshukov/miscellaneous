////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HASH_TABLE_INL__
#define __HASH_TABLE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
static const ulong __Primes__[] = // from stl
{
    53UL,         97UL,         193UL,       389UL,       769UL,
    1543UL,       3079UL,       6151UL,      12289UL,     24593UL,
    49157UL,      98317UL,      196613UL,    393241UL,    786433UL,
    1572869UL,    3145739UL,    6291469UL,   12582917UL,  25165843UL,
    50331653UL,   100663319UL,  201326611UL, 402653189UL, 805306457UL, 
    1610612741UL, 3221225473UL, 4294967291UL
};
////////////////////////////////////////////////////////////////////////////////////////
// class HashTable
// ----- ---------
template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::HashTable(const _KeyExtractor& _kx, const _Comparator& _cmp, ulong _size, bool _create, const tchar* _mutex_name, uint _timeout) : ADT<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>(_kx, _cmp, _mutex_name, _timeout), Count(0), Buckets(0)
{
    if(_create)
    {
        Create(_size);
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::~HashTable()
{
    Destroy();
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ HashTableNodeBase<_T, _Key>* HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::ConstructNode(const _T& _data)
{
    void* p = _Allocator::Allocate(sizeof(HashTableNode<_T, _Key>));
    HashTableNode<_T, _Key>* node = new (p) HashTableNode<_T, _Key>(_data);
    node->ModifyFlags(NodeBase<_T, _Key>::StandardAlloc, 0);
    return node;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::DestroyNode(HashTableNodeBase<_T, _Key>* _node)
{
    if(_node != null)
    {
        if(_node->GetFlags() & HashTableNodeBase<_T, _Key>::StandardAlloc)
        {
            if(ShouldDelete())
            {
                delete _node;
            }
        }
        else
        {
            _node->~HashTableNodeBase<_T, _Key>(); // virtual dtor OK
            _Allocator::Deallocate(static_cast<HashTableNode<_T, _Key>*>(_node)); // casting
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Create(ulong _size)
{
    if(Buckets.IsEmpty())
    {
        Synchronization::Guard<_Mutex> guard(Mutex);

        Buckets.Resize(AdjustSize(_size));
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Destroy()
{
    Synchronization::Guard<_Mutex> guard(Mutex);

    for(ulong i = 0; i < Buckets.GetCount(); ++i)
    {
        HashTableNodeBase<_T, _Key>* tmp = Buckets[i];

        while(tmp != null)
        {
            Remove(GetKey(tmp), true);
            tmp = Buckets[i];
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ ulong HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::AdjustSize(ulong _size)
{
    _size = _size == 0 ? 769 : _size;

    int n = sizeof(__Primes__)/sizeof(__Primes__[0]);

    for(int i = 0; i < n; ++i)
    {
        if(_size <= __Primes__[i])
        {
            return __Primes__[i];
        }
    }

    return __Primes__[0];
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ ulong HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::GetCount() const
{
    return Count;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const _T& HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::operator [] (const _Key& _key) const
{
    HashTableNodeBase<_T, _Key>* node = const_cast<HashTableNodeBase<_T, _Key>*>(Search(_key));

    if(node == null)
    {
        throw X(X::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    Node<_T>* tmp = dynamic_cast<Node<_T>*>(node);

    if(tmp != null)
    {
        return const_cast<_T&>(tmp->GetData());
    }
    else
    {
        return *(reinterpret_cast<_T*>(dynamic_cast<void*>(node)));
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ bool HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::HasEntry(const _Key& _key) const
{
    return Search(_key) != null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ const HashTableNodeBase<_T, _Key>* HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Search(const _Key& _key) const
{
    if(Buckets.IsEmpty())
    {
        throw X(X::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    for(HashTableNodeBase<_T, _Key>* i = Buckets[HashFunc(_key) % Buckets.GetCount()]; i; i = i->Next)
    {
        if(CompareKey(GetKey(i), _key) == 0)
        {
            return i;
        }
    }

    return null;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(HashTableNodeBase<_T, _Key>* _entry)
{
    if(_entry == null)
    {
        throw X(X::InvalidArg);
    }

    if(Buckets.IsEmpty())
    {
        throw X(X::OutOfRange);
    }

    Synchronization::Guard<_Mutex> guard(Mutex);

    uint i = HashFunc(GetKey(_entry)) % Buckets.GetCount();
    
   _entry->Next = Buckets[i];
    Buckets[i]  = _entry;

    ++Count;
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Insert(const _T& _data)
{
    HashTableNodeBase<_T, _Key>* node = ConstructNode(_data);
    Insert(node);
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Remove(const _Key& _key, bool _destroy)
{
    Synchronization::Guard<_Mutex> guard(Mutex);

    ulong i = HashFunc(_key) % Buckets.GetCount();

    HashTableNodeBase<_T, _Key>* curr = Buckets[i];
    HashTableNodeBase<_T, _Key>* prev = curr;

    for(; curr; curr = curr->Next)
    {
        if(CompareKey(GetKey(curr), _key) == 0)
        {
            if(curr == Buckets[i])
            {
                Buckets[i] = curr->Next;
            }
            else
            {
                prev->Next = curr->Next;
            }

            break;
        }

        prev = curr;
    }

    if(curr != null)
    {
        if(_destroy)
        {
            DestroyNode(curr);
        }

        --Count;
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
__INLINE_TEMPLATE__ void HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::Rehash()
{
    Synchronization::Guard<_Mutex> guard(Mutex);

    ulong old_n = Buckets.GetCount();
    ulong new_n = AdjustSize(Buckets.GetCount()+1);

    Array<HashTableNodeBase<_T, _Key>*, Synchronization::NullThreadMutex, _Allocator> buckets(new_n);

    new_n = buckets.GetCount(); // array rounded up

    try
    {
        for(ulong i = 0; i < old_n; ++i)
        {
            HashTableNodeBase<_T, _Key>* tmp = Buckets[i];

            while(tmp != null)
            {
                ulong new_i = HashFunc(GetKey(tmp)) % new_n;
                Buckets[i] = tmp->Next, tmp->Next = buckets[new_i], buckets[new_i] = tmp, tmp = Buckets[i];
            }
        }

        // swap
        Buckets.Swap(buckets);
    }
    catch(...)
    {
        for(ulong i = 0; i < new_n; ++i)
        {
            HashTableNodeBase<_T, _Key>* tmp = buckets[i];

            while(tmp != null)
            {
                ulong new_i = HashFunc(GetKey(tmp)) % old_n;
                buckets[i] = tmp->Next, tmp->Next = Buckets[new_i], Buckets[new_i] = tmp, tmp = buckets[i];
            }
        }
    }
}

template <typename _T, typename _Key, typename _KeyExtractor, typename _Comparator, typename _Mutex, typename _Allocator>
ulong HashTable<_T, _Key, _KeyExtractor, _Comparator, _Mutex, _Allocator>::HashFunc(const tchar* _text)
{
    if(_text)
    {
        uint g;
        uint hash_value = 0;

        while(*_text)
        {
            hash_value = (hash_value << 4)+(*_text++);

            if(g = hash_value & 0xF0000000)
            {
                hash_value ^= g >> 24;
            }

            hash_value &= ~g;
        }
        return hash_value;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HASH_TABLE_INL__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SORTMANAGER_INL__
#define __SORTMANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SortManager
// ----- -----------
template <typename T> SortManager<T>::SortManager(T* _items, uint _count)
{
    Items     = _items;
    ItemCount = _count;

    Setup();
}

template <typename T> __INLINE_TEMPLATE__ uint SortManager<T>::GetItemCount() const
{
    return ItemCount;
}

template <typename T> void SortManager<T>::Setup()
{
    Left  = 0;
    Right = ItemCount-1;
}

template <typename T> void SortManager<T>::Sort()
{
    register uint i;
    register uint j;

    Lock lock(this);

    T x, y, tmp;

    i = Left;
    j = Right;
    x = Items[(Left+Right)/2];

    do
    {
        while(Items[i] < x && i < Right)
        {
            ++i;
        }

        while(x < Items[j] && j > Left)
        {
            --j;
        }

        if(i <= j)
        {
            y        = Items[i];
            Items[i] = Items[j];
            Items[j] = y;

            ++i;
            --j;
        }
    }
    while(i <= j);

    if(Left < j)
    {
        tmp   = Right;
        Right = j;

        Sort();

        Right = tmp;
    }

    if(i < Right)
    {
        tmp  = Left;
        Left = i;

        Sort();

        Left = tmp;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SORTMANAGER_INL__

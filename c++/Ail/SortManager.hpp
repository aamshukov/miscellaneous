////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SORTMANAGER_H__
#define __SORTMANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SortManager
// ----- -----------
template <typename T> class SortManager : private SyncObject
{
    protected:
     uint          ItemCount;
     uint          Left;
     uint          Right;

     T*            Items;
    protected:
     virtual void  Setup();
    public:
                   SortManager(T*, uint);

     uint          GetItemCount() const;

     void          Sort();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SORTMANAGER_H__

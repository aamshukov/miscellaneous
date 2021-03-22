////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1989-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __HASH_TABLE_INC__
#   include <HashTable.inc>
#endif

#ifndef __COLLECTION_H__
#   include <Collection.hpp>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// Collection
// ----------
Collection::HashTableItem::HashTableItem(const tchar* _key, const tchar* _val)
{
    Key = strcpy(new tchar[strlen(_key)+1], _key);
    Val = strcpy(new tchar[strlen(_val)+1], _key);
}

Collection::HashTableItem::~HashTableItem()
{
    delete [] Key, Key = null;
    delete [] Val, Val = null;
}

Collection::Collection() : HashTable(ColKeyExtractor, ColComparator)
{
}

Collection::~Collection()
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

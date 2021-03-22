////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1989-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// Collection
// ----------
class __DECLSPEC__ Collection
{
    private:
        class HashTableItem : private HashTableNodeBase<HashTableItem, tchar*>
        {
            public:
                tchar* Key;
                tchar* Val;
            public:
                HashTableItem(const tchar*, const tchar*);
               ~HashTableItem();
        };

        struct _ColKeyExtractor
        {
            tchar*& operator() (HashTableItem& _item)
            {
                return _item.Key;
            }
        };

        struct _ColComparator
        {
            int8 operator() (const tchar* _k1, const tchar* _k2)
            {
                return strcmp(_k1, _k2);
            }
        };

        typedef HashTable<HashTableItem, tchar*, _ColKeyExtractor, _ColComparator> _HashTable;

       _ColKeyExtractor ColKeyExtractor;
       _ColComparator   ColComparator;
       _HashTable       HashTable;
    public:
        // ctor/dtor
                        Collection();
        virtual        ~Collection();

        // api
        bool            IsEmpty()                   const;
        uint32          GetCount()                  const;

        tchar*          GetValue(const tchar*);

        void            Add(const tchar*, const tchar*);
        void            Remove(const tchar*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COLLECTION_H__

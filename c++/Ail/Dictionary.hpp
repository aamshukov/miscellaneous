////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DICTIONARY_H__
#define __DICTIONARY_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Dictionary
// ----- ----------
class __DECLSPEC__ Dictionary
{
    public:

    typedef Array<AutoPtrArray<tchar> > _Array;

    enum EConst
    {
        DefCount = 32,
        DefLimit = 16384
    };

    private:
     uint           Index;
     uint           Limit;
    _Array          Dict;
     StringTable<>  Table;
    public:
     // ctor/dtor
                    Dictionary(const tchar*, uint = Dictionary::DefCount, uint = Dictionary::DefLimit);
                   ~Dictionary();

     // access
     uint           GetLimit()  const;
     const _Array&  GetDict()   const;

     // protocol
     void           Insert(const tchar*);

    class __DECLSPEC__ XDictionary : public X
    {
        public:
            XDictionary(uint = X::InvalidArg);
    };
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __DICTIONARY_H__

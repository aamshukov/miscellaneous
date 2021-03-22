////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DICTIONARY_INL__
#define __DICTIONARY_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Dictionary
// ----- ----------
__INLINE__ uint Dictionary::GetLimit() const
{
    return Limit;
}

__INLINE__ const Array<AutoPtrArray<tchar> >& Dictionary::GetDict() const
{
    return Dict;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __DICTIONARY_INL__

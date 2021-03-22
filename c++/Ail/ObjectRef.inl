////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __OBJECTREF_INL__
#define __OBJECTREF_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ObjectRef
// ----- ---------
template <typename _T>
ObjectRef<_T>::ObjectRef()
             : Id(0), Reference(0)
{
}

template <typename _T>
ObjectRef<_T>::ObjectRef(_T _id)
             : Id(_id), Reference(0)
{
}

template <typename _T>
ObjectRef<_T>::~ObjectRef()
{
}

template <typename _T>
__INLINE_TEMPLATE__ _T ObjectRef<_T>::GetId() const
{
    return Id;
}

template <typename _T>
__INLINE_TEMPLATE__ void ObjectRef<_T>::SetId(_T _id)
{
    Id = _id;
}

template <typename _T>
_T ObjectRef<_T>::AddReference()
{
    return ++Reference;
}

template <typename _T>
_T ObjectRef<_T>::ReleaseReference()
{
    return --Reference;
}

template <typename _T>
__INLINE_TEMPLATE__ _T ObjectRef<_T>::GetReference() const
{
    return Reference;
}

template <typename _T>
__INLINE_TEMPLATE__ void ObjectRef<_T>::AdjustReference(_T _ref)
{
    Reference = _ref;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __OBJECTREF_INL__

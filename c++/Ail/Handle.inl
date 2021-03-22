////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HANDLE_INL__
#define __HANDLE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Handle
// ----- ------
template <typename _Handle> Handle<_Handle>::Handle(_Handle _handle) : HValue(_handle)
{
}

template <typename _Handle> Handle<_Handle>::Handle(const Handle<_Handle>& _other)
{
    operator = (_other);
}

template <typename _Handle> Handle<_Handle>::~Handle()
{
    // do not alter the value !
}

template <typename _Handle> __INLINE_TEMPLATE__ const Handle<_Handle>& Handle<_Handle>::operator = (const Handle<_Handle>& _other)
{
    if(this != &_other)
    {
        HValue = _other.HValue;
    }

    return *this;
}

template <typename _Handle> __INLINE_TEMPLATE__ Handle<_Handle>::operator _Handle ()
{
    return HValue;
}

template <typename _Handle> __INLINE_TEMPLATE__ bool Handle<_Handle>::operator == (_Handle _handle) const
{
    return HValue == _handle;
}

template <typename _Handle> __INLINE_TEMPLATE__ bool Handle<_Handle>::operator != (_Handle _handle) const
{
    return HValue != _handle;
}

template <typename _Handle> __INLINE_TEMPLATE__ Handle<_Handle>::operator const _Handle () const
{
    return reinterpret_cast<const _Handle>(HValue);
}

template <typename _Handle> __INLINE_TEMPLATE__ _Handle Handle<_Handle>::GetHandle()
{
    return HValue;
}

template <typename _Handle> __INLINE_TEMPLATE__ const _Handle Handle<_Handle>::GetHandle() const
{
    return reinterpret_cast<const _Handle>(HValue);
}

template <typename _Handle> __INLINE_TEMPLATE__ void Handle<_Handle>::SetHandle(_Handle _handle)
{
    HValue = _handle;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HANDLE_INL__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BUFFER_INL__
#define __BUFFER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Buffer
// ----- ------
template <typename _T> Buffer<_T>::Buffer()
{
}

template <typename _T> Buffer<_T>::Buffer(const Buffer& _other, uint _i, uint _n)
{
    Assign(_other, _i, _n);
}

template <typename _T> Buffer<_T>::Buffer(const _T* _stream, uint _n)
{
    Assign(_stream, _n);
}

template <typename _T> Buffer<_T>::Buffer(uint _n, _T _c)
{
    if(_c == 0)
    {
        Reserve(_n);
    }
    else
    {
        Assign(_c, _n);
    }
}

template <typename _T> Buffer<_T>::~Buffer()
{
}

template <typename _T> __INLINE_TEMPLATE__ const std::basic_string<_T>& Buffer<_T>::GetString() const
{
    return static_cast<const std::basic_string<_T>&>(String_);
}

template <typename _T> Buffer<_T>& Buffer<_T>::operator = (const Buffer<_T>& _other)
{
    return Assign(_other);
}

template <typename _T> Buffer<_T>& Buffer<_T>::operator = (const _T* _stream)
{
    return Assign(_stream);
}

template <typename _T> Buffer<_T>& Buffer<_T>::operator = (_T _c)
{
    return Assign(_c);
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::operator += (const Buffer<_T>& _buffer)
{
    return Append(_buffer);
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::operator += (const _T* _stream)
{
    return Append(_stream);
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::operator += (_T _c)
{
    return Append(_c);
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::operator -= (uint _n)
{
    try
    {
        String_.resize(_n > String_.size() ? 0 : _n);
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ bool Buffer<_T>::operator == (const Buffer& _buffer)
{
    return String_.compare(_buffer.String_) == 0;
}

template <typename _T> __INLINE_TEMPLATE__ bool Buffer<_T>::operator != (const Buffer& _buffer)
{
    return String_.compare(_buffer.String_) != 0;
}

template <typename _T> __INLINE_TEMPLATE__ const _T& Buffer<_T>::operator [] (uint _i) const
{
    try
    {
        return String_[_i];
    }
    catch(...)
    {
        throw XBuffer(X::OutOfRange);
    }
}

template <typename _T> __INLINE_TEMPLATE__ bool Buffer<_T>::IsEmpty() const
{
    return String_.empty();
}

template <typename _T> __INLINE_TEMPLATE__ void Buffer<_T>::SetEmpty()
{
    String_.erase(0, String_.size());
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Assign(const Buffer& _buffer, uint _i, uint _n)
{
    try
    {
        String_.assign(_buffer.String_, _i, _n == -1 ? _buffer.String_.size() : _n);
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Assign(const _T* _stream, uint _n)
{
    try
    {
        if(_n == -1)
        {
            String_.assign(_stream);
        }
        else
        {
            String_.assign(_stream, _n);
        }
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Assign(_T _c, uint _n)
{
    try
    {
        String_.assign(_n, _c);
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Append(const Buffer& _buffer, uint _i, uint _n)
{
    try
    {
        String_.append(_buffer.String_, _i, _n == -1 ? _buffer.String_.size() : _n);
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Append(const _T* _stream, uint _n)
{
    try
    {
        if(_n == -1)
        {
            String_.append(_stream);
        }
        else
        {
            String_.append(_stream, _n);
        }
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Append(_T _c, uint _n)
{
    try
    {
        String_.append(_n, _c);
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Insert(uint _i_dst, const Buffer& _buffer, uint _i_src, uint _n_src)
{
    try
    {
        String_.insert(_i_dst, _buffer.String_, _i_src, _n_src == -1 ? _buffer.String_.size() : _n_src);
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Insert(uint _i_dst, const _T* _stream, uint _n_src)
{
    try
    {
        if(_n_src == -1)
        {
            String_.insert(_i_dst, _stream);
        }
        else
        {
            String_.insert(_i_dst, _stream, _n_src);
        }
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ Buffer<_T>& Buffer<_T>::Insert(uint _i_dst, _T _c, uint _n_src)
{
    try
    {
        String_.insert(_i_dst, _n_src, _c);
        return *this;
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ uint Buffer<_T>::GetSize() const
{
    return String_.size();
}

template <typename _T> __INLINE_TEMPLATE__ uint Buffer<_T>::GetCapacity() const
{
    return String_.capacity();
}

template <typename _T> __INLINE_TEMPLATE__ void Buffer<_T>::Resize(uint _n)
{
    try
    {
        String_.resize(_n);
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ void Buffer<_T>::Reserve(uint _n)
{
    try
    {
        String_.reserve(_n);
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}

template <typename _T> __INLINE_TEMPLATE__ void Buffer<_T>::Reset()
{
    std::fill_n(String_.begin(), String_.size(), 0);
}

template <typename _T> __INLINE_TEMPLATE__ void Buffer<_T>::Remove(uint _i, uint _n)
{
    try
    {
        String_.erase(_i, _n);
    }
    catch(...)
    {
        throw XBuffer(X::OutOfRange);
    }
}

template <typename _T> __INLINE_TEMPLATE__ void Buffer<_T>::Swap(Buffer& _buffer)
{
    try
    {
        String_.swap(_buffer.String_);
    }
    catch(...)
    {
        throw XBuffer(X::OutOfMemory);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __BUFFER_INL__

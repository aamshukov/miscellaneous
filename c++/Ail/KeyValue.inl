////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __KEY_VALUE_INL__
#define __KEY_VALUE_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class KeyValue
// ----- --------
template <typename _Key, typename _Value>
KeyValue<_Key, _Value>::KeyValue()
{
}

template <typename _Key, typename _Value>
KeyValue<_Key, _Value>::KeyValue(const KeyValue& _other)
{
    if(this != &_other) 
    {
        First = _other.First, Second = _other.Second; 
    }
}

template <typename _Key, typename _Value>
KeyValue<_Key, _Value>::KeyValue(_Key& _key, _Value& _value) : Pair(_key, _value)
{
    First  = _key;
    Second = _value; 
}


template <typename _Key, typename _Value>
KeyValue<_Key, _Value>& KeyValue<_Key, _Value>::operator = (const KeyValue& _other)
{
    if(this != &_other) 
    {
        First = _other.First, Second = _other.Second; 
    }
    return *this;
}

template <typename _Key, typename _Value>
__INLINE_TEMPLATE__ bool KeyValue<_Key, _Value>::operator == (const KeyValue& _other)
{
    return First == _other.First && Second = _other.Second;
}

template <typename _Key, typename _Value>
__INLINE_TEMPLATE__ const _Key& KeyValue<_Key, _Value>::GetKey() const
{
    return First;
}

template <typename _Key, typename _Value>
__INLINE_TEMPLATE__ const _Value& KeyValue<_Key, _Value>::GetValue() const
{
    return Second;
}

template <typename _Key, typename _Value>
__INLINE_TEMPLATE__ void KeyValue<_Key, _Value>::SetValue(const _Value& _value)
{
    Second = _value;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __KEY_VALUE_INL__

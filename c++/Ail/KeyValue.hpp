////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __KEY_VALUE_H__
#define __KEY_VALUE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class KeyValue
// ----- --------
template <typename _Key = pctchar, typename _Value = tchar*> class KeyValue : public Pair<_Key, _Value>
{
    typedef KeyValue<_Key, _Value> _KV;

    public:
     // ctor/dtor
                    KeyValue();
                    KeyValue(const KeyValue&);
                    KeyValue(_Key&, _Value&);

     // operators
    _KV&            operator = (const _KV&);
     bool           operator == (const _KV&);

     // access
     const _Key&    GetKey()                const;

     const _Value&  GetValue()              const;
     void           SetValue(const _Value&);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __KEY_VALUE_H__

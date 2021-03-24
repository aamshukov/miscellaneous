////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RANGE_H__
#define __RANGE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Range
// ----- -----
template <typename V = uint> class Range
{
    public:
     V              MinValue;
     V              MaxValue;
    public:
     // ctor/dtor
                    Range();
                    Range(const Range&);
                    Range(V, V);

     // operators
     const Range<V> operator = (const Range<V>&);
     bool           operator == (const Range<V>&);

     // access
     V              GetMinValue()           const;
     void           SetMinValue(V val);

     V              GetMaxValue()           const;
     void           SetMaxValue(V val);

     // protocol
     bool           IsInRange(V)            const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RANGE_H__

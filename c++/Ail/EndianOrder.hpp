////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ENDIAN_ORDER_H__
#define __ENDIAN_ORDER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class EndianOrder
// ----- -----------
class __DECLSPEC__ EndianOrder
{
    private:
     bool       LittleEndian;
     bool       ReverseOrder;
    public:
     // ctor/dtor
                EndianOrder();
               ~EndianOrder();

     // access
     bool       IsLittleEndian()    const;
     bool       IsReverseOrder()    const;

     // protocol
     void       Arrange(byte*, uint);
     void       Arrange(byte*, const byte*, uint);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ENDIAN_ORDER_H__

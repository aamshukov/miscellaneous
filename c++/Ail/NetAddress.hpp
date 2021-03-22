////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NET_ADDRESS_H__
#define __NET_ADDRESS_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class NetAddress
// ----- ----------
class __DECLSPEC__ NetAddress
{
    protected:
     virtual ulong  Hash()  const = 0;
    public:
     // ctor/dtor
                    NetAddress();
     virtual       ~NetAddress();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __NET_ADDRESS_H__

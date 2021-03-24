////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __INET_UTIL_H__
#define __INET_UTIL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class InetUtil
// ----- --------
class __DECLSPEC__ InetUtil
{
    public:

    enum ETimeProtocol
    {
        Daytime = 13,
        Time    = 37
    };

    public:
     static const tchar**   GetNTPServers();
     static bool            GetNetworkTime(tchar*, uint, const tchar* = null, const tchar* = null, const tchar* = null, const tchar* = null, const tchar* = null, short = 5, InetUtil::ETimeProtocol = InetUtil::Daytime, uint = 20);
     static uint            GetNetworkTime(const tchar* = null, const tchar* = null, const tchar* = null, const tchar* = null, const tchar* = null, short = 5, uint = 20);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __INET_UTIL_H__

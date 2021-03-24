////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SOCKET_MANAGER_INL__
#define __SOCKET_MANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SocketManager
// ----- -------------
__INLINE__ ushort SocketManager::GetStartupCount() const
{
    return StartupCount;
}

__INLINE__ WSAData& SocketManager::GetInformation() const
{
    return const_cast<WSAData&>(Info);
}

__INLINE__ ushort SocketManager::GetMajorVersion() const
{
    return HIBYTE(Info.wVersion);
}

__INLINE__ ushort SocketManager::GetMinorVersion() const
{
    return LOBYTE(Info.wVersion);
}

__INLINE__ const tchar* SocketManager::GetDescription() const
{
    return static_cast<const tchar*>(Info.szDescription);
}

__INLINE__ const tchar* SocketManager::GetSystemStatus() const
{
    return static_cast<const tchar*>(Info.szSystemStatus);
}

__INLINE__ const tchar* SocketManager::GetVendorInfo() const
{
    return static_cast<const tchar*>(Info.lpVendorInfo);
}

__INLINE__ ushort SocketManager::GetMaxUDPDAvailable() const
{
    return Info.iMaxUdpDg;
}

__INLINE__ ushort SocketManager::GetMaxSocketsAvailable() const
{
    return Info.iMaxSockets;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SOCKET_MANAGER_INL__

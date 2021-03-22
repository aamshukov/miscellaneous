////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SOCKET_MANAGER_H__
#define __SOCKET_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SocketManager
// ----- -------------
class __DECLSPEC__ SocketManager
{
    private:
     ushort         StartupCount;
     WSAData        Info;
    public:
     // ctor/dtor
                    SocketManager(bool = true, bool = true);
     virtual       ~SocketManager();

     // access
     ushort         GetStartupCount()           const;
     WSAData&       GetInformation()            const;

     // protocol
     ushort         GetMajorVersion()           const;
     ushort         GetMinorVersion()           const;

     const tchar*   GetDescription()            const;
     const tchar*   GetSystemStatus()           const;
     const tchar*   GetVendorInfo()             const;

     ushort         GetMaxUDPDAvailable()       const;
     ushort         GetMaxSocketsAvailable()    const;

     int            Startup(ushort = 0x0202);
     int            Shutdown();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SOCKET_MANAGER_H__

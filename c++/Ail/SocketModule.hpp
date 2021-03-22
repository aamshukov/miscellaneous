////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SOCKET_MODULE_H__
#define __SOCKET_MODULE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SocketModule
// ----- ------------
class __DECLSPEC__ SocketModule : public Module
{
    public:
     // ctor/dtor
                        SocketModule();

     // access
     static Module&     GetSocketModule();

     //protocol
     static int         Startup(ushort, WSADATA*);
     static int         Cleanup();
     //
     static int         GetLastError();
     static void        SetLastError(int);
     static bool        GetOverlappedResult(SOCKET, WSAOVERLAPPED*, uint*, bool, uint*);
     //
     static SOCKET      CreateSocket(int, int, int);
     static SOCKET      CreateSocket(int, int, int, WSAPROTOCOL_INFO*, GROUP, uint);
     static int         CloseSocket(SOCKET);
     static int         DuplicateSocket(SOCKET, uint, WSAPROTOCOL_INFO*);
     //
     static hostent*    GetHostByAddress(const char*, int, int);
     static HANDLE      GetHostByAddress(HWND, uint, const char*, int, int, char*, int);

     static hostent*    GetHostByName(const char*);
     static HANDLE      GetHostByName(HWND, uint, const char*, char*, int);

     static int         GetHostName(char*, int);
     static int         GetPeerName(SOCKET, sockaddr*, int*);

     static protoent*   GetProtocolByName(const char*);
     static HANDLE      GetProtocolByName(HWND, uint, const char*, char*, int);

     struct protoent*   GetProtocolByNumber(int);
     static HANDLE      GetProtocolByNumber(HWND, uint, int, char*, int);

     static servent*    GetServiceByName(const char*, const char*);
     static HANDLE      GetServiceByName(HWND, uint, const char*, const char*, char*, int);

     static servent*    GetServerByPort(int, const char*);
     static HANDLE      GetServerByPort(HWND, uint, int, const char*, char*, int);

     static int         GetSocketName(SOCKET, sockaddr*, int*);

     static int         GetSocketOption(SOCKET, int, int, char*, int*);
     static int         SetSocketOption(SOCKET, int, int, const char*, int);
           
     static ushort      HtoNS(ushort);
     static int         HtoNS(SOCKET, ushort, ushort*);
     static ulong       HtoNL(ulong);
     static int         HtoNL(SOCKET, ulong, ulong*);
     static ushort      NtoHS(ushort);
     static int         NtoHS(SOCKET, ushort, ushort*);
     static ulong       NtoHL(ulong);
     static int         NtoHL(SOCKET, ulong, ulong*);

     static ulong       InetAddress(const char*);
     static char*       InetNtoA(in_addr);

     static int         AddressToString(sockaddr*, ulong, WSAPROTOCOL_INFO*, tchar*, ulong*);
     static int         StringToAddress(tchar*, int, WSAPROTOCOL_INFO*, sockaddr*, int*);

     static int         IoctlSocket(SOCKET, long, ulong*);
     static int         IoctlSocket(SOCKET, uint, void*, uint, void*, uint, uint*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
     //
     static SOCKET      Accept(SOCKET, sockaddr*, int*);
     static SOCKET      Accept(SOCKET, sockaddr*, int*, LPCONDITIONPROC, uint);
 
     static int         Bind(SOCKET, const sockaddr*, int);
     static int         Listen(SOCKET, int);
 
     static int         Connect(SOCKET, const sockaddr*, int);
     static int         Connect(SOCKET, const sockaddr*, int, WSABUF*, WSABUF*, QOS*, QOS*);

     static int         Receive(SOCKET, char*, int, int);
     static int         Receive(SOCKET, WSABUF*, uint, uint*, uint*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
     static int         ReceiveDisconnect(SOCKET, WSABUF*);
     static int         ReceiveFrom(SOCKET, char*, int, int, sockaddr*, int*);
     static int         ReceiveFrom(SOCKET, WSABUF*, uint, uint*, uint*, sockaddr*, int*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE);

     static int         Send(SOCKET, const char*, int, int);
     static int         Send(SOCKET, WSABUF*, uint, uint*, uint, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
     static int         SendDisconnect(SOCKET, WSABUF*);
     static int         SendTo(SOCKET, const char*, int, int, const sockaddr*, int);
     static int         SendTo(SOCKET, WSABUF*, uint, uint*, uint, const sockaddr*, int, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
 
     static int         Select(int, fd_set*, fd_set*, fd_set*, const timeval*);
     static int         Select(SOCKET, HWND, uint, long);

     static bool        GetQOSByName(SOCKET, WSABUF*, QOS*);
     static SOCKET      JoinLeaf(SOCKET, const sockaddr*, int, WSABUF*, WSABUF*, QOS*, QOS*, uint);

     static int         Shutdown(SOCKET, int);
     static int         CancelAsyncRequest(HANDLE);
     //
     static int         GetServiceClassInfo(GUID*, GUID*, ulong*, WSASERVICECLASSINFO*);
     static int         GetServiceClassNameByClassId(GUID*, tchar*, ulong*);

     static int         InstallServiceClass(WSASERVICECLASSINFO*);
     static int         SetService(WSAQUERYSET*, WSAESETSERVICEOP, ulong);
     static int         RemoveServiceClass(GUID*);

     static int         LookupServiceBegin(WSAQUERYSET*, ulong, HANDLE*);
     static int         LookupServiceNext(HANDLE, ulong, ulong*, WSAQUERYSET*);
     static int         LookupServiceEnd(HANDLE);
     //
     static int         EnumNameSpaceProviders(ulong*, WSANAMESPACE_INFO*);
     static int         ProviderConfigChange(HANDLE*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE);
     //
     static int         EnumProtocols(int*, WSAPROTOCOL_INFO*, ulong*);
     //
     static WSAEVENT    CreateEvent();
     static bool        CloseEvent(WSAEVENT);
     static int         EventSelect(SOCKET, WSAEVENT, long);
     static bool        SetEvent(WSAEVENT);
     static bool        ResetEvent(WSAEVENT);
     static int         EnumNetworkEvents(SOCKET, WSAEVENT, WSANETWORKEVENTS*);
     static uint        WaitForMultipleEvents(uint, const WSAEVENT*, bool, uint, bool);
     static int         FDIsSet(SOCKET, fd_set*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SOCKET_MODULE_H__

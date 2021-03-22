////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __SOCKET_MODULE_INC__
#   include <SocketModule.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class SocketModule
// ----- ------------
SocketModule::SocketModule() : Module(_t("WS2_32.DLL"))
{
}

Module& SocketModule::GetSocketModule()
{
    static SocketModule _the_module_;
    return _the_module_;
}

int SocketModule::Startup(ushort _version_requested, WSADATA* _data)
{
    const char _name_[] = "WSAStartup";
    //
    static ModuleProc2<int, ushort, WSADATA*> Startup(GetSocketModule(), _name_);
    return Startup(_version_requested, _data);
}

int SocketModule::Cleanup()
{
    const char _name_[] = "WSACleanup";
    //
    static ModuleProc0<int> Cleanup(GetSocketModule(), _name_);
    return Cleanup();
}

int SocketModule::GetLastError()
{
    const char _name_[] = "WSAGetLastError";
    //
    static ModuleProc0<int> GetLastError(GetSocketModule(), _name_);
    return GetLastError();
}

void SocketModule::SetLastError(int _error)
{
    const char _name_[] = "WSASetLastError";
    //
    static ModuleProcV1<int> SetLastError(GetSocketModule(), _name_);
    SetLastError(_error);
}

bool SocketModule::GetOverlappedResult(SOCKET _s, WSAOVERLAPPED* _o, uint* _count, bool _wait, uint* _flags)
{
    const char _name_[] = "WSAGetOverlappedResult";
    //
    static ModuleProc5<BOOL, SOCKET, WSAOVERLAPPED*, uint*, bool, uint*> GetOverlappedResult(GetSocketModule(), _name_);
    return GetOverlappedResult(_s, _o, _count, _wait, _flags) == 1;
}

SOCKET SocketModule::CreateSocket(int _af, int _type, int _protocol)
{
    const char _name_[] = "socket";
    //
    static ModuleProc3<SOCKET, int, int, int> CreateSocket(GetSocketModule(), _name_);
    return CreateSocket(_af, _type, _protocol);
}

SOCKET SocketModule::CreateSocket(int _af, int _type, int _protocol, WSAPROTOCOL_INFO* _protocol_info, GROUP _g, uint _flags)
{
#ifdef _UNICODE
    const char _name_[] = "WSASocketW";
    //
    static ModuleProc6<SOCKET, int, int, int, LPWSAPROTOCOL_INFOA, GROUP, uint> CreateSocket(GetSocketModule(), _name_);
#else
    const char _name_[] = "WSASocketA";
    //
    static ModuleProc6<SOCKET, int, int, int, LPWSAPROTOCOL_INFOA, GROUP, uint> CreateSocket(GetSocketModule(), _name_);
#endif
    return CreateSocket(_af, _type, _protocol, _protocol_info, _g, _flags);
}

int SocketModule::CloseSocket(SOCKET _s)
{
    const char _name_[] = "closesocket";
    //
    static ModuleProc1<int, SOCKET> CloseSocket(GetSocketModule(), _name_);
    return CloseSocket(_s);
}

int SocketModule::DuplicateSocket(SOCKET _s, uint _process_id, WSAPROTOCOL_INFO* _info)
{
#ifdef _UNICODE
    const char _name_[] = "WSADuplicateSocketW";
    //
    static ModuleProc3<int, SOCKET, uint, WSAPROTOCOL_INFO*> DuplicateSocket(GetSocketModule(), _name_);
#else
    const char _name_[] = "WSADuplicateSocketA";
    //
    static ModuleProc3<int, SOCKET, uint, WSAPROTOCOL_INFO*> DuplicateSocket(GetSocketModule(), _name_);
#endif
    return DuplicateSocket(_s, _process_id, _info);
}

hostent* SocketModule::GetHostByAddress(const char* _address, int _count, int _type)
{
    const char _name_[] = "gethostbyaddr";
    //
    static ModuleProc3<hostent*, const char*, int, int> GetHostByAddress(GetSocketModule(), _name_);
    return GetHostByAddress(_address, _count, _type);
}

HANDLE SocketModule::GetHostByAddress(HWND _hwnd, uint _msg, const char* _addr, int _addr_count, int _type, char* _buf, int _count)
{
    const char _name_[] = "WSAAsyncGetHostByAddr";
    //
    static ModuleProc7<HANDLE, HWND, uint, const char*, int, int, char*, int> GetHostByAddress(GetSocketModule(), _name_);
    return GetHostByAddress(_hwnd, _msg, _addr, _addr_count, _type, _buf, _count);
}

hostent* SocketModule::GetHostByName(const char* _name)
{
    const char _name_[] = "gethostbyname";
    //
    static ModuleProc1<hostent*, const char*> GetHostByName(GetSocketModule(), _name_);
    return GetHostByName(_name);
}

HANDLE SocketModule::GetHostByName(HWND _hwnd, uint _msg, const char* _name, char* _buf, int _count)
{
    const char _name_[] = "WSAAsyncGetHostByName";
    //
    static ModuleProc5<HANDLE, HWND, uint, const char*, char*, int> GetHostByName(GetSocketModule(), _name_);
    return GetHostByName(_hwnd, _msg, _name, _buf, _count);
}

int SocketModule::GetHostName(char* _name, int _count)
{
    const char _name_[] = "gethostname";
    //
    static ModuleProc2<int, const char*, int> GetHostName(GetSocketModule(), _name_);
    return GetHostName(_name, _count);
}

int SocketModule::GetPeerName(SOCKET _s, sockaddr* _name, int* _count)
{
    const char _name_[] = "getpeername";
    //
    static ModuleProc3<int, SOCKET, sockaddr*, int*> GetPeerName(GetSocketModule(), _name_);
    return GetPeerName(_s, _name, _count);
}

protoent* SocketModule::GetProtocolByName(const char* _name)
{
    const char _name_[] = "getprotobyname";
    //
    static ModuleProc1<protoent*, const char*> GetProtocolByName(GetSocketModule(), _name_);
    return GetProtocolByName(_name);
}

HANDLE SocketModule::GetProtocolByName(HWND _hwnd, uint _msg, const char* _name, char* _buf, int _count)
{
    const char _name_[] = "WSAAsyncGetProtoByName";
    //
    static ModuleProc5<HANDLE, HWND, uint, const char*, char*, int> GetProtocolByName(GetSocketModule(), _name_);
    return GetProtocolByName(_hwnd, _msg, _name, _buf, _count);
}

protoent* SocketModule::GetProtocolByNumber(int _n)
{
    const char _name_[] = "getprotobynumber";
    //
    static ModuleProc1<protoent*, int> GetProtocolByNumber(GetSocketModule(), _name_);
    return GetProtocolByNumber(_n);
}

HANDLE SocketModule::GetProtocolByNumber(HWND _hwnd, uint _msg, int _number, char* _buf, int _count)
{
    const char _name_[] = "WSAAsyncGetProtoByNumber";
    //
    static ModuleProc5<HANDLE, HWND, uint, int, char*, int> GetProtocolByNumber(GetSocketModule(), _name_);
    return GetProtocolByNumber(_hwnd, _msg, _number, _buf, _count);
}

servent* SocketModule::GetServiceByName(const char* _name, const char* _protocol)
{
    const char _name_[] = "getservbyname";
    //
    static ModuleProc2<servent*, const char*, const char*> GetServiceByName(GetSocketModule(), _name_);
    return GetServiceByName(_name, _protocol);
}

HANDLE SocketModule::GetServiceByName(HWND _hwnd, uint _msg, const char* _name, const char* _protocol, char* _buf, int _count)
{
    const char _name_[] = "WSAAsyncGetServByName";
    //
    static ModuleProc6<HANDLE, HWND, uint, const char*, const char*, char*, int> GetServiceByName(GetSocketModule(), _name_);
    return GetServiceByName(_hwnd, _msg, _name, _protocol, _buf, _count);
}

servent* SocketModule::GetServerByPort(int _port, const char* _protocol)
{
    const char _name_[] = "getservbyport";
    //
    static ModuleProc2<servent*, int, const char*> GetServerByPort(GetSocketModule(), _name_);
    return GetServerByPort(_port, _protocol);
}

HANDLE SocketModule::GetServerByPort(HWND _hwnd, uint _msg, int _port, const char* _protocol, char* _buf, int _count)
{
    const char _name_[] = "WSAAsyncGetServByPort";
    //
    static ModuleProc6<HANDLE, HWND, uint, int, const char*, char*, int> GetServerByPort(GetSocketModule(), _name_);
    return GetServerByPort(_hwnd, _msg, _port, _protocol, _buf, _count);
}

int SocketModule::GetSocketName(SOCKET _s, sockaddr* _name, int* _count)
{
    const char _name_[] = "getsockname";
    //
    static ModuleProc3<int, SOCKET, sockaddr*, int*> GetSocketName(GetSocketModule(), _name_);
    return GetSocketName(_s, _name, _count);
}

int SocketModule::GetSocketOption(SOCKET _s, int _level, int _optname, char* _optval, int* _optcount)
{
    const char _name_[] = "getsockopt";
    //
    static ModuleProc5<int, SOCKET, int, int, char*, int*> GetSocketOption(GetSocketModule(), _name_);
    return GetSocketOption(_s, _level, _optname, _optval, _optcount);
}

int SocketModule::SetSocketOption(SOCKET _s, int _level, int _optname, const char* _optval, int _optcount)
{
    const char _name_[] = "setsockopt";
    //
    static ModuleProc5<int, SOCKET, int, int, const char*, int> SetSocketOption(GetSocketModule(), _name_);
    return SetSocketOption(_s, _level, _optname, _optval, _optcount);
}

ushort SocketModule::HtoNS(ushort _host_short)
{
    const char _name_[] = "htons";
    //
    static ModuleProc1<ushort, ushort> HtoNS(GetSocketModule(), _name_);
    return HtoNS(_host_short);
}

int SocketModule::HtoNS(SOCKET _s, ushort _host_short, ushort* _net_short)
{
    const char _name_[] = "WSAHtons";
    //
    static ModuleProc3<int, SOCKET, ushort, ushort*> HtoNS(GetSocketModule(), _name_);
    return HtoNS(_s, _host_short, _net_short);
}

ulong SocketModule::HtoNL(ulong _host_long)
{
    const char _name_[] = "htonl";
    //
    static ModuleProc1<ulong, ulong> HtoNL(GetSocketModule(), _name_);
    return HtoNL(_host_long);
}

int SocketModule::HtoNL(SOCKET _s, ulong _host_long, ulong* _net_long)
{
    const char _name_[] = "WSAHtonl";
    //
    static ModuleProc3<int, SOCKET, ulong, ulong*> HtoNL(GetSocketModule(), _name_);
    return HtoNL(_s, _host_long, _net_long);
}

ushort SocketModule::NtoHS(ushort _net_short)
{
    const char _name_[] = "ntohs";
    //
    static ModuleProc1<ushort, ushort> NtoHS(GetSocketModule(), _name_);
    return NtoHS(_net_short);
}

int SocketModule::NtoHS(SOCKET _s, ushort _net_short, ushort* _host_short)
{
    const char _name_[] = "WSANtohs";
    //
    static ModuleProc3<int, SOCKET, ushort, ushort*> NtoHS(GetSocketModule(), _name_);
    return NtoHS(_s, _net_short, _host_short);
}

ulong SocketModule::NtoHL(ulong _net_long)
{
    const char _name_[] = "ntohl";
    //
    static ModuleProc1<ulong, ulong> NtoHL(GetSocketModule(), _name_);
    return NtoHL(_net_long);
}

int SocketModule::NtoHL(SOCKET _s, ulong _net_long, ulong* _host_long)
{
    const char _name_[] = "WSANtohl";
    //
    static ModuleProc3<int, SOCKET, ulong, ulong*> NtoHL(GetSocketModule(), _name_);
    return NtoHL(_s, _net_long, _host_long);
}

ulong SocketModule::InetAddress(const char* _address)
{
    const char _name_[] = "inet_addr";
    //
    static ModuleProc1<ulong, const char*> InetAddress(GetSocketModule(), _name_);
    return InetAddress(_address);
}

char* SocketModule::InetNtoA(in_addr _address)
{
    const char _name_[] = "inet_ntoa";
    //
    static ModuleProc1<char*, in_addr> InetNtoA(GetSocketModule(), _name_);
    return InetNtoA(_address);
}

int SocketModule::AddressToString(sockaddr* _address, ulong _count, WSAPROTOCOL_INFO* _info, tchar* _string, ulong* _string_length)
{
    const char _name_[] = "WSAAddressToString";
    //
    static ModuleProc5<int, sockaddr*, ulong, WSAPROTOCOL_INFO*, tchar*, ulong*> AddressToString(GetSocketModule(), _name_);
    return AddressToString(_address, _count, _info, _string, _string_length);
}

int SocketModule::StringToAddress(tchar* _string, int _af, WSAPROTOCOL_INFO* _info, sockaddr* _address, int* _count)
{
    const char _name_[] = "WSAStringToAddress";
    //
    static ModuleProc5<int, tchar*, int, WSAPROTOCOL_INFO*, sockaddr*, int*> StringToAddress(GetSocketModule(), _name_);
    return StringToAddress(_string, _af, _info, _address, _count);
}

int SocketModule::IoctlSocket(SOCKET _s, long _command, ulong* _arg)
{
    const char _name_[] = "ioctlsocket";
    //
    static ModuleProc3<int, SOCKET, long, ulong*> IoctlSocket(GetSocketModule(), _name_);
    return IoctlSocket(_s, _command, _arg);
}

int SocketModule::IoctlSocket(SOCKET _s, uint _code, void* _in_buff, uint _in_count, void* _out_buff, uint _out_count, uint* _count, WSAOVERLAPPED* _o, LPWSAOVERLAPPED_COMPLETION_ROUTINE _route)
{
    const char _name_[] = "WSAIoctl";
    //
    static ModuleProc9<int, SOCKET, uint, void*, uint, void*, uint, uint*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE> IoctlSocket(GetSocketModule(), _name_);
    return IoctlSocket(_s, _code, _in_buff, _in_count, _out_buff, _out_count, _count, _o, _route);
}

SOCKET SocketModule::Accept(SOCKET _s, sockaddr* _address, int* _count)
{
    const char _name_[] = "accept";
    //
    static ModuleProc3<SOCKET, SOCKET, sockaddr*, int*> Accept(GetSocketModule(), _name_);
    return Accept(_s, _address, _count);
}

SOCKET SocketModule::Accept(SOCKET _s, sockaddr* _addr, int* _count, LPCONDITIONPROC _cond, uint _data)
{
    const char _name_[] = "WSAAccept";
    //
    static ModuleProc5<SOCKET, SOCKET, sockaddr*, int*, LPCONDITIONPROC, uint> Accept(GetSocketModule(), _name_);
    return Accept(_s, _addr, _count, _cond, _data);
}

int SocketModule::Bind(SOCKET _s, const sockaddr* _name, int _count)
{
    const char _name_[] = "bind";
    //
    static ModuleProc3<int, SOCKET, const sockaddr*, int> Bind(GetSocketModule(), _name_);
    return Bind(_s, _name, _count);
}

int SocketModule::Listen(SOCKET _s, int _queue_size)
{
    const char _name_[] = "listen";
    //
    static ModuleProc2<int, SOCKET, int> Listen(GetSocketModule(), _name_);
    return Listen(_s, _queue_size);
}

int SocketModule::Connect(SOCKET _s, const sockaddr* _name, int _count)
{
    const char _name_[] = "connect";
    //
    static ModuleProc3<int, SOCKET, const sockaddr*, int> Connect(GetSocketModule(), _name_);
    return Connect(_s, _name, _count);
}

int SocketModule::Connect(SOCKET _s, const sockaddr* _addr, int _count, WSABUF* _buff1, WSABUF* _buff2, QOS* _qos1, QOS* _qos2)
{
    const char _name_[] = "WSAConnect";
    //
    static ModuleProc7<int, SOCKET, const sockaddr*, int, WSABUF*, WSABUF*, QOS*, QOS*> Connect(GetSocketModule(), _name_);
    return Connect(_s, _addr, _count, _buff1, _buff2, _qos1, _qos2);
}

int SocketModule::Receive(SOCKET _s, char* _buffer, int _count, int _flags)
{
    const char _name_[] = "recv";
    //
    static ModuleProc4<int, SOCKET, char*, int, int> Receive(GetSocketModule(), _name_);
    return Receive(_s, _buffer, _count, _flags);
}

int SocketModule::Receive(SOCKET _s, WSABUF* _buff, uint _count, uint* _received, uint* _flags, WSAOVERLAPPED* _o, LPWSAOVERLAPPED_COMPLETION_ROUTINE _route)
{
    const char _name_[] = "WSARecv";
    //
    static ModuleProc7<int, SOCKET, WSABUF*, uint, uint*, uint*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE> Receive(GetSocketModule(), _name_);
    return Receive(_s, _buff, _count, _received, _flags, _o, _route);
}

int SocketModule::ReceiveDisconnect(SOCKET _s, WSABUF* _buff)
{
    const char _name_[] = "WSARecvDisconnect";
    //
    static ModuleProc2<int, SOCKET, WSABUF*> ReceiveDisconnect(GetSocketModule(), _name_);
    return ReceiveDisconnect(_s, _buff);
}

int SocketModule::ReceiveFrom(SOCKET _s, char* _buffer, int _count, int _flags, sockaddr* _from_name, int* _from_count)
{
    const char _name_[] = "recvfrom";
    //
    static ModuleProc6<int, SOCKET, char*, int, int, sockaddr*, int*> ReceiveFrom(GetSocketModule(), _name_);
    return ReceiveFrom(_s, _buffer, _count, _flags, _from_name, _from_count);
}

int SocketModule::ReceiveFrom(SOCKET _s, WSABUF* _buff, uint _count, uint* _received, uint* _flags, sockaddr* _addr, int* _count_from, WSAOVERLAPPED* _o, LPWSAOVERLAPPED_COMPLETION_ROUTINE _route)
{
    const char _name_[] = "WSARecvFrom";
    //
    static ModuleProc9<int, SOCKET, WSABUF*, uint, uint*, uint*, sockaddr*, int*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE> ReceiveFrom(GetSocketModule(), _name_);
    return ReceiveFrom(_s, _buff, _count, _received, _flags, _addr, _count_from, _o, _route);
}

int SocketModule::Send(SOCKET _s, const char* _buffer, int _count, int _flags)
{
    const char _name_[] = "send";
    //
    static ModuleProc4<int, SOCKET, const char*, int, int> Send(GetSocketModule(), _name_);
    return Send(_s, _buffer, _count, _flags);
}

int SocketModule::Send(SOCKET _s, WSABUF* _buff, uint _count, uint* _sended, uint _flags, WSAOVERLAPPED* _o, LPWSAOVERLAPPED_COMPLETION_ROUTINE _route)
{
    const char _name_[] = "WSASend";
    //
    static ModuleProc7<int, SOCKET, WSABUF*, uint, uint*, uint, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE> Send(GetSocketModule(), _name_);
    return Send(_s, _buff, _count, _sended, _flags, _o, _route);
}

int SocketModule::SendDisconnect(SOCKET _s, WSABUF* _buff)
{
    const char _name_[] = "WSASendDisconnect";
    //
    static ModuleProc2<int, SOCKET, WSABUF*> SendDisconnect(GetSocketModule(), _name_);
    return SendDisconnect(_s, _buff);
}

int SocketModule::SendTo(SOCKET _s, const char* _buffer, int _count, int _flags, const sockaddr* _to_name, int _to_count)
{
    const char _name_[] = "sendto";
    //
    static ModuleProc6<int, SOCKET, const char*, int, int, const sockaddr*, int> SendTo(GetSocketModule(), _name_);
    return SendTo(_s, _buffer, _count, _flags, _to_name, _to_count);
}

int SocketModule::SendTo(SOCKET _s, WSABUF* _buff, uint _count, uint* _sent, uint _flags, const sockaddr* _to, int _to_count, WSAOVERLAPPED* _o, LPWSAOVERLAPPED_COMPLETION_ROUTINE _route)
{
    const char _name_[] = "WSASendTo";
    //
    static ModuleProc9<int, SOCKET, WSABUF*, uint, uint*, uint, const sockaddr*, int, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE> SendTo(GetSocketModule(), _name_);
    return SendTo(_s, _buff, _count, _sent, _flags, _to, _to_count, _o, _route);
}

int SocketModule::Select(int _dummy, fd_set* _read, fd_set* _write, fd_set* _excpt, const timeval* _timeout)
{
    const char _name_[] = "select";
    //
    static ModuleProc5<int, int, fd_set*, fd_set*, fd_set*, const timeval*> Select(GetSocketModule(), _name_);
    return Select(_dummy, _read, _write, _excpt, _timeout);
}

int SocketModule::Select(SOCKET _s, HWND _hwnd, uint _msg, long _event)
{
    const char _name_[] = "WSAAsyncSelect";
    //
    static ModuleProc4<int, SOCKET, HWND, uint, long> Select(GetSocketModule(), _name_);
    return Select(_s, _hwnd, _msg, _event);
}

bool SocketModule::GetQOSByName(SOCKET _s, WSABUF* _buff, QOS* _qos)
{
    const char _name_[] = "WSAGetQOSByName";
    //
    static ModuleProc3<bool, SOCKET, WSABUF*, QOS*> GetQOSByName(GetSocketModule(), _name_);
    return GetQOSByName(_s, _buff, _qos) == 1;
}

SOCKET SocketModule::JoinLeaf(SOCKET _s, const sockaddr* _addr, int _count, WSABUF* _buff1, WSABUF* _buff2, QOS* _qos1, QOS* _qos2, uint _flags)
{
    const char _name_[] = "WSAJoinLeaf";
    //
    static ModuleProc8<SOCKET, SOCKET, const sockaddr*, int, WSABUF*, WSABUF*, QOS*, QOS*, uint> JoinLeaf(GetSocketModule(), _name_);
    return JoinLeaf(_s, _addr, _count, _buff1, _buff2, _qos1, _qos2, _flags);
}

int SocketModule::Shutdown(SOCKET _s, int _how)
{
    const char _name_[] = "shutdown";
    //
    static ModuleProc2<int, SOCKET, int> Shutdown(GetSocketModule(), _name_);
    return Shutdown(_s, _how);
}

int SocketModule::CancelAsyncRequest(HANDLE _handle)
{
    const char _name_[] = "WSACancelAsyncRequest";
    //
    static ModuleProc1<int, HANDLE> CancelAsyncRequest(GetSocketModule(), _name_);
    return CancelAsyncRequest(_handle);
}

int SocketModule::GetServiceClassInfo(GUID* _provider_id, GUID* _service_id, ulong* _count, WSASERVICECLASSINFO* _info)
{
    const char _name_[] = "WSAGetServiceClassInfo";
    //
    static ModuleProc4<int, GUID*, GUID*, ulong*, WSASERVICECLASSINFO*> GetServiceClassInfo(GetSocketModule(), _name_);
    return GetServiceClassInfo(_provider_id, _service_id, _count, _info);
}

int SocketModule::GetServiceClassNameByClassId(GUID* _service_id, tchar* _name, ulong* _count)
{
    const char _name_[] = "WSAGetServiceClassNameByClassId";
    //
    static ModuleProc3<int, GUID*, tchar*, ulong*> GetServiceClassNameByClassId(GetSocketModule(), _name_);
    return GetServiceClassNameByClassId(_service_id, _name, _count);
}

int SocketModule::InstallServiceClass(WSASERVICECLASSINFO* _info)
{
    const char _name_[] = "WSAInstallServiceClass";
    //
    static ModuleProc1<int, WSASERVICECLASSINFO*> InstallServiceClass(GetSocketModule(), _name_);
    return InstallServiceClass(_info);
}

int SocketModule::SetService(WSAQUERYSET* _info, WSAESETSERVICEOP _op, ulong _flags)
{
    const char _name_[] = "WSASetService";
    //
    static ModuleProc3<int, WSAQUERYSET*, WSAESETSERVICEOP, ulong> SetService(GetSocketModule(), _name_);
    return SetService(_info, _op, _flags);
}

int SocketModule::RemoveServiceClass(GUID* _service_id)
{
    const char _name_[] = "WSARemoveServiceClass";
    //
    static ModuleProc1<int, GUID*> RemoveServiceClass(GetSocketModule(), _name_);
    return RemoveServiceClass(_service_id);
}

int SocketModule::LookupServiceBegin(WSAQUERYSET* _info, ulong _flags, HANDLE* _hlookup)
{
    const char _name_[] = "WSALookupServiceBegin";
    //
    static ModuleProc3<int, WSAQUERYSET*, ulong, HANDLE*> LookupServiceBegin(GetSocketModule(), _name_);
    return LookupServiceBegin(_info, _flags, _hlookup);
}

int SocketModule::LookupServiceNext(HANDLE _hlookup, ulong _flags, ulong* _count, WSAQUERYSET* _info)
{
    const char _name_[] = "WSALookupServiceNext";
    //
    static ModuleProc4<int, HANDLE, ulong, ulong*, WSAQUERYSET*> LookupServiceNext(GetSocketModule(), _name_);
    return LookupServiceNext(_hlookup, _flags, _count, _info);
}

int SocketModule::LookupServiceEnd(HANDLE _hlookup)
{
    const char _name_[] = "WSALookupServiceEnd";
    //
    static ModuleProc1<int, HANDLE> LookupServiceEnd(GetSocketModule(), _name_);
    return LookupServiceEnd(_hlookup);
}

int SocketModule::EnumNameSpaceProviders(ulong* _count, WSANAMESPACE_INFO* _info)
{
    const char _name_[] = "WSAEnumNameSpaceProviders";
    //
    static ModuleProc2<int, ulong*, WSANAMESPACE_INFO*> EnumNameSpaceProviders(GetSocketModule(), _name_);
    return EnumNameSpaceProviders(_count, _info);
}

int SocketModule::ProviderConfigChange(HANDLE* _notify_handle, WSAOVERLAPPED* _overlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE _routine)
{
    const char _name_[] = "WSAProviderConfigChange";
    //
    static ModuleProc3<int, HANDLE*, WSAOVERLAPPED*, LPWSAOVERLAPPED_COMPLETION_ROUTINE> ProviderConfigChange(GetSocketModule(), _name_);
    return ProviderConfigChange(_notify_handle, _overlapped, _routine);
}

int SocketModule::EnumProtocols(int* _protocols, WSAPROTOCOL_INFO* _buff, ulong* _count)
{
#ifdef _UNICODE
    const char _name_[] = "WSAEnumProtocolsW";
    //
    static ModuleProc3<int, int*, WSAPROTOCOL_INFO*, ulong*> EnumProtocols(GetSocketModule(), _name_);
#else
    const char _name_[] = "WSAEnumProtocolsA";
    //
    static ModuleProc3<int, int*, WSAPROTOCOL_INFO*, ulong*> EnumProtocols(GetSocketModule(), _name_);
#endif
    return EnumProtocols(_protocols, _buff, _count);
}

WSAEVENT SocketModule::CreateEvent()
{
    const char _name_[] = "WSACreateEvent";
    //
    static ModuleProc0<WSAEVENT> CreateEvent(GetSocketModule(), _name_);
    return CreateEvent();
}

bool SocketModule::CloseEvent(WSAEVENT _event)
{
    const char _name_[] = "WSACloseEvent";
    //
    static ModuleProc1<bool, WSAEVENT> CloseEvent(GetSocketModule(), _name_);
    return CloseEvent(_event) == 1;
}

int SocketModule::EventSelect(SOCKET _s, WSAEVENT _event, long _count)
{
    const char _name_[] = "WSAEventSelect";
    //
    static ModuleProc3<int, SOCKET, WSAEVENT, long> EventSelect(GetSocketModule(), _name_);
    return EventSelect(_s, _event, _count);
}

bool SocketModule::SetEvent(WSAEVENT _event)
{
    const char _name_[] = "WSASetEvent";
    //
    static ModuleProc1<bool, WSAEVENT> SetEvent(GetSocketModule(), _name_);
    return SetEvent(_event) == 1;
}

bool SocketModule::ResetEvent(WSAEVENT _event)
{
    const char _name_[] = "WSAResetEvent";
    //
    static ModuleProc1<BOOL, WSAEVENT> ResetEvent(GetSocketModule(), _name_);
    return ResetEvent(_event) == 1;
}

int SocketModule::EnumNetworkEvents(SOCKET _s, WSAEVENT _event, WSANETWORKEVENTS* _events)
{
    const char _name_[] = "WSAEnumNetworkEvents";
    //
    static ModuleProc3<int, SOCKET, WSAEVENT, WSANETWORKEVENTS*> EnumNetworkEvents(GetSocketModule(), _name_);
    return EnumNetworkEvents(_s, _event, _events);
}

uint SocketModule::WaitForMultipleEvents(uint _count, const WSAEVENT* _events, bool _wait_all, uint _timeout, bool _alertable)
{
    const char _name_[] = "WSAWaitForMultipleEvents";
    //
    static ModuleProc5<uint, uint, const WSAEVENT*, bool, uint, bool> WaitForMultipleEvents(GetSocketModule(), _name_);
    return WaitForMultipleEvents(_count, _events, _wait_all, _timeout, _alertable);
}

int SocketModule::FDIsSet(SOCKET _s, fd_set* _fdset)
{
    const char _name_[] = "__WSAFDIsSet";
    //
    static ModuleProc2<int, SOCKET, fd_set*> __WSAFDIsSet(GetSocketModule(), _name_);
    return __WSAFDIsSet(_s, _fdset);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_SOCKET_MODULE_INC__
#   include <PalmSocketModule.inc>
#endif

#ifdef __PALM_OS__ 

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmSocketModule
// ----- ----------------
Err PalmSocketModule::Error = errNone;
//
PalmSocketModule::PalmSocketModule(bool _unload)
                : PalmModule("Net.Lib", netCreator, netLibType, _unload)
{
}

PalmSocketModule::~PalmSocketModule()
{
    Close();
}

Err PalmSocketModule::Open()
{
    Err err = ::NetLibOpen(Handle, &PalmSocketModule::Error);
    return err;
}

Err PalmSocketModule::Close()
{
    Err err = ::NetLibClose(Handle, true);
    Count++; // DO NOT remove the library
    return err;
}

PalmModule& PalmSocketModule::GetSocketModule()
{
    static PalmSocketModule _the_module_;
    //
    if(!_the_module_.IsValid())
    {
        _the_module_.LoadModule();
    }
    return _the_module_;
}

socket_t PalmSocketModule::CreateSocket(NetSocketAddrEnum _address, NetSocketTypeEnum _type, int16 _protocol, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketOpen(PalmSocketModule::GetSocketModule(), _address, _type, _protocol, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::CloseSocket(socket_t _socket, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketClose(PalmSocketModule::GetSocketModule(), _socket, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::Shutdown(socket_t _socket, int16 _dir, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketShutdown(PalmSocketModule::GetSocketModule(), _socket, _dir, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::Connect(socket_t _socket, sockaddr_t* _address, int16 _addr_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketConnect(PalmSocketModule::GetSocketModule(), _socket, _address, _addr_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

socket_t PalmSocketModule::Accept(socket_t _socket, sockaddr_t* _address, int16& _addr_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return static_cast<socket_t>(::NetLibSocketAccept(PalmSocketModule::GetSocketModule(), _socket, _address, &_addr_size, PalmOS::SecondsToTicks(_timeout), &Error));
}

int16 PalmSocketModule::Bind(socket_t _socket, sockaddr_t* _address, int16 _addr_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketBind(PalmSocketModule::GetSocketModule(), _socket, _address, _addr_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::Listen(socket_t _socket, uint16 _queue_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketListen(PalmSocketModule::GetSocketModule(), _socket, _queue_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

hostent_t* PalmSocketModule::GetHostByAddress(hostent_buf_t& _info, sockaddr_t* _address, uint16 _addr_size, uint16 _type, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibGetHostByAddr(PalmSocketModule::GetSocketModule(), reinterpret_cast<uint8*>(_address), _addr_size, _type, &_info, PalmOS::SecondsToTicks(_timeout), &Error);
}

hostent_t* PalmSocketModule::GetHostByName(hostent_buf_t& _info, char* _name, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_name != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibGetHostByName(PalmSocketModule::GetSocketModule(), _name, &_info, PalmOS::SecondsToTicks(_timeout), &Error);
}

Err PalmSocketModule::GetHostName(char* _name, uint16& _count)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_name != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return Error = ::NetLibSettingGet(PalmSocketModule::GetSocketModule(), netSettingHostName, _name, &_count);
}

int16 PalmSocketModule::GetPeerName(socket_t _socket, sockaddr_t* _remote_address, int16& _remote_addr_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_remote_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    //
    sockaddr_t local_address;
    int16 local_addr_size;
    return ::NetLibSocketAddr(PalmSocketModule::GetSocketModule(), _socket, &local_address, &local_addr_size, _remote_address, &_remote_addr_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::GetSocketName(socket_t _socket, sockaddr_t* _local_address, int16& _local_addr_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_local_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    //    
    sockaddr_t remote_address;
    int16 remote_addr_size;
    return ::NetLibSocketAddr(PalmSocketModule::GetSocketModule(), _socket, _local_address, &_local_addr_size, &remote_address, &remote_addr_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

servent_t* PalmSocketModule::GetServiceByName(servent_buf_t& _serv, const char* _serv_name, const char* _proto_name, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_serv_name != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_proto_name != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibGetServByName(PalmSocketModule::GetSocketModule(), _serv_name, _proto_name, &_serv, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::GetSocketOption(socket_t _socket, uint16 _level, uint16 _op, void* _op_value, uint16& _op_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_op_value != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketOptionGet(PalmSocketModule::GetSocketModule(), _socket, _level, _op, _op_value, &_op_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::SetSocketOption(socket_t _socket, uint16 _level, uint16 _op, void* _op_value, uint16 _op_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_op_value != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSocketOptionSet(PalmSocketModule::GetSocketModule(), _socket, _level, _op, _op_value, _op_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

in_addr_t PalmSocketModule::InetAddress(char* _ip)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_ip != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibAddrAToIN(PalmSocketModule::GetSocketModule(), _ip);
}

char* PalmSocketModule::InetNtoA(in_addr_t _ip, char* _buffer)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_buffer != null, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibAddrINToA(PalmSocketModule::GetSocketModule(), _ip, _buffer);
}

int16 PalmSocketModule::Receive(socket_t _socket, byte* _buffer, uint16 _buff_count, uint16 _flags, sockaddr_t* _remote_address, uint16& _remote_addr_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_buffer != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_remote_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibReceive(PalmSocketModule::GetSocketModule(), _socket, _buffer, _buff_count, _flags, _remote_address, &_remote_addr_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::ReceiveFrom(socket_t _socket, NetIOParamType& _io_param, uint16 _flags, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibReceivePB(PalmSocketModule::GetSocketModule(), _socket, &_io_param, _flags, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::Send(socket_t _socket, byte* _buffer, uint16 _buff_count, uint16 _flags, sockaddr_t* _remote_address, uint16 _remote_addr_size, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_buffer != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    palmxassert(_remote_address != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSend(PalmSocketModule::GetSocketModule(), _socket, _buffer, _buff_count, _flags, _remote_address, _remote_addr_size, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::SendTo(socket_t _socket, NetIOParamType& _io_param, uint16 _flags, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    palmxassert(_socket != 0, Error::eInvalidArg, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSendPB(PalmSocketModule::GetSocketModule(), _socket, &_io_param, _flags, PalmOS::SecondsToTicks(_timeout), &Error);
}

int16 PalmSocketModule::Select(uint16 _width, fd_set_t* _read_fds, fd_set_t* _write_fds, fd_set_t* _except_fds, uint16 _timeout)
{
    palmxassert(PalmSocketModule::GetSocketModule().IsValid(), XPalmModule::eLibNotFound, PalmSocketModule::XPalmSocketModule);
    return ::NetLibSelect(PalmSocketModule::GetSocketModule(), _width, _read_fds, _write_fds, _except_fds, PalmOS::SecondsToTicks(_timeout), &Error);
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmSocketModule
// ----- -----------------
void PalmSocketModule::XPalmSocketModule::LoadErrorDescriptions()
{
    // base class
    PalmModule::XPalmModule::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__ 


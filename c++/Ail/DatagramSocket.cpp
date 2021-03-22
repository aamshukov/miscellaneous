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

#ifndef __DATAGRAM_SOCKET_INC__
#   include <DatagramSocket.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class DatagramSocket
// ----- --------------
DatagramSocket::DatagramSocket()
{
}

DatagramSocket::DatagramSocket(const IPv4Address& _remote_address, const IPv4Address& _local_address)
              : Socket(_remote_address, _local_address)
{
}

DatagramSocket::~DatagramSocket()
{
    Disconnect();
}

void DatagramSocket::Create(bool _bind, ushort _proto)
{
    Socket::xxassert(*this, State != Socket::Connected);
    Socket::xxassert(*this, (Socket_ = SocketModule::CreateSocket(AF_INET, SOCK_DGRAM, _proto)) != INVALID_SOCKET);
    // for SOCKS bind could be ignored
    if(_bind)
    {
        Socket::xxassert(*this, SocketModule::Bind(Socket_, LocalAddress, LocalAddress.GetSize()) == 0);
    }
    //
    State = Socket::Connected;
}

void DatagramSocket::Connect(bool _bind, int, ushort _proto)
{
    Socket::xxassert(*this, State != Socket::Connected);
    Socket::xxassert(*this, (Socket_ = SocketModule::CreateSocket(AF_INET, SOCK_DGRAM, _proto)) != INVALID_SOCKET);
    // for SOCKS bind could be ignored
    if(_bind)
    {
        Socket::xxassert(*this, SocketModule::Bind(Socket_, LocalAddress, LocalAddress.GetSize()) == 0);
    }
    Socket::xxassert(*this, SocketModule::Connect(Socket_, RemoteAddress, sizeof(RemoteAddress.GetInetAddress())) == 0);
    //
    int size = LocalAddress.GetSize();
    Socket::xxassert(*this, SocketModule::GetSocketName(Socket_, LocalAddress, &size) == 0);
    //
    State = Socket::Connected;
}

void DatagramSocket::Disconnect()
{
    if(State == Socket::Connected)
    {
        Socket::xxassert(*this, SocketModule::CloseSocket(Socket_) == 0);
        //
        State   = Socket::Disconnected;
        Socket_ = INVALID_SOCKET;
    }
}

int DatagramSocket::Send(const byte* _data, int _count, int _timeout, int _flags)
{
    Socket::xxassert(*this, State == Socket::Connected);
    Socket::xxassert(*this, _data != null && _count > 0);
    //
    int rc = SetTimeout(_timeout, 2);

    if(rc == 0 || rc == SOCKET_ERROR)
    {
        return rc;
    }
    return SocketModule::Send(Socket_, reinterpret_cast<char*>(const_cast<byte*>(_data)), _count, _flags);
}

int DatagramSocket::SendTo(const byte* _data, int _count, const IPv4Address& _remote_address, int _timeout, int _flags)
{
    Socket::xxassert(*this, State == Socket::Connected);
    Socket::xxassert(*this, _data != null && _count > 0);
    //
    int rc = SetTimeout(_timeout, 2);

    if(rc == 0 || rc == SOCKET_ERROR)
    {
        return rc;
    }
    return SocketModule::SendTo(Socket_, reinterpret_cast<char*>(const_cast<byte*>(_data)), _count, _flags, _remote_address, _remote_address.GetSize());
}

int DatagramSocket::Receive(byte* _buffer, int _count, int _timeout, int _flags)
{
    Socket::xxassert(*this, State == Socket::Connected);
    Socket::xxassert(*this, _buffer != null && _count > 0);
    //
    int rc = SetTimeout(_timeout, 1);

    if(rc == 0 || rc == SOCKET_ERROR)
    {
        return rc;
    }
    return SocketModule::Receive(Socket_, reinterpret_cast<char*>(_buffer), _count, _flags);
}

int DatagramSocket::ReceiveFrom(byte* _buffer, int _count, IPv4Address& _remote_address, int _timeout, int _flags)
{
    Socket::xxassert(*this, State == Socket::Connected);
    Socket::xxassert(*this, _buffer != null && _count > 0);
    //
    int size = _remote_address.GetSize();
    int rc = SetTimeout(_timeout, 1);

    if(rc == 0 || rc == SOCKET_ERROR)
    {
        return rc;
    }
    return SocketModule::ReceiveFrom(Socket_, reinterpret_cast<char*>(_buffer), _count, _flags, _remote_address, &size);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

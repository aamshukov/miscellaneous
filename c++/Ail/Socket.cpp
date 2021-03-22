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

#ifndef __SOCKET_INC__
#   include <Socket.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Socket
// ----- ------
const IPv4Address Socket::DummyIP;
//
Socket::Socket() : State(Socket::Unknown), Socket_(-1)
{
}

Socket::Socket(const IPv4Address& _remote_address, const IPv4Address& _local_address)
      : State(Socket::Unknown), LocalAddress(_local_address), RemoteAddress(_remote_address), Socket_(-1)
{
}

Socket::~Socket()
{
    // should be disconnected in a derive class
}

void Socket::xxassert(Socket& xi_socket, int xi_expr, uint xi_error)
{
    if(xi_expr == 0)
    {
        xi_socket.State = Socket::Invalid;
        throw Socket::XSocket(xi_error);
    }
}

void Socket::GetOptions(int _level, int _optname, byte* _data, int* _len) const
{
    Socket::xxassert(const_cast<Socket&>(*this), _data != null && _len != null);
    Socket::xxassert(const_cast<Socket&>(*this), SocketModule::GetSocketOption(Socket_, _level, _optname, reinterpret_cast<char*>(_data), _len) == 0);
}

void Socket::SetOptions(int _level, int _optname, byte* _data, int _len)
{
    Socket::xxassert(const_cast<Socket&>(*this), _data != null);
    Socket::xxassert(const_cast<Socket&>(*this), SocketModule::SetSocketOption(Socket_, _level, _optname, reinterpret_cast<char*>(_data), _len) == 0);
}

int Socket::SetTimeout(int _timeout, short _mode)
{
    if(_timeout == 0)
    {
        return 1; // ok
    }

    fd_set set;
    FD_ZERO(&set);
    FD_SET(Socket_, &set);

    timeval timeout;
    timeout.tv_sec  = _timeout;
    timeout.tv_usec = 0;

    switch(_mode)
    {
        case 0: // exception
            return SocketModule::Select(0, null, null, &set, &timeout);
        case 1: // read
            return SocketModule::Select(0, &set, null, null, &timeout);
        case 2: // write
            return SocketModule::Select(0, null, &set, null, &timeout);
    }

	return 0;
}

int Socket::SetBufferSize(int _new_size, int _optname)
{
    //
    const ushort _mtu_size_ = 1460;
    //
    int size;
    int trysize;
    int finsize = 0;

    size = sizeof(int);
    SocketModule::GetSocketOption(Socket_, SOL_SOCKET, _optname, reinterpret_cast<char*>(&finsize), &size);

    if(_new_size <= finsize)
    {
        _new_size = finsize << 1;
    }

    for(trysize = _new_size; trysize > _mtu_size_; trysize >>= 1)
    {
        uint err = SocketModule::SetSocketOption(Socket_, SOL_SOCKET, _optname, reinterpret_cast<char*>(&trysize), sizeof(int));

        if(err == SOCKET_ERROR)
        {
            err = SocketModule::GetLastError();

            if(err == WSAENOPROTOOPT || err == WSAEINVAL)
            {
                break;
            }
        }
        else
        {
            size = sizeof(int);
            SocketModule::GetSocketOption(Socket_, SOL_SOCKET, _optname, reinterpret_cast<char*>(&finsize), &size);
            break;
        }
    }
    return finsize;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XSocket
// ----- -------
Socket::XSocket::XSocket(uint xi_error) : X(xi_error, SocketModule::GetLastError())
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

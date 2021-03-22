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

#ifndef __STREAM_SOCKET_INC__
#   include <StreamSocket.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class StreamSocket
// ----- ------------
StreamSocket::StreamSocket()
{
}

StreamSocket::StreamSocket(const IPv4Address& _remote_address, const IPv4Address& _local_address)
            : Socket(_remote_address, _local_address)
{
}

StreamSocket::~StreamSocket()
{
    Disconnect();
}

void StreamSocket::Connect(bool _bind, int _timeout, ushort _proto)
{
    Socket::xxassert(*this, State != Socket::Connected);
    Socket::xxassert(*this, (Socket_ = SocketModule::CreateSocket(AF_INET, SOCK_STREAM, _proto)) != INVALID_SOCKET);

    int flag = 1;
    Socket::xxassert(*this, SocketModule::SetSocketOption(Socket_, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char*>(&flag), sizeof(int)) == 0);

    // for SOCKS bind could be ignored
    if(_bind)
    {
        Socket::xxassert(*this, SocketModule::Bind(Socket_, LocalAddress, LocalAddress.GetSize()) == 0);
    }

    if(_timeout > 0)
    {
        int rc;
        ulong flag = 1;

        // make the socket non-blocking & connect
        Socket::xxassert(*this, SocketModule::IoctlSocket(Socket_, FIONBIO, &flag) == 0);
        Socket::xxassert(*this, SocketModule::Connect(Socket_, RemoteAddress, sizeof(RemoteAddress.GetInetAddress())) == 0 || SocketModule::GetLastError() == WSAEINPROGRESS || SocketModule::GetLastError() == WSAEWOULDBLOCK);

        fd_set wrset;

        FD_ZERO(&wrset);
        FD_SET(Socket_, &wrset);

        timeval timeout;
        timeout.tv_sec  = _timeout;
        timeout.tv_usec = 0;

        rc = SocketModule::Select(0, null, &wrset, null, &timeout);

        if(rc == 0)
        {
            Socket::xxassert(*this, 0, XSocket::Timeout);
        }
        else if(rc == SOCKET_ERROR)
        {
            Socket::xxassert(*this, 0, X::Failure);
        }

        // test if the socket connected
        Socket::xxassert(*this, SocketModule::FDIsSet(Socket_, &wrset), X::Failure);

        // make the socket blocking
        flag = 0;
        Socket::xxassert(*this, SocketModule::IoctlSocket(Socket_, FIONBIO, &flag) == 0);
    }
    else
    {
        Socket::xxassert(*this, SocketModule::Connect(Socket_, RemoteAddress, sizeof(RemoteAddress.GetInetAddress())) == 0);
    }
    //
    int size = LocalAddress.GetSize();
    Socket::xxassert(*this, SocketModule::GetSocketName(Socket_, LocalAddress, &size) == 0);
    //
    State = Socket::Connected;
}

void StreamSocket::Disconnect()
{
    if(State == Socket::Connected)
    {
        Socket::xxassert(*this, SocketModule::Shutdown(Socket_, 1) != -1);
        Discard(0, false);
        Socket::xxassert(*this, SocketModule::CloseSocket(Socket_) == 0);
        //
        State   = Socket::Disconnected;
        Socket_ = INVALID_SOCKET;
    }
}

int StreamSocket::Send(const byte* _data, int _count, int _timeout, int _flags)
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

int StreamSocket::Receive(byte* _buffer, int _count, int _timeout, int _flags)
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

int StreamSocket::ReceiveCount(byte* _buffer, int _count, int _timeout)
{
    Socket::xxassert(*this, State == Socket::Connected);
    Socket::xxassert(*this, _buffer != null && _count > 0);
    //
    int rc;
    int count;

    byte* p_buff = _buffer;

    Time s_time;

    while(_count > 0)
    {
        rc = SetTimeout(_timeout, 1);

        if(rc == 0 || rc == SOCKET_ERROR)
        {
            return rc;
        }

        if((count = SocketModule::Receive(Socket_, reinterpret_cast<char*>(p_buff), _count, 0)) < 1 || count == SOCKET_ERROR)
        {
            break;
        }

        p_buff += count;
       _count  -= count;

        if(_timeout > 0)
        {
           _timeout -= Time(Time::GetCurrentTime()-s_time).GetSeconds();

            if(_timeout <= 0)
            {
                break;
            }
        }
    }

    return (int)(p_buff-_buffer);
}

int StreamSocket::ReceiveLine(byte* _buffer, int _count, int _timeout)
{
    Socket::xxassert(*this, State == Socket::Connected);
    Socket::xxassert(*this, _buffer != null && _count > 0);
    //
    int rc;
    int count;
    int received = 0;

    /////////////////////////////////////////////////////////////////////////
    #define SETTIMEOUT()                                                    \
        rc = SetTimeout(_timeout, 1);                                       \
                                                                            \
        if(rc == 0 || rc == SOCKET_ERROR)                                   \
        {                                                                   \
            return rc;                                                      \
        }                                                   
    #define CHECKTIMEOUT()                                                  \
        if(_timeout > 0)                                                    \
        {                                                                   \
           _timeout -= Time(Time::GetCurrentTime()-s_time).GetSeconds();    \
                                                                            \
            if(_timeout <= 0)                                               \
            {                                                               \
                return (int)(p_buff-_buffer);                               \
            }                                                               \
        }                                                                   \
    /////////////////////////////////////////////////////////////////////////

    byte* p_buff = _buffer;

    --_count;

    Time s_time;

    while(_count > 0)
    {
        SETTIMEOUT()

        if((count = SocketModule::Receive(Socket_, reinterpret_cast<char*>(p_buff), _count, MSG_PEEK)) < 1 || count == SOCKET_ERROR)
        {
            return 0;
        }

        if(_buffer[count-1] == Char::CR)
        {
            count = SocketModule::Receive(Socket_, reinterpret_cast<char*>(p_buff), 1, 0);
            p_buff[1] = 0;
            return received+1;
        }

        // find the first CR/LF 
        for(int i = 0; i < count; ++i)
        {
            if(p_buff[i] == Char::CR && p_buff[i+1] == Char::LF)
            {
                CHECKTIMEOUT()
                SETTIMEOUT()
                count = SocketModule::Receive(Socket_, reinterpret_cast<char*>(p_buff), i+2, 0);
                p_buff[i+2] = 0;
                return received+i+2;
            }
        }   

        // if the CR/LF is not found then copy what is available
        CHECKTIMEOUT()
        SETTIMEOUT()
        count = SocketModule::Receive(Socket_, reinterpret_cast<char*>(p_buff), count, 0);
        received += count;
        p_buff[count]=0;
        p_buff = &p_buff[count];
       _count -= count;
    }
    return received;
    /////////////////////////////////////////////////////////////////////////
    #undef SETTIMEOUT
    #undef CHECKTIMEOUT
    /////////////////////////////////////////////////////////////////////////
}

void StreamSocket::Listen(int _count)
{
    Socket::xxassert(*this, (Socket_ = SocketModule::CreateSocket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET);
    Socket::xxassert(*this, SocketModule::Bind(Socket_, LocalAddress, LocalAddress.GetSize()) == 0);
    Socket::xxassert(*this, SocketModule::Listen(Socket_, _count) == 0);
}

void StreamSocket::Accept(StreamSocket& _socket, int _count)
{
    IPv4Address address;
    int size = address.GetSize();

    SOCKET socket = SocketModule::Accept(Socket_, address, &size);
    Socket::xxassert(*this, SocketModule::GetSocketName(Socket_, LocalAddress, &size) == 0);
    //
   _socket.SetState(Socket::Connected);
   _socket.SetSocket(socket);
   _socket.SetLocalAddress(LocalAddress);
   _socket.SetRemoteAddress(address);
}

long StreamSocket::GetAvailable()
{
    ulong count = 0;
    Socket::xxassert(*this, State == Socket::Connected);
    Socket::xxassert(*this, SocketModule::IoctlSocket(Socket_, FIONREAD, &count) == 0);
    return count;
}

void StreamSocket::Discard(int _timeout, bool _isline)
{
    Socket::xxassert(*this, State == Socket::Connected);
    //
    long count = GetAvailable();

    if(count > 0)
    {
        //
        const ushort _buffer_size_ = 256;
        STACK_BUFFER(_buffer_size_, byte)
        //
        Time s_time;

        while(count > 0)
        {
            if(_isline)
            {
                count -= ReceiveLine(buffer, _buffer_size_, _timeout);
            }
            else
            {
                count -= Receive(buffer, _buffer_size_, _timeout);
            }

            if(_timeout > 0)
            {
               _timeout -= Time(Time::GetCurrentTime()-s_time).GetSeconds();

                if(_timeout <= 0)
                {
                    break;
                }
            }
        }
    }
}

void StreamSocket::DisableNagleAlgorithm(bool _disable)
{
    int off = _disable ? 1 : 0;
    Socket::xxassert(*this, SocketModule::SetSocketOption(Socket_, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&off), sizeof(int)) == 0);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

/*
        fd_set rdset;
        fd_set wrset;
        fd_set exset;

        FD_ZERO(&rdset);
        FD_ZERO(&wrset);
        FD_ZERO(&exset);

        FD_SET(Socket_, &rdset);
        FD_SET(Socket_, &wrset);
        FD_SET(Socket_, &exset);

        timeval timeout;
        timeout.tv_sec  = _timeout;
        timeout.tv_usec = 0;

        rc = SocketModule::Select(0, &rdset, &wrset, &exset, &timeout);

        if(rc == 0)
        {
            Socket::xxassert(*this, 0, XSocket::Timeout);
        }
        else if(rc == SOCKET_ERROR)
        {
            Socket::xxassert(*this, 0, X::Failure);
        }
*/
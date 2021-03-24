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

#ifndef __PALM_STREAM_SOCKET_INC__
#   include <PalmStreamSocket.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmStreamSocket
// ----- ----------------
PalmStreamSocket::PalmStreamSocket()
{
}

PalmStreamSocket::PalmStreamSocket(const PalmIPv4& _remote_address, const PalmIPv4& _local_address)
                : PalmSocket(_remote_address, _local_address)
{
}

PalmStreamSocket::~PalmStreamSocket()
{
    Disconnect();
}

void PalmStreamSocket::Connect(bool _bind, uint16 _timeout, int16 _proto)
{
    palmxassert(State != PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    Socket = PalmSocketModule::CreateSocket(netSocketAddrINET, netSocketTypeStream, _proto);
    palmxassert(Socket != INVALID_SOCKET, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);

    uint16 flag = 1;
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelSocket, netSocketOptSockReuseAddr, &flag, sizeof(flag)) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);

    // for SOCKS bind could be ignored
    if(_bind)
    {
        palmxassert(PalmSocketModule::Bind(Socket, LocalAddress, LocalAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
    }

    palmxassert(PalmSocketModule::Connect(Socket, RemoteAddress, RemoteAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);

    int16 size = LocalAddress.GetSize();
    palmxassert(PalmSocketModule::GetSocketName(Socket, LocalAddress, size, _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
    //
    State = PalmSocket::eConnected;
}

void PalmStreamSocket::Disconnect(int16 _dir, uint16 _timeout)
{
    if(State == PalmSocket::eConnected)
    {
        palmxassert(PalmSocketModule::Shutdown(Socket, _dir, _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
        Discard(0, false);
        palmxassert(PalmSocketModule::CloseSocket(Socket, _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
        //
        State  = PalmSocket::eDisconnected;
        Socket = INVALID_SOCKET;
    }
}

int16 PalmStreamSocket::Send(const byte* _data, uint16 _count, uint16 _timeout, uint16 _flags)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(_data != null && _count > 0, Error::eInvalidArg, PalmStreamSocket::XPalmStreamSocket);
    return PalmSocketModule::Send(Socket, const_cast<byte*>(_data), _count, _flags, null, _timeout);
}

int16 PalmStreamSocket::Receive(byte* _buffer, uint16 _count, uint16 _timeout, uint16 _flags)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(_buffer != null && _count > 0, Error::eInvalidArg, PalmStreamSocket::XPalmStreamSocket);
    return PalmSocketModule::Receive(Socket, _buffer, _count, _flags, null, _timeout);
}

int16 PalmStreamSocket::ReceiveCount(byte* _buffer, uint16 _count, uint16 _timeout, uint16 _flags)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(_buffer != null && _count > 0, Error::eInvalidArg, PalmStreamSocket::XPalmStreamSocket);
    //
    uint16 count;

    byte* p_buff = _buffer;

    uint32 s_time = ::TimGetSeconds();

    while(_count > 0)
    {
        if((count = static_cast<uint16>(PalmSocketModule::Receive(Socket, _buffer, _count, _flags, null, _timeout))) == 0)
        {
            break;
        }

        p_buff += count;
       _count  -= count;

        if(_timeout > 0)
        {
           _timeout -= static_cast<uint16>(::TimGetSeconds()-s_time);

            if(static_cast<int32>(_timeout) <= 0)
            {
                break;
            }
        }
    }
    return static_cast<int16>(p_buff-_buffer);
}

int16 PalmStreamSocket::ReceiveLine(byte* _buffer, uint16 _count, uint16 _timeout)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(_buffer != null && _count > 0, Error::eInvalidArg, PalmStreamSocket::XPalmStreamSocket);

    /////////////////////////////////////////////////////////////////////////
    #define CHECKTIMEOUT()                                                  \
        if(_timeout > 0)                                                    \
        {                                                                   \
           _timeout -= static_cast<uint16>(::TimGetSeconds()-s_time);       \
                                                                            \
            if(static_cast<int32>(_timeout) <= 0)                           \
            {                                                               \
                return static_cast<int16>(p_buff-_buffer);                  \
            }                                                               \
        }                                                                   \
    /////////////////////////////////////////////////////////////////////////

    uint16 count;
    uint16 received = 0;

    byte* p_buff = _buffer;

    --_count;

    uint32 s_time = ::TimGetSeconds();

    while(_count > 0)
    {
        if((count = static_cast<uint16>(PalmSocketModule::Receive(Socket, p_buff, _count, netIOFlagPeek, null, _timeout))) == 0)
        {
            return 0;
        }

        if(_buffer[count-1] == Char::CR || _buffer[count-1] == Char::LF)
        {
            count = static_cast<uint16>(PalmSocketModule::Receive(Socket, p_buff, 1, 0, null, _timeout));
            p_buff[1] = 0;
            return static_cast<int16>(received+1);
        }

        for(uint16 i = 0; i < count; ++i)
        {
            if(p_buff[i] == Char::CR && p_buff[i+1] == Char::LF)
            {
                CHECKTIMEOUT()
                count = static_cast<uint16>(PalmSocketModule::Receive(Socket, p_buff, static_cast<uint16>(i+2), 0, null, _timeout));
                p_buff[i+2] = 0;
                return static_cast<int16>(received+i+2);
            }
        }   

        CHECKTIMEOUT()
        count = static_cast<uint16>(PalmSocketModule::Receive(Socket, p_buff, count, 0, null, _timeout));
        received += count;
        p_buff[count]=0;
        p_buff = &p_buff[count];
       _count -= count;
    }
    return static_cast<int16>(received);

    /////////////////////////////////////////////////////////////////////////
    #undef CHECKTIMEOUT
    /////////////////////////////////////////////////////////////////////////
}

void PalmStreamSocket::Listen(uint16 _count, uint16 _timeout)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    Socket = PalmSocketModule::CreateSocket(netSocketAddrINET, netSocketTypeStream);
    palmxassert(Socket != INVALID_SOCKET, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(PalmSocketModule::Bind(Socket, LocalAddress, LocalAddress.GetSize(), _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(PalmSocketModule::Listen(Socket, _count, _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
}

void PalmStreamSocket::Accept(PalmStreamSocket& _socket, uint16 _timeout)
{
    PalmIPv4 address;

    int16 size = address.GetSize();

    socket_t socket;

    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    socket = PalmSocketModule::Accept(Socket, address, size, _timeout);
    palmxassert(socket != INVALID_SOCKET, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(PalmSocketModule::GetSocketName(Socket, LocalAddress, size, _timeout) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
    //
   _socket.SetState(PalmSocket::eConnected);
   _socket.SetSocket(socket);
   _socket.SetLocalAddress(LocalAddress);
   _socket.SetRemoteAddress(address);
}

uint32 PalmStreamSocket::GetAvailable(uint16 _timeout)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    //
    uint32 count = 0;
    byte buffer[256];

    while((count += PalmSocketModule::Receive(Socket, buffer, sizeof(buffer), netIOFlagPeek, null, _timeout)) != 0)
    {
    }
    return count;
}

void PalmStreamSocket::Discard(uint16 _timeout, bool _isline)
{
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    //
    uint32 count = GetAvailable();

    if(count > 0)
    {
        //
        byte buffer[256];
        //
        uint32 s_time = ::TimGetSeconds();

        while(count > 0)
        {
            if(_isline)
            {
                count -= ReceiveLine(buffer, sizeof(buffer), _timeout);
            }
            else
            {
                count -= Receive(buffer, sizeof(buffer), _timeout);
            }

            if(_timeout > 0)
            {
               _timeout -= static_cast<uint16>(::TimGetSeconds()-s_time);

                if(static_cast<int32>(_timeout) <= 0)
                {
                    break;
                }
            }
        }
    }
}

void PalmStreamSocket::DisableNagleAlgorithm(bool _disable)
{
    // apache
    // the nagle algorithm says that we should delay sending partial
    // packets in hopes of getting more data. we don't want to do
    // this; we are not telnet. there are bad interactions between
    // persistent connections and nagle's algorithm that have very severe performance penalties.
    // failing to disable Nagle is not much of a problem with simple HTTP.
    uint16 off = static_cast<uint16>(_disable ? 1 : 0);
    palmxassert(State == PalmSocket::eConnected, XPalmSocket::eInvalidState, PalmStreamSocket::XPalmStreamSocket);
    palmxassert(PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelTCP, netSocketOptTCPNoDelay, &off, sizeof(off)) == errNone, Error::eOperationFailure, PalmStreamSocket::XPalmStreamSocket);
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmStreamSocket
// ----- -----------------
void PalmStreamSocket::XPalmStreamSocket::LoadErrorDescriptions()
{
    // base class
    XPalmSocket::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

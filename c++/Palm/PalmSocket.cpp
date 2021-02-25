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
#   include <PalmSocket.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmSocket
// ----- ----------
const PalmIPv4 PalmSocket::DummyIP;
//
PalmSocket::PalmSocket()
          : State(PalmSocket::eUnknown),
            Socket(INVALID_SOCKET)
{
}

PalmSocket::PalmSocket(const PalmIPv4& _remote_address, const PalmIPv4& _local_address)
          : State(PalmSocket::eUnknown),
            LocalAddress(_local_address),
            RemoteAddress(_remote_address),
            Socket(INVALID_SOCKET)
{
}

PalmSocket::~PalmSocket()
{
	// should be disconnected in a derive class
    Socket = INVALID_SOCKET;
}

void PalmSocket::GetOptions(uint16 _level, uint16 _op_name, byte* _op_value, uint16& _op_size, uint16 _timeout) const
{
    palmxassert(Socket != 0, Error::eUninitialized, PalmSocket::XPalmSocket);
    palmxassert(_op_value != null && _op_size != null, Error::eInvalidArg, PalmSocket::XPalmSocket);
    palmxassert(PalmSocketModule::GetSocketOption(Socket, _level, _op_name, _op_value, _op_size, _timeout) == errNone, Error::eInvalidArg, PalmSocket::XPalmSocket);
}

void PalmSocket::SetOptions(uint16 _level, uint16 _op_name, byte* _op_value, uint16 _op_size, uint16 _timeout)
{
    palmxassert(Socket != 0, Error::eUninitialized, PalmSocket::XPalmSocket);
    palmxassert(_op_value != null,  Error::eInvalidArg, PalmSocket::XPalmSocket);
    palmxassert(PalmSocketModule::SetSocketOption(Socket, _level, _op_name, reinterpret_cast<char*>(_op_value), _op_size, _timeout) == errNone, Error::eInvalidArg, PalmSocket::XPalmSocket);
}

int16 PalmSocket::SetTimeout(uint16 _timeout, PalmSocket::EMode _mode)
{
    if(_timeout == 0)
    {
        return 1; // ok
    }

    uint16 width;

    fd_set_t read_fd;
    fd_set_t write_fd;
    fd_set_t except_fd;

    netFDZero(&read_fd);
    netFDZero(&write_fd);
    netFDZero(&except_fd);

    switch(_mode)
    {
        case PalmSocket::eReadFD: // read
            netFDSet(Socket, &read_fd);
            netFDSet(sysFileDescStdIn, &read_fd);
            width = static_cast<uint16>(Max(static_cast<socket_t>(sysFileDescStdIn), Socket));
            return PalmSocketModule::Select(width, &read_fd, &write_fd, &except_fd, _timeout);
        case PalmSocket::eWriteFD: // write
            netFDSet(Socket, &write_fd);
            netFDSet(sysFileDescStdIn, &write_fd);
            width = static_cast<uint16>(Max(static_cast<socket_t>(sysFileDescStdIn), Socket));
            return PalmSocketModule::Select(width, &read_fd, &write_fd, &except_fd, _timeout);
        case PalmSocket::eExceptFD: // exception
            netFDSet(Socket, &except_fd);
            netFDSet(sysFileDescStdIn, &except_fd);
            width = static_cast<uint16>(Max(static_cast<socket_t>(sysFileDescStdIn), Socket));
            return PalmSocketModule::Select(width, &read_fd, &write_fd, &except_fd, _timeout);
    }
	return 0;
}

uint16 PalmSocket::SetBufferSize(uint16 _new_size, uint16 _op_name)
{
    palmxassert(Socket != 0, Error::eUninitialized, PalmSocket::XPalmSocket);
    //
    const uint16 _mtu_size_ = 1460;
    //
    uint16 size;
    uint16 trysize;
    uint16 finsize = 0;

    size = sizeof(size);
    GetOptions(netSocketOptLevelSocket, _op_name, reinterpret_cast<byte*>(&finsize), size);

    if(_new_size <= finsize)
    {
        _new_size = static_cast<uint16>(finsize << 1);
    }

    for(trysize = _new_size; trysize > _mtu_size_; trysize >>= 1)
    {
        int16 err = PalmSocketModule::SetSocketOption(Socket, netSocketOptLevelSocket, _op_name, &trysize, sizeof(trysize));

        if(err != errNone)
        {
            break;
        }
        else
        {
            size = sizeof(size);
            GetOptions(netSocketOptLevelSocket, _op_name, reinterpret_cast<byte*>(&finsize), size);
            break;
        }
    }
    return finsize;
}
////////////////////////////////////////////////////////////////////////////////////////
// class XPalmSocket
// ----- -----------
void PalmSocket::XPalmSocket::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();

    GetDescriptions()[eInvalidState] = "The socket is in an invalid state";
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

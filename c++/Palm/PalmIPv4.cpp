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

#ifndef __PALM_IPV4_ADDRESS_INC__
#   include <PalmIPv4.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmIPv4
// ----- --------
PalmIPv4::PalmIPv4()
{
    PalmOS::MemSet(&InetAddress, sizeof(InetAddress));
    InetAddress.family = netSocketAddrINET;
}

PalmIPv4::PalmIPv4(const PalmIPv4& _other)
{
    PalmOS::MemCopy(&InetAddress, &_other.InetAddress, sizeof(InetAddress));
}

PalmIPv4::PalmIPv4(const sockaddr_in_t& _address)
{
    PalmOS::MemSet(&InetAddress, sizeof(InetAddress));
    PalmOS::MemCopy(&InetAddress, &_address, sizeof(InetAddress));
}

PalmIPv4::PalmIPv4(const sockaddr_t& _address)
{
    PalmOS::MemSet(&SocketAddress, sizeof(SocketAddress));
    PalmOS::MemCopy(&SocketAddress, &_address, sizeof(SocketAddress));
}

PalmIPv4::PalmIPv4(uint32 _ip, uint16 _port, int16 _family)
{
    // address can be INADDR_ANY, INADDR_LOOPBACK, INADDR_BROADCAST, INADDR_NONE
    PalmOS::MemSet(&InetAddress, sizeof(InetAddress));
    //
    InetAddress.addr   = HtoNL(_ip);
    InetAddress.port   = HtoNS(_port);
    InetAddress.family = _family;
}

PalmIPv4::PalmIPv4(const URL& _url)
{
    AutoPtrArray<char> host = PalmText::StrClone(_url.GetHost().c_str());
    uint16 port = _url.GetPort();
    //
    SetIPv4Address(host, port);
}

PalmIPv4::PalmIPv4(const char* _ip, uint16 _port, int16 _family)
{
    // _ip should be in dotted format '128.23.65.127'
    PalmOS::MemSet(&InetAddress, sizeof(InetAddress));
    //
    InetAddress.addr   = PalmSocketModule::InetAddress(const_cast<char*>(_ip));
    InetAddress.port   = HtoNS(_port);
    InetAddress.family = _family;
}

PalmIPv4::PalmIPv4(const byte* _data, int16 _family)
{
    PalmOS::MemSet(&SocketAddress, sizeof(SocketAddress));
    //
    SocketAddress.family = _family;
    PalmOS::MemCopy(&SocketAddress.data, _data, 14); // 14 from ! ...
}

PalmIPv4::~PalmIPv4()
{
}

PalmIPv4& PalmIPv4::operator = (const PalmIPv4& _other)
{
    if(this != &_other)
    {
        PalmOS::MemCopy(&InetAddress, &_other.InetAddress, sizeof(InetAddress));
    }
    return *this;
}

PalmIPv4& PalmIPv4::operator = (const sockaddr_in_t& _address)
{
    PalmOS::MemCopy(&InetAddress, &_address, sizeof(InetAddress));
    return *this;
}

void PalmIPv4::SetIPv4Address(const char* _host_name, uint16 _port)
{
    if(_host_name == null)
    {
        return;
    }

    if((InetAddress.addr = PalmSocketModule::InetAddress(const_cast<char*>(_host_name))) == INADDR_NONE && PalmText::StrCompare(_host_name, "255.255.255") != 0)
    {
        // NOT dotted format
        hostent_buf_t info;
        PalmOS::MemSet(&info, sizeof(info));
        hostent_t* e = PalmSocketModule::GetHostByName(info, const_cast<char*>(_host_name));

        if(e != null)
        {
            PalmOS::MemCopy(&InetAddress.addr, &e->addrListP[0], e->addrLen);
        }
        else
        {
            InetAddress.addr = INADDR_ANY;
        }
    }

    InetAddress.family = netSocketAddrINET;
    InetAddress.port   = HtoNS(_port);
}

void PalmIPv4::SetIPv4Address(const char* _address)
{
    if(_address == null)
    {
        return;
    }

    // _address is as follows: "ip:port" (e.g. "uilab.com:80" or "128.167.204.57:80")
    // if there is NO ':' in the _address it is first assumed to be a port number,
    // and then try as a IP address
    const char* _entries_ = "1234567890";
    //
    char* p = PalmText::StrStr(_address, ":");
    uint16 port;

    if(p == null && (port = static_cast<uint16>(HtoNS(PalmText::StrAToI(_address)))) != 0)
    {
        InetAddress.addr = INADDR_ANY;
        InetAddress.port = port;
    }
    else 
    {
        if((InetAddress.addr = PalmSocketModule::InetAddress(const_cast<char*>(_address))) == INADDR_NONE && PalmText::StrCompare(_address, "255.255.255") != 0)
        {
            // NOT dotted schema
            hostent_buf_t info;
            PalmOS::MemSet(&info, sizeof(info));
            hostent_t* e = PalmSocketModule::GetHostByName(info, const_cast<char*>(_address));

            if(e != null)
            {
                PalmOS::MemCopy(&InetAddress.addr, &e->addrListP[0], e->addrLen);
            }
            else
            {
                InetAddress.addr = INADDR_ANY;
            }
        }

        if(p != null)
        {
            InetAddress.port = static_cast<uint16>(HtoNS(PalmText::StrAToI(++p)));
        }
    }

    InetAddress.family = netSocketAddrINET;
}

void PalmIPv4::SetIPv4Address(const char* _host_name, const char* _port_name, const char* _protocol)
{
    if(_host_name == null || _port_name == null || _protocol == null)
    {
        return;
    }

    // phase I (obtain port number)
    servent_buf_t serv;
    PalmOS::MemSet(&serv, sizeof(serv));
    servent_t* e = PalmSocketModule::GetServiceByName(serv, _port_name, _protocol);

    if(e != null)
    {
        InetAddress.port = e->port;
    }

    // phase II (obtain IP)
    if((InetAddress.addr = PalmSocketModule::InetAddress(const_cast<char*>(_host_name))) == INADDR_NONE && PalmText::StrCompare(_host_name, "255.255.255") != 0)
    {
        // NOT dotted schema
        hostent_buf_t info;
        PalmOS::MemSet(&info, sizeof(info));
        hostent_t* e = PalmSocketModule::GetHostByName(info, const_cast<char*>(_host_name));

        if(e != null)
        {
            PalmOS::MemCopy(&InetAddress.addr, &e->addrListP[0], e->addrLen);
        }
        else
        {
            InetAddress.addr = INADDR_ANY;
        }
    }

    InetAddress.family = netSocketAddrINET;
}

void PalmIPv4::SetIPv4Address(uint32 _ip, const char* _port_name, const char* _protocol)
{
    servent_buf_t serv;
    PalmOS::MemSet(&serv, sizeof(serv));
    servent_t* e = PalmSocketModule::GetServiceByName(serv, _port_name, _protocol);

    if(e != null)
    {
        InetAddress.port = e->port;
    }

    InetAddress.family = netSocketAddrINET;
    InetAddress.addr   = HtoNL(_ip);
}

void PalmIPv4::GetHostName(char* _buffer, uint16 _count) const
{
    if(_buffer == null)
    {
        return;
    }

    if(InetAddress.addr != 0)
    {
        PalmSocketModule::GetHostName(_buffer, _count);
    }
}

void PalmIPv4::GetAddressAsString(char* _buffer, PalmIPv4::EFormat _format)
{
    if(_buffer == null)
    {
        return;
    }

    _buffer[0] = 0;

    if(_format == PalmIPv4::eIP_Port)
    {
        char term[16];
        PalmText::StrPrintf(term, "%ld", NtoHS(InetAddress.port));
        //
        PalmSocketModule::InetNtoA(GetIPv4Address(0), _buffer);
        PalmText::StrCat(_buffer, ":");
        PalmText::StrCat(_buffer, term);
    }
    else
    {
        hostent_buf_t info;
        PalmOS::MemSet(&info, sizeof(info));
        hostent_t* e = PalmSocketModule::GetHostByAddress(info, &SocketAddress, 4, netSocketAddrINET);

        if(e != null)
        {
            if(_format == PalmIPv4::eUnformat)
            {
                PalmText::StrCopy(_buffer, e->nameP);
            }
            else if(_format == PalmIPv4::eHost_Port)
            {
                char term[8];
                PalmText::StrPrintf(term, "%ld", InetAddress.port);
                //
                PalmText::StrCopy(_buffer, e->nameP);
                PalmText::StrCat(_buffer, ":");
                PalmText::StrCat(_buffer, term);
            }
        }
    }
}

ulong PalmIPv4::Hash() const
{
    return GetIPv4Address();
}

uint32 PalmIPv4::ConvertAddress(const char* _address)
{
    // _address should be in dotted format
    // returns in network-order
    if(_address == null)
    {
        return 0;
    }
    return PalmSocketModule::InetAddress(const_cast<char*>(_address));
}

void PalmIPv4::ConvertAddress(uint32 _address, char* _buffer, bool _encode)
{
    // returns in dotted format
    if(_buffer == null)
    {
        return;
    }
    //
    in_addr_t addr;

   _buffer[0] = 0;

    if(_encode)
    {
        addr = HtoNL(_address);
    }

    PalmSocketModule::InetNtoA(addr, _buffer);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__


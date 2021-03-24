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

#ifndef __IP_V4_ADDRESS_INC__
#   include <IPv4Address.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IPv4Address
// ----- -----------
IPv4Address::IPv4Address()
{
    InitMemory(&InetAddress, sizeof(InetAddress));
    InetAddress.sin_family = AF_INET;
}

IPv4Address::IPv4Address(const IPv4Address& _other)
{
    operator = (_other);
}

IPv4Address::IPv4Address(const sockaddr_in& _address)
{
    InitMemory(&InetAddress, sizeof(InetAddress));
    memcpy(&InetAddress, &_address, sizeof(InetAddress));
}

IPv4Address::IPv4Address(const sockaddr& _address)
{
    InitMemory(&SocketAddress, sizeof(SocketAddress));
    memcpy(&SocketAddress, &_address, sizeof(SocketAddress));
}

IPv4Address::IPv4Address(uint _ip, ushort _port, short _family)
{
    // address can be INADDR_ANY, INADDR_LOOPBACK, INADDR_BROADCAST, INADDR_NONE
    InitMemory(&InetAddress, sizeof(InetAddress));
    //
    InetAddress.sin_addr.S_un.S_addr = SocketModule::HtoNL(_ip);
    InetAddress.sin_port             = SocketModule::HtoNS(_port);
    InetAddress.sin_family           = _family;
}

IPv4Address::IPv4Address(const URL& _url)
{
    AutoPtrArray<tchar> host = StrClone(_url.GetHost());
    ushort port = _url.GetPort();
    //
    SetIPv4Address(host, port);
}

IPv4Address::IPv4Address(const tchar* _ip, ushort _port, short _family)
{
    // _ip should be in dotted format '128.23.65.127'
    InitMemory(&InetAddress, sizeof(InetAddress));
    //
#ifdef _UNICODE
    AutoPtrArray<char> p = W2A(_ip);
    InetAddress.sin_addr.S_un.S_addr = SocketModule::InetAddress(p);
#else
    InetAddress.sin_addr.S_un.S_addr = SocketModule::InetAddress(_ip);
#endif
    InetAddress.sin_port             = SocketModule::HtoNS(_port);
    InetAddress.sin_family           = _family;
}

IPv4Address::IPv4Address(const byte* _data, short _family)
{
    InitMemory(&SocketAddress, sizeof(SocketAddress));
    //
    SocketAddress.sa_family = _family;
    memcpy(&SocketAddress.sa_data, _data, 14); // 14 from Winsock ! ...
}

IPv4Address::~IPv4Address()
{
}

IPv4Address& IPv4Address::operator = (const IPv4Address& _other)
{
    if(this != &_other)
    {
        memcpy(&InetAddress, &_other.InetAddress, sizeof(InetAddress));
    }
    return *this;
}

IPv4Address& IPv4Address::operator = (const sockaddr_in& _address)
{
    memcpy(&InetAddress, &_address, sizeof(InetAddress));
    return *this;
}

void IPv4Address::SetIPv4Address(const tchar* _host_name, ushort _port)
{
    IPv4Address::xxassert(_host_name != null);
    //
    if((InetAddress.sin_addr.S_un.S_addr = SocketModule::InetAddress(_host_name)) == INADDR_NONE && _tcscmp(_host_name, _t("255.255.255")) != 0)
    {
        // NOT dotted format
        hostent* e = SocketModule::GetHostByName(_host_name);

#ifdef _DEBUG
        int err = SocketModule::GetLastError();
#endif
        if(e != null)
        {
            memcpy(&InetAddress.sin_addr, e->h_addr, e->h_length);
        }
        else
        {
            InetAddress.sin_addr.S_un.S_addr = INADDR_ANY;
        }
    }

    InetAddress.sin_family = AF_INET;
    InetAddress.sin_port   = SocketModule::HtoNS(_port);
}

void IPv4Address::SetIPv4Address(const tchar* _address)
{
    IPv4Address::xxassert(_address != null);
    // _address is as follows: "ip:port" (e.g. "uilab.com:80" or "128.167.204.57:80")
    // if there is NO ':' in the _address it is first assumed to be a port number,
    // and then try as a IP address
    const tchar* _entries_ = _t("1234567890");
    //
    tchar* p = _tcschr(_address, _t(':'));
    ushort port;

    if(p == null && (port = SocketModule::HtoNS(atoi(_address))) != 0)
    {
        IPv4Address::xxassert(_tcsspn(_address, _entries_) == _tcslen(_address));
        //
        InetAddress.sin_addr.S_un.S_addr = INADDR_ANY;
        InetAddress.sin_port             = port;
    }
    else 
    {
        if((InetAddress.sin_addr.S_un.S_addr = SocketModule::InetAddress(_address)) == INADDR_NONE && _tcscmp(_address, _t("255.255.255")) != 0)
        {
            // NOT dotted schema
            hostent* e = SocketModule::GetHostByName(_address);

#ifdef _DEBUG
            int err = SocketModule::GetLastError();
#endif
            if(e != null)
            {
                memcpy(&InetAddress.sin_addr, e->h_addr, e->h_length);
            }
            else
            {
                InetAddress.sin_addr.S_un.S_addr = INADDR_ANY;
            }
        }

        if(p != null)
        {
            InetAddress.sin_port = SocketModule::HtoNS(atoi(++p));
        }
    }
    
    InetAddress.sin_family = AF_INET;
}

void IPv4Address::SetIPv4Address(const tchar* _host_name, const tchar* _port_name, const tchar* _protocol)
{
    IPv4Address::xxassert(_port_name != null && _host_name != null && _protocol != null);

    // phase I (obtain port number)
    servent* e = SocketModule::GetServiceByName(_port_name, _protocol);

    if(e != null)
    {
        InetAddress.sin_port = e->s_port;
    }

    // phase II (obtain IP)
    if((InetAddress.sin_addr.S_un.S_addr = SocketModule::InetAddress(_host_name)) == INADDR_NONE && _tcscmp(_host_name, _t("255.255.255")) != 0)
    {
        // NOT dotted schema
        hostent* e = SocketModule::GetHostByName(_host_name);

#ifdef _DEBUG
        int err = SocketModule::GetLastError();
#endif
        if(e != null)
        {
            memcpy(&InetAddress.sin_addr, e->h_addr, e->h_length);
        }
        else
        {
            InetAddress.sin_addr.S_un.S_addr = INADDR_ANY;
        }
    }

    InetAddress.sin_family = AF_INET;
}

void IPv4Address::SetIPv4Address(uint _ip, const tchar* _port_name, const tchar* _protocol)
{
    IPv4Address::xxassert(_port_name != null && _protocol != null);
    //
    servent* e = SocketModule::GetServiceByName(_port_name, _protocol);

    if(e != null)
    {
        InetAddress.sin_port = e->s_port;
    }

    InetAddress.sin_family = AF_INET;
    InetAddress.sin_addr.S_un.S_addr = SocketModule::HtoNL(_ip);
}

void IPv4Address::GetHostName(tchar* _buffer, int _count) const
{
    IPv4Address::xxassert(_buffer != null);
    //
    if(InetAddress.sin_addr.S_un.S_addr != 0)
    {
        SocketModule::GetHostName(_buffer, _count);
    }
}

void IPv4Address::GetAddressAsString(tchar* _buffer, IPv4Address::EFormat _format) const
{
    IPv4Address::xxassert(_buffer != null, X::InvalidArg);
    //
    _buffer[0] = 0;

    if(_format == IPv4Address::IP_Port)
    {
        tchar term[8];
        _snprintf(term, sizeof(term), _t("%ld"), SocketModule::NtoHS(InetAddress.sin_port));
        //
        _tcscpy(_buffer, SocketModule::InetNtoA(GetIPv4Address(0)));
        _tcscat(_buffer, _t(":"));
        _tcscat(_buffer, term);
    }
    else
    {
        hostent* e = SocketModule::GetHostByAddress((char*)(&InetAddress.sin_addr.S_un.S_addr), 4, AF_INET);

        if(e != null)
        {
            if(_format == IPv4Address::Unformat)
            {
                _tcscpy(_buffer, e->h_name);
            }
            else if(_format == IPv4Address::Host_Port)
            {
                tchar term[8];
                _snprintf(term, sizeof(term), _t("%ld"), InetAddress.sin_port);
                //
                _tcscpy(_buffer, e->h_name);
                _tcscat(_buffer, _t(":"));
                _tcscat(_buffer, term);
            }
        }
    }
}

ulong IPv4Address::Hash() const
{
    return GetIPv4Address();
}

uint IPv4Address::ConvertAddress(const tchar* _address)
{
    // _address should be in dotted format
    // returns in network-order
    IPv4Address::xxassert(_address != null, X::InvalidArg);
#ifdef _UNICODE
    AutoPtrArray<char> p = W2A(_address);
    return SocketModule::InetAddress(p);
#else
    return SocketModule::InetAddress(_address);
#endif
}

void IPv4Address::ConvertAddress(uint _address, tchar* _buffer, bool _encode)
{
    // returns in dotted format
    IPv4Address::xxassert(_buffer != null, X::InvalidArg);
    //
    in_addr tmp;
    char* p;

   _buffer[0] = 0;

    if(_encode)
    {
        tmp.s_addr = SocketModule::HtoNL(_address);
    }

    p = SocketModule::InetNtoA(tmp);

    if(p != null)
    {
#ifdef _UNICODE
        AutoPtrArray<wchar> pw = A2W(p);
       _tcscpy(_buffer, pw);
#else
       _tcscpy(_buffer, p);
#endif
    }
}

void IPv4Address::xxassert(int _expr, uint _error)
{
    if(_expr == 0)
    {
        throw IPv4Address::XIPv4Address(_error);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// class XIPv4Address
// ----- ----------
IPv4Address::XIPv4Address::XIPv4Address(uint _error) : X(_error)
{
    SysError = SocketModule::GetLastError();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

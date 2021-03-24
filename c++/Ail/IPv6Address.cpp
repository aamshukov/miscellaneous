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

#ifndef __IP_V6_ADDRESS_INC__
#   include <IPv6Address.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IPv6Address
// ----- -----------
IPv6Address::IPv6Address()
{
    InitMemory(&InetAddress, sizeof(InetAddress));
    InetAddress.sin6_family = AF_INET6;
}

IPv6Address::IPv6Address(const IPv6Address& _other)
{
    operator = (_other);
}

IPv6Address::IPv6Address(const sockaddr_in6& _address)
{
    SetInetAddress(_address);
}

IPv6Address::IPv6Address(const tchar* _ip, ushort _port, short _family)
{
    SetIPv6Address(_ip, _port, _family);
}

IPv6Address::~IPv6Address()
{
}

void IPv6Address::xxassert(int _expr, uint _error)
{
    if(_expr == 0)
    {
        throw IPv6Address::XIPv6Address(_error);
    }
}

IPv6Address& IPv6Address::operator = (const IPv6Address& _other)
{
    if(this != &_other)
    {
        memcpy(&InetAddress, &_other.InetAddress, sizeof(InetAddress));
    }
    return *this;
}

IPv6Address& IPv6Address::operator = (const sockaddr_in6& _address)
{
    SetInetAddress(_address);
    return *this;
}

void IPv6Address::SetIPv6Address(const tchar* _ip, ushort _port, short _family)
{
}

void IPv6Address::GetHostName(tchar* _buffer, int _count) const
{
    IPv6Address::xxassert(_buffer != null);
}

ulong IPv6Address::Hash() const
{
    return ElfHashBytes((byte*)&InetAddress.sin6_addr, sizeof(InetAddress.sin6_addr));
}

void IPv6Address::GetAddressAsString(tchar* _buffer, IPv6Address::EFormat _format) const
{
    IPv6Address::xxassert(_buffer != null, X::InvalidArg);
    //
   _buffer[0] = 0;
};
////////////////////////////////////////////////////////////////////////////////////////
// class XIPv6Address
// ----- ----------
IPv6Address::XIPv6Address::XIPv6Address(uint _error) : X(_error)
{
    SysError = SocketModule::GetLastError();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

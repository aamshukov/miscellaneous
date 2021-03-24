////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IP_V6_ADDRESS_INL__
#define __IP_V6_ADDRESS_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IPv6Address
// ----- -----------
__INLINE__ IPv6Address::operator sockaddr_in6* ()
{
    return &InetAddress;
}

__INLINE__ IPv6Address::operator const sockaddr_in6* () const
{
    return static_cast<const sockaddr_in6*>(&InetAddress);
}

__INLINE__ IPv6Address::operator sockaddr_in6 ()
{
    return InetAddress;
}

__INLINE__ IPv6Address::operator const sockaddr_in6 () const
{
    return static_cast<const sockaddr_in6>(InetAddress);
}

__INLINE__ bool IPv6Address::operator == (const IPv6Address& _other) const
{
    return memcmp(&InetAddress, &_other, sizeof(InetAddress)) == 0;
}

__INLINE__ bool IPv6Address::operator != (const IPv6Address& _other) const
{
    return memcmp(&InetAddress, &_other, sizeof(InetAddress)) != 0;
}

__INLINE__ bool IPv6Address::IsValid() const
{
    return InetAddress.sin6_family != 0;
}

__INLINE__ int IPv6Address::GetSize() const
{
    return sizeof(InetAddress);
}

__INLINE__ const sockaddr_in6& IPv6Address::GetInetAddress() const
{
    return static_cast<const sockaddr_in6&>(InetAddress);
}

__INLINE__ void IPv6Address::SetInetAddress(const sockaddr_in6& _address)
{
    memcpy(&InetAddress, &_address, sizeof(InetAddress));
}

__INLINE__ ushort IPv6Address::GetPort() const
{
    return InetAddress.sin6_port;
}

__INLINE__ void IPv6Address::SetPort(ushort _port)
{
    InetAddress.sin6_port = SocketModule::HtoNS(_port);
}

__INLINE__ ulong IPv6Address::GetFlow() const
{
    return InetAddress.sin6_flowinfo;
}

__INLINE__ void IPv6Address::SetFlow(ulong _flow)
{
    InetAddress.sin6_flowinfo = _flow;
}

__INLINE__ ushort IPv6Address::GetFamily() const
{
    return InetAddress.sin6_family;
}

__INLINE__ void IPv6Address::SetFamily(ushort _family)
{
    InetAddress.sin6_family = _family;
}

__INLINE__ uint IPv6Address::GetIPv4Address() const
{
    return static_cast<uint>(InetAddress.sin6_addr.s6_addr[12]);
}

__INLINE__ const in_addr6& IPv6Address::GetIPv6Address() const
{
    return static_cast<const in_addr6&>(InetAddress.sin6_addr);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IP_V6_ADDRESS_INL__

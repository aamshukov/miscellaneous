////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IP_V4_ADDRESS_INL__
#define __IP_V4_ADDRESS_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IPv4Address
// ----- -----------
__INLINE__ bool IPv4Address::IsValid() const
{
    return InetAddress.sin_family != 0;
}

__INLINE__ int IPv4Address::GetSize() const
{
    return sizeof(InetAddress);
}

__INLINE__ IPv4Address::operator sockaddr_in* ()
{
    return &InetAddress;
}

__INLINE__ IPv4Address::operator const sockaddr_in* () const
{
    return static_cast<const sockaddr_in*>(&InetAddress);
}

__INLINE__ IPv4Address::operator sockaddr_in ()
{
    return InetAddress;
}

__INLINE__ IPv4Address::operator const sockaddr_in () const
{
    return static_cast<const sockaddr_in>(InetAddress);
}

__INLINE__ IPv4Address::operator sockaddr* ()
{
    return &SocketAddress;
}

__INLINE__ IPv4Address::operator const sockaddr* () const
{
    return static_cast<const sockaddr*>(&SocketAddress);
}

__INLINE__ IPv4Address::operator sockaddr ()
{
    return SocketAddress;
}

__INLINE__ IPv4Address::operator const sockaddr () const
{
    return static_cast<const sockaddr>(SocketAddress);
}

__INLINE__ bool IPv4Address::operator == (const IPv4Address& _other) const
{
    return memcmp(&InetAddress, &_other, sizeof(InetAddress)) == 0;
}

__INLINE__ bool IPv4Address::operator != (const IPv4Address& _other) const
{
    return memcmp(&InetAddress, &_other, sizeof(InetAddress)) != 0;
}

__INLINE__ const sockaddr_in& IPv4Address::GetInetAddress() const
{
    return static_cast<const sockaddr_in&>(InetAddress);
}

__INLINE__ void IPv4Address::SetInetAddress(const sockaddr_in& _address)
{
    memcpy(&InetAddress, &_address, sizeof(InetAddress));
}

__INLINE__ const sockaddr& IPv4Address::GetSocketAddress() const
{
    return static_cast<const sockaddr&>(SocketAddress);
}

__INLINE__ void IPv4Address::SetSocketAddress(const sockaddr& _address)
{
    memcpy(&SocketAddress, &_address, sizeof(SocketAddress));
}

__INLINE__ ushort IPv4Address::GetFamily() const
{
    return InetAddress.sin_family;
}

__INLINE__ void IPv4Address::SetFamily(ushort _family)
{
    InetAddress.sin_family = _family;
}

__INLINE__ ushort IPv4Address::GetPort() const
{
    return InetAddress.sin_port;
}

__INLINE__ void IPv4Address::SetPort(ushort _port)
{
    InetAddress.sin_port = SocketModule::HtoNS(_port);
}

__INLINE__ uint IPv4Address::GetIPv4Address() const
{
    return static_cast<uint>(InetAddress.sin_addr.s_addr);
}

__INLINE__ const in_addr& IPv4Address::GetIPv4Address(int) const
{
    return static_cast<const in_addr&>(InetAddress.sin_addr);
}

__INLINE__ void IPv4Address::SetIPv4Address(uint _ip)
{
    InetAddress.sin_addr.S_un.S_addr = SocketModule::HtoNL(_ip);
}

__INLINE__ void IPv4Address::SetIPv4Address(const in_addr& _address)
{
    InetAddress.sin_addr = _address;
}

__INLINE__ void IPv4Address::SetIPv4Address(uint _ip, ushort _port)
{
    InetAddress.sin_addr.S_un.S_addr = SocketModule::HtoNL(_ip);
    InetAddress.sin_port             = SocketModule::HtoNS(_port);
}

__INLINE__ uint IPv4Address::GetNode(uint _subnet_mask) const
{
    if(_subnet_mask == 0)
    {
        IPv4Address::EClass inet_class = GetClass();

        if(inet_class == IPv4Address::ClassA)
        {
            _subnet_mask = IN_CLASSA_NET;
        }
        else if(inet_class == IPv4Address::ClassB)
        {
            _subnet_mask = IN_CLASSB_NET;
        }
        else if(inet_class == IPv4Address::ClassC)
        {
            _subnet_mask = IN_CLASSC_NET;
        }
        else if(inet_class == IPv4Address::ClassD)
        {
            _subnet_mask = IN_CLASSD_NET;
        }
        else
        {
            return 0;
        }
    }
    return InetAddress.sin_addr.s_addr & ~_subnet_mask;
}

__INLINE__ IPv4Address::EClass IPv4Address::GetClass() const
{
    if(IN_CLASSA(InetAddress.sin_addr.s_addr))
    {
        return IPv4Address::ClassA;
    }
    else if(IN_CLASSB(InetAddress.sin_addr.s_addr))
    {
        return IPv4Address::ClassB;
    }
    else if(IN_CLASSC(InetAddress.sin_addr.s_addr))
    {
        return IPv4Address::ClassC;
    }
    return IPv4Address::ClassUnknown;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IP_V4_ADDRESS_INL__

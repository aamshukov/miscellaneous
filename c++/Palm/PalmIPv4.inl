////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_IPV4_ADDRESS_INL__
#define __PALM_IPV4_ADDRESS_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmIPv4
// ----- --------
__INLINE__ bool PalmIPv4::IsValid() const
{
    return InetAddress.addr != 0;
}

__INLINE__ int16 PalmIPv4::GetSize() const
{
    return sizeof(InetAddress);
}

__INLINE__ PalmIPv4::operator sockaddr_in_t* ()
{
    return &InetAddress;
}

__INLINE__ PalmIPv4::operator const sockaddr_in_t* () const
{
    return static_cast<const sockaddr_in_t*>(&InetAddress);
}

__INLINE__ PalmIPv4::operator sockaddr_in_t ()
{
    return InetAddress;
}

__INLINE__ PalmIPv4::operator const sockaddr_in_t () const
{
    return static_cast<const sockaddr_in_t>(InetAddress);
}

__INLINE__ PalmIPv4::operator sockaddr_t* ()
{
    return &SocketAddress;
}

__INLINE__ PalmIPv4::operator const sockaddr_t* () const
{
    return static_cast<const sockaddr_t*>(&SocketAddress);
}

__INLINE__ PalmIPv4::operator sockaddr_t ()
{
    return SocketAddress;
}

__INLINE__ PalmIPv4::operator const sockaddr_t () const
{
    return static_cast<const sockaddr_t>(SocketAddress);
}

__INLINE__ bool PalmIPv4::operator == (const PalmIPv4& _other) const
{
    return PalmOS::MemCompare(&InetAddress, &_other, sizeof(InetAddress)) == 0;
}

__INLINE__ bool PalmIPv4::operator != (const PalmIPv4& _other) const
{
    return PalmOS::MemCopy((void*)(&InetAddress), (void*)(&_other), sizeof(InetAddress)) != 0;
}

__INLINE__ const sockaddr_in_t& PalmIPv4::GetInetAddress() const
{
    return static_cast<const sockaddr_in_t&>(InetAddress);
}

__INLINE__ void PalmIPv4::SetInetAddress(const sockaddr_in_t& _address)
{
    PalmOS::MemCopy(&InetAddress, &_address, sizeof(InetAddress));
}

__INLINE__ const sockaddr_t& PalmIPv4::GetSocketAddress() const
{
    return static_cast<const sockaddr_t&>(SocketAddress);
}

__INLINE__ void PalmIPv4::SetSocketAddress(const sockaddr_t& _address)
{
    PalmOS::MemCopy(&SocketAddress, &_address, sizeof(SocketAddress));
}

__INLINE__ int16 PalmIPv4::GetFamily() const
{
    return InetAddress.family;
}

__INLINE__ void PalmIPv4::SetFamily(int16 _family)
{
    InetAddress.family = _family;
}

__INLINE__ uint16 PalmIPv4::GetPort() const
{
    return InetAddress.port;
}

__INLINE__ void PalmIPv4::SetPort(uint16 _port)
{
    InetAddress.port = HtoNS(_port);
}

__INLINE__ uint32 PalmIPv4::GetIPv4Address() const
{
    return static_cast<uint32>(InetAddress.addr);
}

__INLINE__ const in_addr_t& PalmIPv4::GetIPv4Address(int32) const
{
    return static_cast<const in_addr_t&>(InetAddress.addr);
}

__INLINE__ void PalmIPv4::SetIPv4Address(uint32 _ip)
{
    InetAddress.addr = HtoNL(_ip);
}

__INLINE__ void PalmIPv4::SetIPv4Address(const in_addr_t& _address)
{
    InetAddress.addr = _address;
}

__INLINE__ void PalmIPv4::SetIPv4Address(uint32 _ip, uint16 _port)
{
    InetAddress.addr = HtoNL(_ip);
    InetAddress.port = HtoNS(_port);
}

// network classes
// ------- -------
#define IN_CLASSA(i)       (((int32)(i) & 0x80000000) == 0)
#define IN_CLASSA_NET      0xFF000000
#define IN_CLASSA_NSHIFT   24
#define IN_CLASSA_HOST     0x00FFFFFF
#define IN_CLASSA_MAX      128

#define IN_CLASSB(i)       (((int32)(i) & 0xC0000000) == 0x80000000)
#define IN_CLASSB_NET      0xFFFF0000
#define IN_CLASSB_NSHIFT   16
#define IN_CLASSB_HOST     0x0000FFFF
#define IN_CLASSB_MAX      65536

#define IN_CLASSC(i)       (((int32)(i) & 0xE0000000) == 0xC0000000)
#define IN_CLASSC_NET      0xFFFFFF00
#define IN_CLASSC_NSHIFT   8
#define IN_CLASSC_HOST     0x000000FF

#define IN_CLASSD(i)       (((LONG)(I) & 0xF0000000) == 0xE0000000)
#define IN_CLASSD_NET      0xF0000000
#define IN_CLASSD_NSHIFT   28
#define IN_CLASSD_HOST     0x0FFFFFFF
#define IN_MULTICAST(i)    IN_CLASSD(i)

#define INADDR_ANY         (uint32)0x00000000
#define INADDR_LOOPBACK    0x7F000001
#define INADDR_BROADCAST   (uint32)0xFFFFFFFF
#define INADDR_NONE        0xFFFFFFFF

#define ADDR_ANY           INADDR_ANY
//
__INLINE__ uint32 PalmIPv4::GetNode(uint32 _subnet_mask) const
{
    if(_subnet_mask == 0)
    {
        PalmIPv4::EClass inet_class = GetClass();

        if(inet_class == PalmIPv4::eClassA)
        {
            _subnet_mask = IN_CLASSA_NET;
        }
        else if(inet_class == PalmIPv4::eClassB)
        {
            _subnet_mask = IN_CLASSB_NET;
        }
        else if(inet_class == PalmIPv4::eClassC)
        {
            _subnet_mask = IN_CLASSC_NET;
        }
        else if(inet_class == PalmIPv4::eClassD)
        {
            _subnet_mask = IN_CLASSD_NET;
        }
        else
        {
            return 0;
        }
    }
    return InetAddress.addr & ~_subnet_mask;
}

__INLINE__ PalmIPv4::EClass PalmIPv4::GetClass() const
{
    if(IN_CLASSA(InetAddress.addr))
    {
        return PalmIPv4::eClassA;
    }
    else if(IN_CLASSB(InetAddress.addr))
    {
        return PalmIPv4::eClassB;
    }
    else if(IN_CLASSC(InetAddress.addr))
    {
        return PalmIPv4::eClassC;
    }
    return PalmIPv4::eClassUnknown;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_IPV4_ADDRESS_INL__

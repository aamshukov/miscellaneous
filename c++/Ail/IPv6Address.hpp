////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IP_V6_ADDRESS_H__
#define __IP_V6_ADDRESS_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IPv6Address
// ----- -----------
class __DECLSPEC__ IPv6Address : public NetAddress
{
    // all 'in'  parameters are host-ordered
    // all 'out' parameters are network-ordered
    // internal reperesentation is network-ordered
    public:

    enum EFormat
    {
        Unformat = 0,
        Host_Port,
        Hex_Port,
        Hex_IPv4_Port
    };

    private:
     typedef sockaddr_in6 _InetAddress;
     //
    _InetAddress            InetAddress;
    private:
     static void            xxassert(int, uint = X::InvalidArg);
    public:
     // ctor/dtor
                            IPv6Address();
                            IPv6Address(const IPv6Address&);
                            IPv6Address(const sockaddr_in6&);
                            IPv6Address(const tchar*, ushort = 0, short = AF_INET6);
     virtual               ~IPv6Address();

     // operators
                            // sockaddr_in
                            operator sockaddr_in6* ();
                            operator const sockaddr_in6* ()                                 const;
                            operator sockaddr_in6 ();
                            operator const sockaddr_in6 ()                                  const;

     IPv6Address&           operator =  (const IPv6Address&);
     IPv6Address&           operator =  (const sockaddr_in6&);

     bool                   operator == (const IPv6Address&)                                const;
     bool                   operator != (const IPv6Address&)                                const;

     // access
     bool                   IsValid()                                                       const;
     int                    GetSize()                                                       const;

     const sockaddr_in6&    GetInetAddress()                                                const;
     void                   SetInetAddress(const sockaddr_in6&);

     ushort                 GetPort()                                                       const;
     void                   SetPort(ushort);

     ulong                  GetFlow()                                                       const;
     void                   SetFlow(ulong);

     ushort                 GetFamily()                                                     const;
     void                   SetFamily(ushort);

     uint                   GetIPv4Address()                                                const;
     const in_addr6&        GetIPv6Address()                                                const;
     void                   SetIPv6Address(const tchar*, ushort = 0, short = AF_INET6);

     // protocol
     void                   GetHostName(tchar*, int)                                        const;
     ulong                  Hash()                                                          const;
     //
     void                   GetAddressAsString(tchar*, EFormat = IPv6Address::Host_Port) const;
    public:

    /////////////////////
    // class XIPv6Address
    // ----- ------------
    class __DECLSPEC__ XIPv6Address : public X
    {
        public:
            XIPv6Address(uint = X::Failure);
    };

    friend class XIPv6Address;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IP_V6_ADDRESS_H__

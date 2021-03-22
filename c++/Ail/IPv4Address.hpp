////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IP_V4_ADDRESS_H__
#define __IP_V4_ADDRESS_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IPv4Address
// ----- -----------
class __DECLSPEC__ IPv4Address : public NetAddress
{
    // all 'in'  parameters are host-ordered
    // all 'out' parameters are network-ordered
    // internal reperesentation is network-ordered
    public:

    enum EFormat
    {
        Unformat  = 0,
        IP_Port   = 1,
        Host_Port = 2
    };

    enum EClass
    {
        ClassA,      // A class net addressing
        ClassB,      // B class net addressing
        ClassC,      // C class net addressing
        ClassD,      // not in use
        ClassE,      // not in use
        ClassUnknown // Unknown class net addressing
    };

    private:
     typedef sockaddr_in _InetAddress;
     typedef sockaddr    _SocketAddress;
     //
     union
     {
        _InetAddress    InetAddress;
        _SocketAddress  SocketAddress;
     };

    private:
     static void        xxassert(int, uint = X::InvalidArg);
    public:
     // ctor/dtor
                        IPv4Address();
                        IPv4Address(const IPv4Address&);
                        IPv4Address(const sockaddr_in&);
                        IPv4Address(const sockaddr&);
                        IPv4Address(uint, ushort = 0, short = AF_INET);
                        IPv4Address(const URL&);
                        IPv4Address(const tchar*, ushort = 0, short = AF_INET);
                        IPv4Address(const byte*, short = AF_INET);
     virtual           ~IPv4Address();

     // operators
                        // sockaddr_in
                        operator sockaddr_in* ();
                        operator const sockaddr_in* ()                                  const;
                        operator sockaddr_in ();
                        operator const sockaddr_in ()                                   const;

                        // sockaddr
                        operator sockaddr* ();
                        operator const sockaddr* ()                                     const;
                        operator sockaddr ();
                        operator const sockaddr ()                                      const;

     IPv4Address&       operator =  (const IPv4Address&);
     IPv4Address&       operator =  (const sockaddr_in&);

     bool               operator == (const IPv4Address&)                                const;
     bool               operator != (const IPv4Address&)                                const;

     // access
     bool               IsValid()                                                       const;
     int                GetSize()                                                       const;

     const sockaddr_in& GetInetAddress()                                                const;
     void               SetInetAddress(const sockaddr_in&);
     const sockaddr&    GetSocketAddress()                                              const;
     void               SetSocketAddress(const sockaddr&);

     ushort             GetFamily()                                                     const;
     void               SetFamily(ushort);

     ushort             GetPort()                                                       const;
     void               SetPort(ushort);

     uint               GetIPv4Address()                                                const;
     const in_addr&     GetIPv4Address(int)                                             const;

     void               SetIPv4Address(uint);
     void               SetIPv4Address(const in_addr&);
     void               SetIPv4Address(uint, ushort);
     void               SetIPv4Address(const tchar*, ushort);
     void               SetIPv4Address(const tchar*);
     void               SetIPv4Address(const tchar*, const tchar*, const tchar* = _t("tcp"));
     void               SetIPv4Address(uint, const tchar*, const tchar* = _t("tcp"));

     // protocol
     void               GetHostName(tchar*, int)                                        const;

     uint               GetNode(uint = 0)                                               const;
     EClass             GetClass()                                                      const;

     void               GetAddressAsString(tchar*, EFormat = IPv4Address::IP_Port)      const;
     ulong              Hash()                                                          const;
     //
     static uint        ConvertAddress(const tchar*);
     static void        ConvertAddress(uint, tchar*, bool = true);
    public:

    /////////////////////
    // class XIPv4Address
    // ----- ------------
    class __DECLSPEC__ XIPv4Address : public X
    {
        public:
            XIPv4Address(uint = X::Failure);
    };

    friend class XIPv4Address;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IP_V4_ADDRESS_H__

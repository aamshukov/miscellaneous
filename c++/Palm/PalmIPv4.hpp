////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_IPV4_ADDRESS_H__
#define __PALM_IPV4_ADDRESS_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmIPv4
// ----- --------
class __DECLSPEC__ PalmIPv4
{
    // all 'in'  parameters are host-ordered
    // all 'out' parameters are network-ordered
    // internal reperesentation is network-ordered
    public:

    enum EFormat
    {
        eUnformat  = 0,
        eIP_Port   = 1,
        eHost_Port = 2
    };

    enum EClass
    {
        eClassA,      // A class net addressing
        eClassB,      // B class net addressing
        eClassC,      // C class net addressing
        eClassD,      // not in use
        eClassE,      // not in use
        eClassUnknown // unknown class net addressing
    };

    public:

     union
     {
        sockaddr_in_t InetAddress;
        sockaddr_t    SocketAddress;
     };

    public:
     // ctor/dtor
                            PalmIPv4();
                            PalmIPv4(const PalmIPv4&);
                            PalmIPv4(const sockaddr_in_t&);
                            PalmIPv4(const sockaddr_t&);
                            PalmIPv4(uint32, uint16 = 0, int16 = netSocketAddrINET);
                            PalmIPv4(const URL&);
                            PalmIPv4(const char*, uint16 = 0, int16 = netSocketAddrINET);
                            PalmIPv4(const byte*, int16 = netSocketAddrINET);
     virtual               ~PalmIPv4();

     // operators
                            // sockaddr_in
                            operator sockaddr_in_t* ();
                            operator const sockaddr_in_t* ()                                const;
                            operator sockaddr_in_t ();
                            operator const sockaddr_in_t ()                                 const;

                            // sockaddr
                            operator sockaddr_t* ();
                            operator const sockaddr_t* ()                                   const;
                            operator sockaddr_t ();
                            operator const sockaddr_t ()                                    const;

     PalmIPv4&              operator =  (const PalmIPv4&);
     PalmIPv4&              operator =  (const sockaddr_in_t&);

     bool                   operator == (const PalmIPv4&)                                   const;
     bool                   operator != (const PalmIPv4&)                                   const;

     // access
     bool                   IsValid()                                                       const;
     int16                  GetSize()                                                       const;

     const sockaddr_in_t&   GetInetAddress()                                                const;
     void                   SetInetAddress(const sockaddr_in_t&);
     const sockaddr_t&      GetSocketAddress()                                              const;
     void                   SetSocketAddress(const sockaddr_t&);

     int16                  GetFamily()                                                     const;
     void                   SetFamily(int16);

     uint16                 GetPort()                                                       const;
     void                   SetPort(uint16);

     uint32                 GetIPv4Address()                                                const;
     const in_addr_t&       GetIPv4Address(int32)                                           const;

     void                   SetIPv4Address(uint32);
     void                   SetIPv4Address(const in_addr_t&);
     void                   SetIPv4Address(uint32, uint16);
     void                   SetIPv4Address(const char*, uint16);
     void                   SetIPv4Address(const char*);
     void                   SetIPv4Address(const char*, const char*, const char* = "tcp");
     void                   SetIPv4Address(uint32, const char*, const char* = "tcp");

     // protocol
     void                   GetHostName(char*, uint16)                                      const;

     uint32                 GetNode(uint32 = 0)                                             const;
     EClass                 GetClass()                                                      const;

     void                   GetAddressAsString(char*, EFormat = PalmIPv4::eIP_Port);
     ulong                  Hash()                                                          const;
     //
     static uint32          ConvertAddress(const char*);
     static void            ConvertAddress(uint32, char*, bool = true);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_IPV4_ADDRESS_H__

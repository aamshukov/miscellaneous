////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ICMP_H__
#define __ICMP_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ICMP
// ----- ----
class __DECLSPEC__ ICMP
{
    public:

    enum EConst
    {
        DEF_MAXHOPS     = 30,   // max number of hops
        DEF_NPROBES     = 3,    // number of probe packets to send
        DEF_MAXQUIT     = 5,    // quit after this consecutive timeouts
        DEF_TIMEOUT     = 3,    // time to wait for response (seconds)
        DEF_RETRIES     = 2,    // number of datagram retries per nameserver
        DEF_RETRANS     = 3,    // timeout (seconds) between datagram retries

        MAX_START_TTL   = 255,  // Cisco and BSD4.3
        NETWARE_TTL     = 128,  // Netware routers
        OLD_PROTEON_TTL = 29,   // Proteon 8.1 and lower
        NEW_PROTEON_TTL = 59,   // Proteon 8.2 and higher
        OLD_BSD_TCP     = 30,
        NEW_BSD_TCP     = 60,
    };

    enum EType
    {
        ICMP_ECHOREPLY              = 0,    // echo reply
        ICMP_UNREACH                = 3,    // dest unreachable, codes:
        ICMP_UNREACH_NET            = 0,    // bad net
        ICMP_UNREACH_HOST           = 1,    // bad host
        ICMP_UNREACH_PROTOCOL       = 2,    // bad protocol
        ICMP_UNREACH_PORT           = 3,    // bad port
        ICMP_UNREACH_NEEDFRAG       = 4,    // IP_DF caused drop
        ICMP_UNREACH_SRCFAIL        = 5,    // src route failed
        ICMP_SOURCEQUENCH           = 4,    // packet lost, slow down
        ICMP_REDIRECT               = 5,    // shorter route, codes:
        ICMP_REDIRECT_NET           = 0,    // for network
        ICMP_REDIRECT_HOST          = 1,    // for host
        ICMP_REDIRECT_TOSNET        = 2,    // for tos and net
        ICMP_REDIRECT_TOSHOST       = 3,    // for tos and host
        ICMP_ECHO                   = 8,    // echo service
        ICMP_TIMXCEED               = 11,   // time exceeded, code:
        ICMP_TIMXCEED_INTRANS       = 0,    // ttl==0 in transit
        ICMP_TIMXCEED_REASS         = 1,    // ttl==0 in reass
        ICMP_PARAMPROB              = 12,   // ip header bad
        ICMP_TSTAMP                 = 13,   // timestamp request
        ICMP_TSTAMPREPLY            = 14,   // timestamp reply
        ICMP_IREQ                   = 15,   // information request
        ICMP_IREQREPLY              = 16,   // information reply
        ICMP_MASKREQ                = 17,   // address mask request
        ICMP_MASKREPLY              = 18,   // address mask reply

        // new
        ICMP_ROUTERADVERT           = 9,    // router advertisement
        ICMP_ROUTERSOLICIT          = 10,   // router solicitation
        ICMP_UNREACH_NET_UNKNOWN    = 6,    // unknown net
        ICMP_UNREACH_HOST_UNKNOWN   = 7,    // unknown host
        ICMP_UNREACH_ISOLATED       = 8,    // src host isolated
        ICMP_UNREACH_NET_PROHIB     = 9,    // prohibited access
        ICMP_UNREACH_HOST_PROHIB    = 10,   // ditto
        ICMP_UNREACH_TOSNET         = 11,   // bad tos for net
        ICMP_UNREACH_TOSHOST        = 12,   // bad tos for host

        // defined per RFC 1812 (chapter 5.2.7.1)
        ICMP_UNREACH_ADM_PROHIB     = 13,   // prohibited access
        ICMP_UNREACH_PREC_VIOL      = 14,   // precedence violation
        ICMP_UNREACH_PREC_CUT       = 15    // precedence cutoff
    };

    enum EError
    {
        EX_SUCCESS      = 0,    // successful termination
        EX_USAGE        = 64,   // command line usage error
        EX_DATAERR      = 65,   // data format error
        EX_NOINPUT      = 66,   // cannot open input
        EX_NOUSER       = 67,   // addressee unknown
        EX_NOHOST       = 68,   // host name unknown
        EX_UNAVAILABLE  = 69,   // service unavailable
        EX_SOFTWARE     = 70,   // internal software error
        EX_OSERR        = 71,   // system error (e.g., can't fork)
        EX_OSFILE       = 72,   // critical OS file missing
        EX_CANTCREAT    = 73,   // can't create (user) output file
        EX_IOERR        = 74,   // input/output error
        EX_TEMPFAIL     = 75,   // temp failure; user is invited to retry
        EX_PROTOCOL     = 76,   // remote error in protocol
        EX_NOPERM       = 77,   // permission denied
        EX_CONFIG       = 78    // local configuration error
    };

    class __DECLSPEC__ IPHeader
    {
        typedef struct in_addr _address;

        public:
        
        enum EFlags
        {
            IP_DF = 0x4000,     // don't fragment flag
            IP_MF = 0x2000      // more fragments flag
        };

        public:
#if (__BYTE_ORDER__ == __LITTLE_ENDIAN__ || __BYTE_ORDER__ == __PDP_ENDIAN__)
         byte       Length:4;   // header length
         byte       Version:4;  // version
#else
         byte       Version:4;  // version
         byte       HLength:4;  // header length
#endif
         byte       TOS;        // type of service
         short      TLength;    // total length
         ushort     ID;         // identification
         short      Offset;     // fragment offset field
         byte       TTL;        // time to live
         byte       Proto;      // protocol
         ushort     Checksum;   // checksum
        _address    IPSrc;      // source address
        _address    IPDst;      // dest address
        public:
         // ctor/dtor
                    IPHeader();
                   ~IPHeader();
    };

    class __DECLSPEC__ ICMPHeader
    {
        typedef struct in_addr _address;

        public:
         byte       Type;       // type of message, see below
         byte       Code;       // type sub code
         ushort     Checksum;   // ones complement cksum of struct

        union _HUN
        {
            byte    PPtr;       // ICMP_PARAMPROB
           _address GWAddress;  // ICMP_REDIRECT

            struct _IDSeq
            {
                ushort ID;
                ushort Seq;
            } IDSeq;

            int     Void;
        } HUN;

        union _DUN
        {
            struct _TS
            {
                uint OTime;
                uint RTime;
                uint TTime;
            } TS;

            struct _IP
            {
//                IPHeader IPHdr;
                // options and then 64 bits of data
            } IP;

            uint    Mask;
            byte    Data[1];
        } DUN;
    };

    private:
     static int     MTU[19];
    public:
     // ctor/dtor
                    ICMP();
                   ~ICMP();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ICMP_H__

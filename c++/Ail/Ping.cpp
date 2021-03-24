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

#ifndef __PING_INC__
#   include <Ping.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IpHeader
// ----- --------
Ping::IpHeader::IpHeader()
{
    InitMemory(this, sizeof(*this));
}
////////////////////////////////////////////////////////////////////////////////////////
// class IcmpHeader
// ----- ----------
Ping::IcmpHeader::IcmpHeader()
{
    InitMemory(this, sizeof(*this));
}
////////////////////////////////////////////////////////////////////////////////////////
// class Ping
// ----- ----
Ping::Ping()
{
}

Ping::~Ping()
{
}

void Ping::DoPing(const IPv4Address& _address, ushort _packetsize, ushort _count)
{
    // create raw socket
    Connection.Create(false, IPPROTO_ICMP);
    Connection.SetBufferSize();
    //
    ushort psize  = min(Ping::MaxPacketSize, max(Ping::MinPacketSize, _packetsize));
           psize += sizeof(Ping::IcmpHeader);

    byte* buffer   = reinterpret_cast<byte*>(STACK_ALLOCATE(Ping::MaxPacketSize));
    byte* icmpdata = reinterpret_cast<byte*>(STACK_ALLOCATE(Ping::MaxPacketSize));

    // prepare icmp header
    InitMemory(icmpdata, Ping::MaxPacketSize);

    Ping::IcmpHeader* icmphdr = reinterpret_cast<Ping::IcmpHeader*>(icmpdata);

    icmphdr->Type      = 8;// ICMP_ECHO
    icmphdr->Code      = 0;
    icmphdr->Id        = static_cast<ushort>(::GetCurrentProcessId());
    icmphdr->Checksum  = 0;
    icmphdr->SeqNumber = 0;

    memset(icmpdata+sizeof(Ping::IcmpHeader), 'A', psize-sizeof(Ping::IcmpHeader));

    uint cc;
    ushort seqnumber = 0;

    for(ushort i = 0; i < _count; i++)
    {
        ((Ping::IcmpHeader*)icmpdata)->Checksum  = 0;
        ((Ping::IcmpHeader*)icmpdata)->Timestamp = ::GetTickCount();
        ((Ping::IcmpHeader*)icmpdata)->SeqNumber = seqnumber++;
        ((Ping::IcmpHeader*)icmpdata)->Checksum  = Checksum(reinterpret_cast<ushort*>(icmpdata), psize);

        try
        {
            cc = Connection.SendTo(icmpdata, psize, _address);
        }
        catch(Socket::XSocket& _e)
        {
            if(_e.GetSysError() == WSAETIMEDOUT)
            {
                continue;
            }
            break;
        }
        catch(...)
        {
            break;
        }

        try
        {
            IPv4Address address;
            cc = Connection.ReceiveFrom(buffer, Ping::MaxPacketSize, address);
        }
        catch(Socket::XSocket& _e)
        {
            if(_e.GetSysError() == WSAETIMEDOUT)
            {
                continue;
            }
            break;
        }
        catch(...)
        {
            break;
        }

        // decode icmp header
        Ping::IpHeader* iphdr = reinterpret_cast<Ping::IpHeader*>(buffer);
	    ushort iphdrcount = iphdr->HeaderCount*4; // number of 32-bit words *4 = bytes

        if(psize < iphdrcount+Ping::MinPacketSize)
        {
            // ?? something wrong
        }

        icmphdr = reinterpret_cast<Ping::IcmpHeader*>(buffer+iphdrcount);

        if(icmphdr->Type != 0) // ICMP_ECHOREPLY
        {
            // not echo replay
            return;
        }

        if(icmphdr->Id != ::GetCurrentProcessId())
        {
            // not our packet
            return ;
        }
        Sleep(1000); //  1 sec timeout
    }
}

ushort Ping::Checksum(ushort* _buffer, int _count)
{
    if(_buffer == null || _count == 0)
    {
        return 0;
    }

    ulong cksum = 0;

    while(_count > 1)
    {
        cksum += *_buffer++;
       _count -= sizeof(ushort);
    }
  
    // mop up an odd byte, if neccessary
    // see w.richard stevens "unix network programming" vol.1, p.672
    if(_count > 0)
    {
        cksum += *(byte*)_buffer;
  }

    // add back carry outs from top 16 bits to low 16 bits
    // see w.richard stevens "unix network programming" vol.1, p.672
    cksum  = (cksum >> 16)+(cksum & 0xFFFF); // add hi 16 to low 16
    cksum += (cksum >>16);                   // add carry
    return ushort(~cksum);                   // truncate to 16 bits
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

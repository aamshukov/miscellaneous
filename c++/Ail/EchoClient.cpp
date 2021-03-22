////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __ECHO_CLIENT_INC__
#   include <EchoClient.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class EchoClient
// ----- ----------
EchoClient::EchoClient()
{
}

EchoClient::EchoClient(const IPv4Address& _address) : Connection(_address)
{
}

EchoClient::~EchoClient()
{
}

bool EchoClient::Echo(const byte* _data, int _count, int _timeout, int _flags)
{
    try
    {
        AutoPtrArray<byte> buffer(new byte[_count]);
        InitMemory(buffer, _count);
        //
        Connection.Connect();
        Connection.Send(_data, _count, _timeout, _flags);
        Connection.Receive(buffer, _count, _timeout, _flags);
        return memcmp(buffer, _data, _count) == 0;
    }
    catch(...)
    {
        return false;
    }
}

bool EchoClient::Echo(const byte* _data, int _count, IPv4Address& _remote_address, int _timeout, int _flags)
{
    try
    {
        AutoPtrArray<byte> buffer(new byte[_count]);
        InitMemory(buffer, _count);
        //
        Connection.Create();
        Connection.SendTo(_data, _count, _remote_address, _timeout, _flags);
        Connection.ReceiveFrom(buffer, _count, _remote_address, _timeout, _flags);
        return memcmp(buffer, _data, _count) == 0;
    }
    catch(...)
    {
        return false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

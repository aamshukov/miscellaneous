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

#ifndef __INET_UTIL_INC__
#   include <InetUtil.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
static const tchar* NTPServers[] =
{
   _t("192.5.5.250"),   // clock.isc.org
   _t("209.81.9.7"),    // clock.via.net
   _t("18.72.0.3"),     // bitsy.mit.edu
   _t("18.26.4.105"),   // bonehed.lcs.mit.edu
   _t("192.93.2.20"),   // canon.inria.fr
   _t("16.1.0.4"),      // clepsydra.dec.com 204.123.2.5
   _t("192.48.153.74"), // clock.sgi.com
   _t("128.156.1.43"),  // lerc-dns.lerc.nasa.gov 
   _t("129.132.2.21"),  // swisstime.ethz.ch
   _t("192.5.41.40"),   // tick.usno.navy.mil
   _t("128.156.1.43"),  // lerc-dns.lerc.nasa.gov
   _t("140.142.16.34"), // bigben.cac.washington.edu (CNAME ntp-wu.usno.navy.mil) 
    null
};
////////////////////////////////////////////////////////////////////////////////////////
// class InetUtil
// ----- --------
const tchar** InetUtil::GetNTPServers()
{
    return NTPServers;
}

bool InetUtil::GetNetworkTime(tchar* _buffer, uint _count, const tchar* _url, const tchar* _username, const tchar* _password, const tchar* _proxy, const tchar* _socks, short _socks_ver, InetUtil::ETimeProtocol _proto, uint _timeout)
{
    if(_buffer == null || _url == null)
    {
        return false;
    }
   _buffer[0] = 0;
    //
    InetConnection connection;

    connection.SetUsername(_username);
    connection.SetPassword(_password);
    connection.SetProxy(_proxy);
    connection.SetSocks(_socks);
    connection.SetSocksVer(_socks_ver);

    /////////////////////////////////////////////////////////////////////////////////////
    #define GETTIME                                                                     \
    if(socket.IsConnected())                                                            \
    {                                                                                   \
        uint count = socket.Send(reinterpret_cast<byte*>(&" "), 1, _timeout);           \
             count = socket.Receive(reinterpret_cast<byte*>(_buffer), _count, _timeout);\
    }                                                                                   \
    /////////////////////////////////////////////////////////////////////////////////////

    if(_url != null)
    {
        // try supplied url
        IPv4Address address(_url);
        StreamSocket socket;
        socket.SetRemoteAddress(address);
        connection.Connect(socket, _url);
        GETTIME
    }
    else
    {
        // try predefined urls
        for(int i = 0; NTPServers[i] != null; i++)
        {
            IPv4Address address(NTPServers[i]);
            StreamSocket socket;
            socket.SetRemoteAddress(address);
            connection.Connect(socket, NTPServers[i]);

            if(socket.IsConnected())
            {
                GETTIME
                break;
            }
        }
    }
    //////////////
    #undef GETTIME
    //////////////
    return _buffer[0] != 0;
}

uint InetUtil::GetNetworkTime(const tchar* _url, const tchar* _username, const tchar* _password, const tchar* _proxy, const tchar* _socks, short _socks_ver, uint _timeout)
{
    uint buffer;
    InetUtil::GetNetworkTime(reinterpret_cast<tchar*>(&buffer), sizeof(buffer), _url, _username, _password, _proxy, _socks, _socks_ver, InetUtil::Time, _timeout);
    return buffer;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

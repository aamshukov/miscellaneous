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

#ifndef __INET_CONNECTION_INC__
#   include <InetConnection.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class InetConnection
// ----- --------------
InetConnection::InetConnection()
{
}

InetConnection::~InetConnection()
{
}

void InetConnection::Connect(StreamSocket& _connection, const tchar* _url, uint _timeout)
{
    if(_connection.IsConnected() || _url == null)
    {
        return;
    }
    //
    if(Socks != null)
    {
        // RFC1928/RFC1929
        // connect through SOCKS server
        URL socks(Socks);
        IPv4Address address(_url);
        IPv4Address socks_address(socks.GetHost(), socks.GetPort());
       _connection.SetRemoteAddress(socks_address);
       _connection.Connect();

        if(SocksVer == 4) // SOCKS4
        {
            // try to connect
            // the syntax of the request is as follows:
            //    VER(1) CMD(1) DST.PORT(2) DST.IP(4) USERID(~) NULL
            // the syntax of the replay is as follows:
            //    VER(1) CMD(1) DST.PORT(2) DST.IP(4)
            // return code is as follows:
            //  90: request granted
            //  91: request rejected or failed
            //  92: request rejected because SOCKS server cannot connect to identd on the client
            //  93: request rejected because the client program and identd report different user-ids
            byte request[1+1+2+4+1]; // +1 for '0'
            memset(&request, 0, sizeof(request));

            uint ip = address.GetIPv4Address();
            ushort port = address.GetPort();

            request[0] = 0x04; // version SOCKS4
            request[1] = 0x01; // connect
            memcpy(&request[2], &port, 2);
            memcpy(&request[4], &ip, 4);

            uint count = _connection.Send(request, sizeof(request), _timeout);
            memset(&request, 0, sizeof(request));
            count = _connection.Receive(request, sizeof(request), _timeout);

            if(count == 0 || request[1] != 90)
            {
                return;
            }
        }
        else // SOCKS5
        {
            // socks negotiation
            byte b[4];

            b[0] = 0x05; // version SOCKS5
            b[1] = 0x01;
            b[2] = Password == null ? 0x00 : 0x02; // gss-api - '01'; username/password - '02'
            b[3] = 0x00;

            uint count = _connection.Send(b, 3, _timeout);
            b[0] = b[1] = b[2] = 0;
            count = _connection.Receive(b, sizeof(b), _timeout);

            // X'00' NO AUTHENTICATION REQUIRED
            // X'01' GSSAPI
            // X'02' USERNAME/PASSWORD
            // X'03' to X'7F' IANA ASSIGNED
            // X'80' to X'FE' RESERVED FOR PRIVATE METHODS
            // X'FF' NO ACCEPTABLE METHODS
            if(count == 0 || b[0] != 0x05 || b[1] == 0xFF)
            {
                return;
            }

            if(b[1] == 0x01)
            {
                // auth GSS-API
            }
            else if(b[1] == 0x02)
            {
                // auth USERNAME/PASSWORD
                // the syntax of the request is as follows:
                //  VER(1) ULEN(1) UNAME(255) PLEN(1) PASSWD(255)
                byte up[1+1+255+1+255];
                memset(&up, 0, sizeof(up));

                if(Username != null)
                {
                    up[0]  = 0x01;
                    up[1]  = StrLen(Username);
                    memcpy(&up[2], Username, up[1]);
                }

                if(Password != null)
                {
                    up[256] = StrLen(Password);
                    memcpy(&up[257], Password, up[256]);
                }

                uint count = _connection.Send(up, sizeof(up), _timeout);
                memset(&up, 0, sizeof(up));
                count = _connection.Receive(up, sizeof(up), _timeout);

                // a STATUS field of X'00' indicates success. If the server returns a
                // `failure' (STATUS value other than X'00') status, it MUST close the connection.
                if(up[1] != 0)
                {
                    return;
                }
            }

            // try to connect
            // the syntax of the request is as follows:
            //    VER(1) CMD(1) RSV(1) ATYP(1) DST.ADDR(~) DST.PORT(2)
            // the syntax of the replay is as follows:
            //    VER(1) REP(1) RSV(1) ATYP(1) BND.ADDR(~) BND.PORT(2)
            byte request[1+1+1+1+4+2];
            memset(&request, 0, sizeof(request));

            uint ip = address.GetIPv4Address();
            ushort port = address.GetPort();

            request[0] = 0x05;
            request[1] = 0x01; // connect
            request[3] = 0x01; // IPv4

            memcpy(&request[4], &ip, 4);
            memcpy(&request[8], &port, 2);

            count = _connection.Send(request, sizeof(request), _timeout);
            memset(&request, 0, sizeof(request));
            count = _connection.Receive(request, sizeof(request), _timeout);

            // X'00' succeeded
            // X'01' general SOCKS server failure
            // X'02' connection not allowed by ruleset
            // X'03' Network unreachable
            // X'04' Host unreachable
            // X'05' _connection refused
            // X'06' TTL expired
            // X'07' Command not supported
            // X'08' Address type not supported
            // X'09' to X'FF' unassigned
            if(count == 0 || request[0] != 0x05 || request[1] != 0x00)
            {
                return;
            }
        }
    }
    else if(Proxy != null)
    {
        // connect through proxy server
        URL proxy(Proxy);
        IPv4Address address(proxy.GetHost(), proxy.GetPort());
       _connection.SetRemoteAddress(address);
       _connection.Connect();
    }
    else
    {
        // direct connection
        IPv4Address address(_url);
       _connection.SetRemoteAddress(address);
       _connection.Connect();
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

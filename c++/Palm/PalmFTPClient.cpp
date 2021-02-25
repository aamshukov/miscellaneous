////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_FTP_CLIENT_INC__
#   include <PalmFTPClient.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPClient
// ----- ---------
FTPClient::FTPClient(const FTPURL& _url) : Resource(_url), Terminated(false), SocksVersion(4)
{
}

FTPClient::~FTPClient()
{
    Connection.Disconnect();
}

ftpcode FTPClient::Connect()
{
    if(!SOCKSServer.GetURL().empty())
    {
        // RFC1928/RFC1929
        // connect through SOCKS server
        PalmIPv4 address(Resource);
        PalmIPv4 socks_address(SOCKSServer.GetHost().c_str(), SOCKSServer.GetPort());

        Connection.SetRemoteAddress(socks_address);
        Connection.Connect();

        if(SocksVersion == 4) // SOCKS4
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
            PalmOS::MemSet(&request, sizeof(request));

            uint32 ip = address.GetIPv4Address();
            uint16 port = address.GetPort();

            request[0] = 0x04; // version SOCKS4
            request[1] = 0x01; // connect
            PalmOS::MemCopy(&request[2], &port, 2);
            PalmOS::MemCopy(&request[4], &ip, 4);

            uint32 count = Connection.Send(request, sizeof(request), PalmSocket::eTimeout);
            PalmOS::MemSet(&request, sizeof(request));
            count = Connection.Receive(request, sizeof(request), PalmSocket::eTimeout);

            if(count == 0 || request[1] != 90)
            {
                return FTProtocol::eCode0;
            }
#ifdef _DEBUG
            // just for fun ! ...
            PalmOS::MemCopy(&port, &request[2], 2);
            PalmOS::MemCopy(&ip, &request[4], 4);

            if(ip == 0)
            {
                // SOCKS server is not multi-homed host
                ip = socks_address.GetIPv4Address();
            }
            //
            const uint16 _port_mask_ = 0x00FF;
            const uint32 _ip_mask_   = 0xFF000000;
            //
            int x = 1;
            bool little_endian = (*(char*)&x) == 1;

            if(little_endian)
            {
                // convert from the network order back to the host order
                port = static_cast<uint16>(((port >> 8) & _port_mask_)|((port & _port_mask_) << 8));

                uint32 tmp;
                uint32* p = &ip;

                tmp   = static_cast<byte>(*p);
                tmp <<= 8;
                *p  >>= 8;

                tmp  += static_cast<byte>(*p);
                tmp <<= 8;
                *p  >>= 8;

                tmp  += static_cast<byte>(*p);
                tmp <<= 8;
                *p  >>= 8;

                tmp += static_cast<byte>(*p);
                *p   = tmp;
            }
#endif
        }
        else // SOCKS5
        {
            // socks negotiation
            byte b[4];

            b[0] = 0x05; // version SOCKS5
            b[1] = 0x01;
            b[2] = static_cast<byte>(Password.empty() == null ? 0x00 : 0x02); // gss-api - '01'; username/password - '02'
            b[3] = 0x00;

            uint32 count = Connection.Send(b, 3, PalmSocket::eTimeout);
            b[0] = b[1] = b[2] = 0;
            count = Connection.Receive(b, sizeof(b), PalmSocket::eTimeout);

            // X'00' NO AUTHENTICATION REQUIRED
            // X'01' GSSAPI
            // X'02' USERNAME/PASSWORD
            // X'03' to X'7F' IANA ASSIGNED
            // X'80' to X'FE' RESERVED FOR PRIVATE METHODS
            // X'FF' NO ACCEPTABLE METHODS
            if(count == 0 || b[0] != 0x05 || b[1] == 0xFF)
            {
                return FTProtocol::eCode0;
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
                PalmOS::MemSet(&up, sizeof(up));

                up[0] = 0x01;
                up[1] = static_cast<byte>(Username.size());
                PalmOS::MemCopy(&up[2], Username.c_str(), up[1]);

                up[256] = static_cast<byte>(Password.size());
                PalmOS::MemCopy(&up[257], Password.c_str(), up[256]);

                uint32 count = Connection.Send(up, sizeof(up), PalmSocket::eTimeout);
                PalmOS::MemSet(&up, sizeof(up));
                count = Connection.Receive(up, sizeof(up), PalmSocket::eTimeout);

                // a STATUS field of X'00' indicates success. If the server returns a
                // `failure' (STATUS value other than X'00') status, it MUST close the connection.
                if(up[1] != 0)
                {
                    return FTProtocol::eCode0;
                }
            }

            // try to connect
            // the syntax of the request is as follows:
            //    VER(1) CMD(1) RSV(1) ATYP(1) DST.ADDR(~) DST.PORT(2)
            // the syntax of the replay is as follows:
            //    VER(1) REP(1) RSV(1) ATYP(1) BND.ADDR(~) BND.PORT(2)
            byte request[1+1+1+1+4+2];
            PalmOS::MemSet(&request, sizeof(request));

            uint32 ip = address.GetIPv4Address();
            uint16 port = address.GetPort();

            request[0] = 0x05;
            request[1] = 0x01; // connect
            request[3] = 0x01; // IPv4

            PalmOS::MemCopy(&request[4], &ip, 4);
            PalmOS::MemCopy(&request[8], &port, 2);

            count = Connection.Send(request, sizeof(request), PalmSocket::eTimeout);
            PalmOS::MemSet(&request, sizeof(request));
            count = Connection.Receive(request, sizeof(request), PalmSocket::eTimeout);

            // X'00' succeeded
            // X'01' general SOCKS server failure
            // X'02' connection not allowed by ruleset
            // X'03' Network unreachable
            // X'04' Host unreachable
            // X'05' Connection refused
            // X'06' TTL expired
            // X'07' Command not supported
            // X'08' Address type not supported
            // X'09' to X'FF' unassigned
            if(count == 0 || request[0] != 0x05 || request[1] != 0x00)
            {
                return FTProtocol::eCode0;
            }
        }
    }
    else if(!ProxyServer.GetURL().empty())
    {
        // connect through proxy server
        PalmIPv4 address(ProxyServer.GetHost().c_str(), ProxyServer.GetPort());
        Connection.SetRemoteAddress(address);
        Connection.Connect();
    }
    else
    {
        // direct connection
        PalmIPv4 address(Resource);
        Connection.SetRemoteAddress(address);
        Connection.Connect();
    }

    Terminated = false; 

    // get greetings ...
    return GetGreetings();
}

ftpcode FTPClient::Disconnect()
{
    if(Connection.IsConnected())
    {
        byte buffer[1024];
        PalmOS::MemSet(buffer, sizeof(buffer));
        //
        SendCommandQUIT();
        Connection.ReceiveLine(buffer, sizeof(buffer), PalmSocket::eTimeout);
        ftpcode code = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer));
        Connection.Disconnect();
        return code;
    }
    return FTProtocol::eCode0;
}

ftpcode FTPClient::CheckLink(bool _passv, uint16 _timeout)
{
    PalmFile file;
    fsize_t_ size = static_cast<fsize_t_>(-1);
    return GetResource(file, null, 0, size, _passv, _timeout);
}

ftpcode FTPClient::CheckLink(const char* _url, const char* _proxy, bool _passv, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    //
    try
    {
        FTPURL url(_url);
        FTPClient client(url);

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        return client.CheckLink(_passv, _timeout);
    }
    catch(...)
    {
        return FTProtocol::eCode0;
    }
}

ftpcode FTPClient::GetGreetings()
{
    byte buffer[1024];
    PalmOS::MemSet(buffer, sizeof(buffer));

    // get greetings ...
    do
    {
        uint32 count = Connection.ReceiveLine(buffer, sizeof(buffer), PalmSocket::eTimeout);
    }
    while(FTProtocol::IsMultiLineResponse(reinterpret_cast<char*>(buffer)));
    return FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer));
}

ftpcode FTPClient::GetSize(fsize_t_& _size, bool _passv, uint16 _timeout)
{
    PalmFile file;
   _size = static_cast<fsize_t_>(-1);
    return GetResource(file, null, 0, _size, _passv, _timeout);
}

ftpcode FTPClient::GetSize(fsize_t_& _size, const char* _url, const char* _proxy, bool _passv, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    //
    try
    {
        FTPURL url(_url);
        FTPClient client(url);

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        return client.GetSize(_size, _passv, _timeout);
    }
    catch(...)
    {
        return FTProtocol::eCode0;
    }
}

ftpcode FTPClient::GetResource(PalmFile& _file, const char* _url, fpos_t_ _pos, fpos_t_& _size, bool _passv, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);

    // phase I (login)
    if(!Connection.IsConnected())
    {
        Connect();
    }

   _string username = GetUsername();
   _string password = GetPassword();
   _string account  = GetAccount();

    if(username.empty())
    {
        username = Resource.GetUsername();
    }

    if(password.empty())
    {
        password = Resource.GetPassword();
    }

    ftpcode code;

    if((code = Login(username.c_str(), password.c_str(), account.c_str())) != FTProtocol::eCode230)
    {
        return code;
    }

    // phase II (process)
    //  firewall-free case and firewall is present
    //  see RFC 1579 (firewall-friendly ftp)
    if(_passv)
    {
        // firewall-friendly
        code = GetResourceThroughFirewall(_file, _url == null ? Resource.GetURL().c_str() : _url, _pos, _size, _timeout);
    }
    else
    {
        // firewall-free
        code = GetResourceFirewallFree(_file, _url == null ? Resource.GetURL().c_str() : _url, _pos, _size, _timeout);
    }
    return code;
}

ftpcode FTPClient::GetResourceThroughFirewall(PalmFile& _file, const char* _url, fpos_t_ _pos, fsize_t_& _size, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    //
    //
    // firewall case
    PalmIPv4 ip;
    ftpcode code = SendCommandPASV(ip);

    if(code != FTProtocol::eCode227)
    {
        // failed
        return code;
    }

    if((code = SendCommandTYPE(FTProtocol::eASCII, FTProtocol::eNonprint, _timeout)) != FTProtocol::eCode200)
    {
        return code;
    }

    FTPURL url(_url);

    PalmStreamSocket connection;
    connection.SetRemoteAddress(ip);
    connection.Connect();
    connection.SetBufferSize();

    if(_size == -1)
    {
        // just grab size
        return SendCommandSIZE(url.GetAbsPath(), _size, _timeout);
    }

	if(_pos > 0)
    {
        if((code = SendCommandREST(_pos)) == FTProtocol::eCode350)
        {
            _file.Seek(static_cast<int32>(_pos));
        }
    }

    if((code = SendCommandRETR(url.GetAbsPath(), _timeout)) < FTProtocol::eCode100 || code >= FTProtocol::eCode300)
    {
        // failed to retrive the file
        return code;
    }
    //
    byte buffer[1024];
    PalmOS::MemSet(buffer, sizeof(buffer));

    int32 count;
    int32 size = 0;

    while((count = connection.Receive(buffer, sizeof(buffer), _timeout)) > 0)
    {
       _file.Write(buffer, 1, count);
        size += count;

        if(Terminated)
        {
            SendCommandABOR(_timeout);
            return FTProtocol::eCode201;
        }
    }

    if(Connection.GetAvailable() > 0)
    {
        count = Connection.ReceiveLine(buffer, sizeof(buffer), _timeout);
        code  = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer));
    }
    return code;
}

ftpcode FTPClient::GetResourceFirewallFree(PalmFile& _file, const char* _url, fpos_t_ _pos, fsize_t_& _size, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    //
    const uint16 _attempts_ = 128;
    //
    ftpcode code;
    uint16  port = static_cast<uint16>(1024+(::TimGetSeconds()%1024)); // arbitrary

    for(uint16 i = 0; i < _attempts_; ++i)
    {
        PalmIPv4 ip(uint32(0), port);
        PalmStreamSocket listener;
        listener.SetLocalAddress(ip);
        listener.Listen();

        if((code = SendCommandTYPE(FTProtocol::eASCII, FTProtocol::eNonprint, _timeout)) != FTProtocol::eCode200)
        {
            // failed
            break;
        }

        if((code = SendCommandPORT(Connection.GetLocalAddress().GetIPv4Address(), port, _timeout)) != FTProtocol::eCode200)
        {
            // keep going
            ++port;
            continue;
        }

        if((code = SendCommandTYPE(FTProtocol::eBinary, FTProtocol::eNonprint, _timeout)) != FTProtocol::eCode200)
        {
            // failed
            break;
        }

	    if(_pos > 0)
        {
            if((code = SendCommandREST(_pos)) == FTProtocol::eCode350)
            {
                _file.Seek(static_cast<int32>(_pos));
            }
        }

        FTPURL url(_url);

        if(_size == -1)
        {
            // just grab size
            return SendCommandSIZE(url.GetAbsPath(), _size, _timeout);
        }

        if((code = SendCommandRETR(url.GetAbsPath(), _timeout)) < FTProtocol::eCode100 || code >= FTProtocol::eCode300)
        {
            // failed to retrive the file
            break;
        }

        PalmStreamSocket connection;
        listener.Accept(connection);
        connection.SetBufferSize();
        //
        byte buffer[1024];
        PalmOS::MemSet(buffer, sizeof(buffer));

        int32 count;
        int64 size = 0;

        while((count = connection.Receive(buffer, sizeof(buffer), _timeout)) > 0)
        {
           _file.Write(buffer, 1, count);
            size += count;

            if(Terminated)
            {
                SendCommandABOR(_timeout);
                return FTProtocol::eCode201;
            }
        }

        if(Connection.GetAvailable() > 0)
        {
            count = Connection.ReceiveLine(buffer, sizeof(buffer), _timeout);
            code  = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer));
        }
        return code;
    }
    return FTProtocol::eCode0;
}

ftpcode FTPClient::GetResource(const char* _filename, const char* _url, fpos_t_ _pos, const char* _proxy, bool _passv, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    palmxassert(_filename != null, Error::eInvalidArg, FTPClient::XFTPClient);

    try
    {
        fsize_t_ size = 0;

        FTPURL url(_url);
        FTPClient client(url);

        PalmFile file;
    	palmxassert(file.Open(PalmOS::GetCardNumber(), _filename, sysFileTFileStream, PalmOS::GetCreatorID(), fileModeReadOnly) == errNone, Error::eOperationFailure, FTPClient::XFTPClient);

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        return client.GetResource(file, _url, _pos, size, _passv, _timeout);
    }
    catch(...)
    {
        return FTProtocol::eCode0;
    }
}

ftpcode FTPClient::GetList(PalmFile& _file, const char* _url, bool _passv, uint16)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);

    // phase I (login)
    if(!Connection.IsConnected())
    {
        Connect();
    }

   _string username = GetUsername();
   _string password = GetPassword();
   _string account  = GetAccount();

    if(username.empty())
    {
        username = Resource.GetUsername();
    }

    if(password.empty())
    {
        password = Resource.GetPassword();
    }

    ftpcode code;

    if((code = Login(username.c_str(), password.c_str(), account.c_str())) != FTProtocol::eCode230)
    {
        return code;
    }

    // phase II (process)
    //  firewall-free case and firewall is present
    //  see RFC 1579 (firewall-friendly ftp)
    if(_passv)
    {
        // firewall-friendly
        code = GetListThroughFirewall(_file, _url == null ? Resource.GetURL().c_str() : _url);
    }
    else
    {
        // firewall-free
        code = GetListFirewallFree(_file, _url == null ? Resource.GetURL().c_str() : _url);
    }
    return code;
}

ftpcode FTPClient::GetListThroughFirewall(PalmFile& _file, const char* _url, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    //
    PalmIPv4 ip;
    ftpcode code = SendCommandPASV(ip);

    if(code != FTProtocol::eCode227)
    {
        // failed
        return code;
    }

    if((code = SendCommandTYPE(FTProtocol::eASCII, FTProtocol::eNonprint, _timeout)) != FTProtocol::eCode200)
    {
        // failed
        return code;
    }

    FTPURL url(_url);

    PalmStreamSocket connection;

    connection.SetRemoteAddress(ip);
    connection.Connect();
    connection.SetBufferSize();

    if(!connection.IsConnected())
    {
        return FTProtocol::eCode0;
    }

   _string dir = url.GetAbsPath();

    if(!dir.empty() && ((code = SendCommandCWD(dir)) < FTProtocol::eCode100 || code >= FTProtocol::eCode300))
    {
        // failed to retrive the file
        return code;
    }

    if((code = SendCommandLIST(_string())) < FTProtocol::eCode100 || code >= FTProtocol::eCode300)
    {
        // failed to retrive the file
        return code;
    }

    // get the list
    const uint16 _buffer_size_ = 4096;
    const uint16 _line_size_   = 1024;
    //
    int16 count;
    AutoPtrArray<byte> buffer(new byte[_buffer_size_]);
    AutoPtrArray<char> line(new char[_line_size_]);

    char* p_buff = reinterpret_cast<char*>(buffer.GetP());
    char* p_curr;
    char* p_line;

    while((count = connection.Receive(buffer, _buffer_size_, _timeout)) > 0)
    {
        p_curr = reinterpret_cast<char*>(buffer.GetP());
        p_line = line;

        if(Terminated)
        {
            SendCommandABOR(_timeout);
            return FTProtocol::eCode201;
        }

        for(;;)
        {
            while(p_curr < p_buff+count && !(*p_curr == Char::CR || *p_curr == Char::LF))
            {
                *p_line++ = *p_curr++;
            }

            if(p_curr >= p_buff+count)
            {
                // we are outside the buffer, alert
                if((count = connection.Receive(buffer, _buffer_size_, _timeout)) == 0)
                {
                   *p_line = 0;
                    goto _exit_pasv;
                }

                p_curr = p_buff;
                continue;
            }

            // skip CRLF or CR or LF
            if(*p_curr == Char::CR || *p_curr == Char::LF)
            {
                *p_line++ = *p_curr++;

                if(*p_curr == Char::CR || *p_curr == Char::LF)
                {
                    *p_line++ = *p_curr++;
                }
            }

           *p_line = 0;
            p_line = line;

            // process line
            // some unix servers send TOTAL field
            char term[16];
            PalmText::StrNCopy(term, line, 5);
            term[5] = 0;
            
            if(PalmText::StrICompare(term, "total") != 0)
            {
                _file.Write(line, 1, PalmText::StrLen(line));
            }
        }
    }

_exit_pasv:

    if(Connection.GetAvailable() > 0)
    {
        count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);
        code  = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
    }
    return code;
}

ftpcode FTPClient::GetListFirewallFree(PalmFile& _file, const char* _url, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    //
    const uint16 _attempts_ = 128;
    //
    ftpcode code;
    uint16  port = static_cast<uint16>(1024+(::TimGetSeconds()%1024)); // arbitrary

    for(uint16 i = 0; i < _attempts_; ++i)
    {
        PalmIPv4 ip(uint32(0), port);
        PalmStreamSocket listener;
        listener.SetLocalAddress(ip);
        listener.Listen();

        if((code = SendCommandTYPE(FTProtocol::eASCII, FTProtocol::eNonprint, _timeout)) != FTProtocol::eCode200)
        {
            // failed
            break;
        }

        if((code = SendCommandPORT(Connection.GetLocalAddress().GetIPv4Address(), port, _timeout)) != FTProtocol::eCode200)
        {
            // keep going
            ++port;
            continue;
        }

        FTPURL url(_url);
        _string dir = url.GetAbsPath();

        if(!dir.empty() && ((code = SendCommandCWD(dir)) < FTProtocol::eCode100 || code >= FTProtocol::eCode300))
        {
            // failed to retrive the file
            return code;
        }

        if((code = SendCommandLIST(_string())) < FTProtocol::eCode100 || code >= FTProtocol::eCode300)
        {
            // failed to retrive the file
            break;
        }

        PalmStreamSocket connection;
        listener.Accept(connection);
        connection.SetBufferSize();

        // get the list
        const uint16 _buffer_size_ = 4096;
        const uint16 _line_size_   = 1024;
        //
        int16 count;
        AutoPtrArray<byte> buffer(new byte[_buffer_size_]);
        AutoPtrArray<char> line(new char[_line_size_]);

        char* p_buff = reinterpret_cast<char*>(buffer.GetP());
        char* p_curr;
        char* p_line;

        while((count = connection.Receive(buffer, _buffer_size_, _timeout)) > 0)
        {
            p_curr = reinterpret_cast<char*>(buffer.GetP());
            p_line = line;

            if(Terminated)
            {
                SendCommandABOR(_timeout);
                return FTProtocol::eCode201;
            }

            for(;;)
            {
                while(p_curr < p_buff+count && !(*p_curr == Char::CR || *p_curr == Char::LF))
                {
                    *p_line++ = *p_curr++;
                }

                if(p_curr >= p_buff+count)
                {
                    // we are outside the buffer, alert
                    if((count = connection.Receive(buffer, _buffer_size_, _timeout)) == 0)
                    {
                       *p_line = 0;
                        goto _exit;
                    }

                    p_curr = p_buff;
                    continue;
                }

                // skip CRLF or CR or LF
                if(*p_curr == Char::CR || *p_curr == Char::LF)
                {
                    *p_line++ = *p_curr++;

                    if(*p_curr == Char::CR || *p_curr == Char::LF)
                    {
                        *p_line++ = *p_curr++;
                    }
                }

               *p_line = 0;
                p_line = line;

                // process line
                // some unix servers send TOTAL field
                char term[16];
                StrNCopy(term, line, 5);
                term[5] = 0;
            
                if(PalmText::StrICompare(term, "total") != 0)
                {
                    _file.Write(line, 1, StrLen(line));
                }
            }
        }

_exit:

        if(Connection.GetAvailable() > 0)
        {
            count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);
            code  = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
        }
        return code;
    }
    return FTProtocol::eCode0;
}

ftpcode FTPClient::GetList(const char* _filename, const char* _url, const char* _proxy, bool _passv, uint16 _timeout)
{
    palmxassert(_url != null, Error::eInvalidArg, FTPClient::XFTPClient);
    palmxassert(_filename != null, Error::eInvalidArg, FTPClient::XFTPClient);

    try
    {
        FTPURL url(_url);
        FTPClient client(url);

        PalmFile file;
    	palmxassert(file.Open(PalmOS::GetCardNumber(), _filename, sysFileTFileStream, PalmOS::GetCreatorID(), fileModeReadOnly) == errNone, Error::eOperationFailure, FTPClient::XFTPClient);

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        return client.GetList(file, _url, _passv, _timeout);
    }
    catch(...)
    {
        return FTProtocol::eCode0;
    }
}

ftpcode FTPClient::Login(const char* _username, const char* _password, const char* _account, uint16 _timeout)
{
    ftpcode code = SendCommandUSER(_username == null || _username[0] == 0 ? "anonymous" : _username, _timeout);

    if(code == FTProtocol::eCode331)
    {
        // password is required
        code = SendCommandPASS(_password == null || _password[0] == 0 ? "guest" : _password, _timeout);

        if(code == FTProtocol::eCode332)
        {
            // account is required
            code = SendCommandACCT(_account, _timeout);
        }
    }
    else if(code == FTProtocol::eCode332)
    {
        // account is required
        code = SendCommandACCT(_account, _timeout);
    }
    return code;
}

ftpcode FTPClient::SendCommandUSER(const _string& _username, uint16 _timeout)
{
    // returns:
    //  230, 530, 500, 501, 421, 331, 332
    palmxassert(!_username.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  USER <SP> <username> <CRLF>
   _string request  = "USER ";
           request += _username;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout, true);
}

ftpcode FTPClient::SendCommandPASS(const _string& _password, uint16 _timeout)
{
    // returns:
    //  230, 202, 530, 500, 501, 503, 421, 332
    palmxassert(!_password.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  PASS <SP> <password> <CRLF>
   _string request  = "PASS ";
           request += _password;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout, true);
}

ftpcode FTPClient::SendCommandACCT(const _string& _account, uint16 _timeout)
{
    // returns:
    //  230, 202, 530, 500, 501, 503, 421
    palmxassert(!_account.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  ACCT <SP> <account-information> <CRLF>
   _string request  = "ACCT ";
           request += _account;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandCWD(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  250, 500, 501, 502, 421, 530, 550
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  CWD  <SP> <pathname> <CRLF>
   _string request  = "CWD ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandCDUP(uint16 _timeout)
{
    // returns:
    //  200, 500, 501, 502, 421, 530, 550

    // send request
    //  CDUP <CRLF>
   _string request  = "CDUP";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSMNT(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  202, 250, 500, 501, 502, 421, 530, 550
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  SMNT <SP> <pathname> <CRLF>
   _string request  = "SMNT ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandQUIT(uint16 _timeout)
{
    // returns:
    //  221, 500

    // send request
    //  QUIT <CRLF>
   _string request  = "QUIT";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandREIN(uint16 _timeout)
{
    // returns:
    //  120, 220, 220, 421, 500, 502

    // send request
    //  REIN <CRLF>
   _string request  = "REIN";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandPORT(uint32 _ip, uint16 _port, uint16 _timeout)
{
    // returns:
    //  200, 500, 501, 530, 421
 
    char buffer[32];
    FTProtocol::BuildPortRequest(_ip, _port, buffer);

    // send request
    //  PORT <SP> <host-port> <CRLF>
   _string request  = "PORT ";
           request += buffer;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandPASV(PalmIPv4& _address, uint16 _timeout)
{
    // returns:
    //  227, 500, 501, 502, 421, 530

    // send request
    //  PASV <CRLF>
    const uint16 _buffer_size_ = 1024;
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    PalmOS::MemSet(buffer, _buffer_size_);

   _string request  = "PASV";
           request += Char::CRLF;

    int16 count;

    Connection.Discard(_timeout);

    if((count = Connection.Send((byte*)(request.c_str()), static_cast<uint16>(request.size()), _timeout)) != request.size())
    {
        return FTProtocol::eCode0;
    }

    count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);

    if(count == 0)
    {
        return FTProtocol::eCode0;
    }

    ftpcode code = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));

    if(code == FTProtocol::eCode227)
    {
        // syntax is as follows:
        //  227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)
        const char* p_buff = reinterpret_cast<char*>(buffer.GetP());
              char* p_curr = PalmText::StrChar(p_buff, Char::ParenLeft);

        if(p_curr == null)
        {
            // stupid server does not complient with RFC 959
            // try to work around this stuff
            p_curr = PalmText::SkipSymbols(p_curr, Char::SPTAB);

            // skip response code
            while(*p_curr != 0 && TxtCharIsDigit(*p_curr))
            {
                ++p_curr;
            }

            // skip stuff between response code and actual address
            while(*p_curr != 0 && !TxtCharIsDigit(*p_curr))
            {
                ++p_curr;
            }
        }
        else
        {
            ++p_curr; // skip '('
        }

        if(p_curr != null)
        {
            // get address
            uint16 n = 0; // number of commas
            char  ip[16];
            char* p_term = ip;

            while(*p_curr != 0)
            {
                if(*p_curr == Char::Comma)
                {
                    if(n++ == 3)
                    {
                        break;
                    }

                    *p_term++ = Char::Period;
                    ++p_curr;
                }
                else
                {
                    *p_term++ = *p_curr++;
                }
            }

            *p_term = 0;
            uint16 port = 0;

            if(*p_curr != 0)
            {
                ++p_curr;

                port = static_cast<uint16>(static_cast<uint16>(PalmText::StrAToI(p_curr)) << 8);

                while(*p_curr != 0 && TxtCharIsDigit(*p_curr))
                {
                    ++p_curr;
                }

                while(*p_curr != 0 && !TxtCharIsDigit(*p_curr))
                {
                    ++p_curr;
                }

                port += static_cast<uint16>(PalmText::StrAToI(p_curr));
            }
           _address = PalmIPv4(ip, port);
        }
    }
    return code;
}

ftpcode FTPClient::SendCommandTYPE(FTProtocol::EFileType _type, FTProtocol::EFileFormat _format, uint16 _timeout)
{
    // returns:
    //  200, 500, 501, 504, 421, 530
    char param[4];
    param[0] = _type;
    param[1] = Char::Space;
    param[2] = _format;
    param[3] = 0;

    if(_type == FTProtocol::eBinary || _type == FTProtocol::eLocal)
    {
        param[1] = 0;
    }

    // send request
    //  TYPE <SP> <type-code> <CRLF>
   _string request  = "TYPE ";
           request += param;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSTRU(FTProtocol::EDataStructure _structure, uint16 _timeout)
{
    // returns:
    //  200, 500, 501, 504, 421, 530
    char param[2];
    param[0] = _structure;
    param[1] = 0;

    // send request
    //  STRU <SP> <structure-code> <CRLF>
   _string request  = "STRU ";
           request += param;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandMODE(FTProtocol::ETransmissionMode _mode, uint16 _timeout)
{
    // returns:
    //  200, 500, 501, 504, 421, 530
    char param[2];
    param[0] = _mode;
    param[1] = 0;

    // send request
    //  MODE <SP> <mode-code> <CRLF>
   _string request  = "MODE ";
           request += param;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandRETR(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 450, 550, 500, 501, 421, 530
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  RETR <SP> <pathname> <CRLF>
   _string request  = "RETR ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSTOR(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 551, 552, 532, 450, 452, 553, 500, 501, 421, 530
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  STOR <SP> <pathname> <CRLF>
   _string request  = "STOR ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSTOU(uint16 _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 551, 552, 532, 450, 452, 553, 500, 501, 421, 530

    // send request
    //  STOU <CRLF>
   _string request  = "STOU";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandAPPE(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 551, 552, 532, 450, 452, 553, 500, 501, 421, 530
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  APPE <SP> <pathname> <CRLF>
    //
   _string request  = "APPE ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandALLO(uint32 _size, uint16 _timeout)
{
    // returns:
    //  200, 202, 500, 501, 504, 421, 530
    palmxassert(_size > 0, Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  ALLO <SP> <decimal-integer>
    //       [<SP> R <SP> <decimal-integer>] <CRLF>
    char term[16];
    PalmText::StrPrintf(term, "%ld", _size);

   _string request  = "ALLO ";
           request += term;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandREST(uint32 _marker, uint16 _timeout)
{
    // returns:
    //  500, 501, 502, 421, 530, 350

    // send request
    //  REST <SP> <marker> <CRLF>
    char term[16];
    PalmText::StrPrintf(term, "%ld", _marker);

   _string request  = "REST ";
           request += term;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandRNFR(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  450, 550, 500, 501, 502, 421, 530, 350
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  RNFR <SP> <pathname> <CRLF>
   _string request  = "RNFR ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandRNTO(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  250, 532, 553, 500, 501, 502, 503, 421, 530
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  RNTO <SP> <pathname> <CRLF>
   _string request  = "RNTO ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandABOR(uint16 _timeout)
{
    // returns:
    //  225, 226, 500, 501, 502, 421

    // send request
    //  ABOR <CRLF>
   _string request  = "ABOR";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandDELE(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  250, 450, 550, 500, 501, 502, 421, 530
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  DELE <SP> <pathname> <CRLF>
   _string request  = "DELE ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandRMD(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  250, 500, 501, 502, 421, 530, 550
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  RMD <SP> <pathname> <CRLF>
   _string request  = "RMD ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandMKD(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  257, 500, 501, 502, 421, 530, 550
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  MKD <SP> <pathname> <CRLF>
   _string request  = "MKD ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandPWD(uint16 _timeout)
{
    // returns:
    //  257, 500, 501, 502, 421, 550

    // send request
    //  PWD <CRLF>
   _string request  = "PWD";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandLIST(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  125, 150, 226, 250, 425, 426, 451, 450, 500, 501, 502, 421, 530

    // send request
    //  LIST <SP> <pathname> <CRLF>
   _string request = "LIST";

    if(!_pathname.empty())
    {
        request += Char::Space;
        request += _pathname;
    }
    request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandNLST(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  125, 150, 226, 250, 425, 426, 451, 450, 500, 501, 502, 421, 530
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  NLST <SP> <pathname> <CRLF>
   _string request  = "NLST ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSITE(const _string& _str, uint16 _timeout)
{
    // returns:
    //  200, 202, 500, 501, 530
    palmxassert(!_str.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  SITE <SP> <string> <CRLF>
   _string request  = "SITE ";
           request += _str;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSYST(uint16 _timeout)
{
    // returns:
    //  215, 500, 501, 502, 421

    // send request
    //  SYST <CRLF>
   _string request  = "SYST";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSTAT(const _string& _pathname, uint16 _timeout)
{
    // returns:
    //  211, 212, 213, 450, 500, 501, 502, 421, 530
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  STAT <SP> <string> <CRLF>
   _string request  = "STAT ";
           request += _pathname;
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::SendCommandSIZE(const _string& _pathname, fsize_t_& _size, uint16 _timeout)
{
    // returns:
    //
    palmxassert(!_pathname.empty(), Error::eInvalidArg, FTPClient::XFTPClient);

    // send request
    //  SIZE <SP> <pathname> <CRLF>
   _string request  = "SIZE ";
           request += _pathname;
           request += Char::CRLF;

    char buffer[128];
    PalmOS::MemSet(buffer, sizeof(buffer));

    int16 count;

    Connection.Discard(_timeout);

    if((count = Connection.Send((byte*)(request.c_str()), static_cast<uint16>(request.size()), _timeout)) != request.size())
    {
        return FTProtocol::eCode0;
    }

    count = Connection.ReceiveLine((byte*)(buffer), sizeof(buffer), _timeout);

    if(count == 0)
    {
        return FTProtocol::eCode0;
    }
    return FTProtocol::GetResourceSize(buffer, _size);
}

ftpcode FTPClient::SendCommandHELP(const _string&, uint32)
{
    // not relevant
    return FTProtocol::eCode0;
}

ftpcode FTPClient::SendCommandNOOP(uint16 _timeout)
{
    // returns:
    //  200, 500 421

    // send request
    //  NOOP <CRLF>
   _string request  = "NOOP";
           request += Char::CRLF;
    return ProcessRequest(request.c_str(), _timeout);
}

ftpcode FTPClient::ProcessRequest(const char* _request, uint16 _timeout, bool _eat_multiline)
{
    uint16 len;
    palmxassert(_request != null, Error::eInvalidArg, FTPClient::XFTPClient);
    palmxassert((len = static_cast<uint16>(PalmText::StrLen(_request))) > 0, Error::eInvalidArg, FTPClient::XFTPClient);
    //
    const uint16 _buffer_size_ = 1024;
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    PalmOS::MemSet(buffer, _buffer_size_);

    int16 count;

    Connection.Discard(_timeout);

    if((count = Connection.Send((byte*)(_request), len, _timeout)) != len)
    {
        return FTProtocol::eCode0;
    }

    // skip greetings (response) from the server
    do
    {
        count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);
    }
    while(_eat_multiline && FTProtocol::IsMultiLineResponse(reinterpret_cast<char*>(buffer.GetP())));// && Connection.GetAvailable() > 0);

    if(count == 0)
    {
        return FTProtocol::eCode0;
    }
    return FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
}
////////////////////////////////////////////////////////////////////////////////////////
// class XFTPClient
// ----- ----------
void FTPClient::XFTPClient::LoadErrorDescriptions()
{
    // base class
    PalmError::LoadErrorDescriptions();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__


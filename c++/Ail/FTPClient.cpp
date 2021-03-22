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

#ifndef __FTP_CLIENT_INC__
#   include <FTPClient.inc>
#endif

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
    if(!SOCKSServer.GetURL().IsEmpty())
    {
        //
        const ushort _timeout_ = 20; // secs
        //

        // RFC1928/RFC1929
        // connect through SOCKS server
        IPv4Address address(Resource);
        IPv4Address socks_address(SOCKSServer.GetHost(), SOCKSServer.GetPort());
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
            memset(&request, 0, sizeof(request));

            uint ip = address.GetIPv4Address();
            ushort port = address.GetPort();

            request[0] = 0x04; // version SOCKS4
            request[1] = 0x01; // connect
            memcpy(&request[2], &port, 2);
            memcpy(&request[4], &ip, 4);

            uint count = Connection.Send(request, sizeof(request), _timeout_);
            memset(&request, 0, sizeof(request));
            count = Connection.Receive(request, sizeof(request), _timeout_);

            if(count == 0 || request[1] != 90)
            {
                return FTProtocol::Code0;
            }
#ifdef _DEBUG
            // just for fun ! ...
            memcpy(&port, &request[2], 2);
            memcpy(&ip, &request[4], 4);

            if(ip == 0)
            {
                // SOCKS server is not multi-homed host
                ip = socks_address.GetIPv4Address();
            }
            //
            const ushort _port_mask_ = 0x00FF;
            const uint   _ip_mask_   = 0xFF000000;
            //
            int x = 1;
            bool little_endian = (*(char*)&x) == 1;

            if(little_endian)
            {
                // convert from the network order back to the host order
                port = static_cast<ushort>(((port >> 8) & _port_mask_)|((port & _port_mask_) << 8));

                uint tmp;
                uint* p = &ip;

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
            b[2] = Password.IsEmpty() == null ? 0x00 : 0x02; // gss-api - '01'; username/password - '02'
            b[3] = 0x00;

            uint count = Connection.Send(b, 3, _timeout_);
            b[0] = b[1] = b[2] = 0;
            count = Connection.Receive(b, sizeof(b), _timeout_);

            // X'00' NO AUTHENTICATION REQUIRED
            // X'01' GSSAPI
            // X'02' USERNAME/PASSWORD
            // X'03' to X'7F' IANA ASSIGNED
            // X'80' to X'FE' RESERVED FOR PRIVATE METHODS
            // X'FF' NO ACCEPTABLE METHODS
            if(count == 0 || b[0] != 0x05 || b[1] == 0xFF)
            {
                return FTProtocol::Code0;
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

                up[0]  = 0x01;
                up[1]  = StrLen(Username);
                memcpy(&up[2], Username, up[1]);

                up[256] = StrLen(Password);
                memcpy(&up[257], Password, up[256]);

                uint count = Connection.Send(up, sizeof(up), _timeout_);
                memset(&up, 0, sizeof(up));
                count = Connection.Receive(up, sizeof(up), _timeout_);

                // a STATUS field of X'00' indicates success. If the server returns a
                // `failure' (STATUS value other than X'00') status, it MUST close the connection.
                if(up[1] != 0)
                {
                    return FTProtocol::Code0;
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

            count = Connection.Send(request, sizeof(request), _timeout_);
            memset(&request, 0, sizeof(request));
            count = Connection.Receive(request, sizeof(request), _timeout_);

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
                return FTProtocol::Code0;
            }
        }
    }
    else if(!ProxyServer.GetURL().IsEmpty())
    {
        // connect through proxy server
        IPv4Address address(ProxyServer.GetHost(), ProxyServer.GetPort());
        Connection.SetRemoteAddress(address);
        Connection.Connect();
    }
    else
    {
        // direct connection
        IPv4Address address(Resource);
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
        //
        const ushort _buffer_size_ = 1024;
        //
        AutoPtrArray<byte> buffer = new byte[_buffer_size_];
        InitMemory(buffer, _buffer_size_);

        SendCommandQUIT();
        Connection.ReceiveLine(buffer.GetP(), _buffer_size_, FTPClient::Timeout);
        ftpcode code = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
        Connection.Disconnect();
        return code;
    }
    return FTProtocol::Code0;
}

ftpcode FTPClient::CheckLink(bool _passv, uint _timeout)
{
    File<> file;
    fsize_t_ size = -1;
    return GetResource(file, null, 0, size, _passv, _timeout);
}

ftpcode FTPClient::CheckLink(const tchar* _url, const tchar* _proxy, bool _passv, uint _timeout)
{
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
        return FTProtocol::Code0;
    }
}

ftpcode FTPClient::GetGreetings()
{
    //
    const ushort _buffer_size_ = 1024;
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    InitMemory(buffer, _buffer_size_);

    // get greetings ...
    do
    {
        uint count = Connection.ReceiveLine(buffer, _buffer_size_, FTPClient::Timeout);
    }
    while(FTProtocol::IsMultiLineResponse((char*)buffer.GetP()));

    return FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
}

ftpcode FTPClient::GetSize(fsize_t_& _size, bool _passv, uint _timeout)
{
    File<> file;
   _size = -1;
    return GetResource(file, null, 0, _size, _passv, _timeout);
}

ftpcode FTPClient::GetSize(fsize_t_& _size, const tchar* _url, const tchar* _proxy, bool _passv, uint _timeout)
{
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
        return FTProtocol::Code0;
    }
}

ftpcode FTPClient::GetResource(File<>& _file, const tchar* _url, fpos_t_ _pos, fpos_t_& _size, bool _passv, uint _timeout)
{
    // phase I (login)
    if(!Connection.IsConnected())
    {
        Connect();
    }

    String<> username = GetUsername();
    String<> password = GetPassword();
    String<> account  = GetAccount();

    if(username.IsEmpty())
    {
        username = Resource.GetUsername();
    }

    if(password.IsEmpty())
    {
        password = Resource.GetPassword();
    }

    ftpcode code;

    if((code = Login(username, password, account)) != FTProtocol::Code230)
    {
        return code;
    }

    // phase II (process)
    //  firewall-free case and firewall is present
    //  see RFC 1579 (firewall-friendly ftp)
    if(_passv)
    {
        // firewall-friendly
        code = GetResourceThroughFirewall(_file, _url == null ? Resource : _url, _pos, _size, _timeout);
    }
    else
    {
        // firewall-free
        code = GetResourceFirewallFree(_file, _url == null ? Resource : _url, _pos, _size, _timeout);
    }
    return code;
}

ftpcode FTPClient::GetResourceThroughFirewall(File<>& _file, const tchar* _url, fpos_t_ _pos, fsize_t_& _size, uint _timeout)
{
    xassertr(_url != null, FTProtocol::Code0);
    //
    // firewall case
    IPv4Address ip;
    ftpcode code = SendCommandPASV(ip);

    if(code != FTProtocol::Code227)
    {
        // failed
        return code;
    }

    if((code = SendCommandTYPE(FTProtocol::ASCII, FTProtocol::Nonprint, _timeout)) != FTProtocol::Code200)
    {
        return code;
    }

    FTPURL url(_url);
    StreamSocket connection;
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
        if((code = SendCommandREST(static_cast<uint>(_pos))) == FTProtocol::Code350)
        {
            _file.SetPosition(_pos);
        }
    }

    if((code = SendCommandRETR(url.GetAbsPath(), _timeout)) < FTProtocol::Code100 || code >= FTProtocol::Code300)
    {
        // failed to retrive the file
        return code;
    }
    //
    const ushort _buffer_size_ = 1024;
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    InitMemory(buffer, _buffer_size_);

    uint count;
    uint64 size = 0;

    while((count = connection.Receive(buffer, _buffer_size_, _timeout)) > 0)
    {
       _file.Write(buffer, count);
        size += count;

        if(Terminated)
        {
            SendCommandABOR(_timeout);
            return FTProtocol::Code201;
        }
    }

    if(Connection.GetAvailable() > 0)
    {
        count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);
        code  = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
    }
    return code;
}

ftpcode FTPClient::GetResourceFirewallFree(File<>& _file, const tchar* _url, fpos_t_ _pos, fsize_t_& _size, uint _timeout)
{
    xassertr(_url != null, FTProtocol::Code0);
    //
    const short _attempts_ = 128;
    //
    ftpcode code;
    ushort  port = static_cast<ushort>(1024+(time(null)%1024)); // arbitrary

    for(short i = 0; i < _attempts_; ++i)
    {
        IPv4Address ip(uint(0), port);
        StreamSocket listener;
        listener.SetLocalAddress(ip);
        listener.Listen();

        if((code = SendCommandTYPE(FTProtocol::ASCII, FTProtocol::Nonprint, _timeout)) != FTProtocol::Code200)
        {
            // failed
            break;
        }

        if((code = SendCommandPORT(Connection.GetLocalAddress().GetIPv4Address(), port, _timeout)) != FTProtocol::Code200)
        {
            // keep going
            ++port;
            continue;
        }

        if((code = SendCommandTYPE(FTProtocol::Binary, FTProtocol::Nonprint, _timeout)) != FTProtocol::Code200)
        {
            // failed
            break;
        }

	    if(_pos > 0)
        {
            if((code = SendCommandREST(static_cast<uint>(_pos))) == FTProtocol::Code350)
            {
                _file.SetPosition(_pos);
            }
        }

        FTPURL url(_url);

        if(_size == -1)
        {
            // just grab size
            return SendCommandSIZE(url.GetAbsPath(), _size, _timeout);
        }

        if((code = SendCommandRETR(url.GetAbsPath(), _timeout)) < FTProtocol::Code100 || code >= FTProtocol::Code300)
        {
            // failed to retrive the file
            break;
        }

        StreamSocket connection;
        listener.Accept(connection);
        connection.SetBufferSize();
        //
        const ushort _buffer_size_ = 1024;
        //
        AutoPtrArray<byte> buffer = new byte[_buffer_size_];
        InitMemory(buffer, _buffer_size_);

        uint count;
        uint64 size = 0;

        while((count = connection.Receive(buffer, _buffer_size_, _timeout)) > 0)
        {
           _file.Write(buffer, count);
            size += count;

            if(Terminated)
            {
                SendCommandABOR(_timeout);
                return FTProtocol::Code201;
            }
        }

        if(Connection.GetAvailable() > 0)
        {
            count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);
            code  = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
        }
        return code;
    }
    return FTProtocol::Code0;
}

ftpcode FTPClient::GetResource(const tchar* _filename, const tchar* _url, fpos_t_ _pos, const tchar* _proxy, bool _passv, uint _timeout)
{
    try
    {
        fsize_t_ size = 0;

        FTPURL url(_url);
        FTPClient client(url);
        File<> file(_filename, File<>::eCreateNew|File<>::eAccessReadWrite|File<>::eShareRead);

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        return client.GetResource(file, _url, _pos, size, _passv, _timeout);
    }
    catch(...)
    {
        return FTProtocol::Code0;
    }
}

ftpcode FTPClient::GetList(File<>& _file, const tchar* _url, bool _passv, uint _timeout)
{
    // phase I (login)
    if(!Connection.IsConnected())
    {
        Connect();
    }

    String<> username = GetUsername();
    String<> password = GetPassword();
    String<> account  = GetAccount();

    if(username.IsEmpty())
    {
        username = Resource.GetUsername();
    }

    if(password.IsEmpty())
    {
        password = Resource.GetPassword();
    }

    ftpcode code;

    if((code = Login(username, password, account)) != FTProtocol::Code230)
    {
        return code;
    }

    // phase II (process)
    //  firewall-free case and firewall is present
    //  see RFC 1579 (firewall-friendly ftp)
    if(_passv)
    {
        // firewall-friendly
        code = GetListThroughFirewall(_file, _url == null ? Resource : _url);
    }
    else
    {
        // firewall-free
        code = GetListFirewallFree(_file, _url == null ? Resource : _url);
    }
    return code;
}

ftpcode FTPClient::GetListThroughFirewall(File<>& _file, const tchar* _url, uint _timeout)
{
    xassertr(_url != null, FTProtocol::Code0);
    //
    IPv4Address ip;
    ftpcode code = SendCommandPASV(ip);

    if(code != FTProtocol::Code227)
    {
        // failed
        return code;
    }

    if((code = SendCommandTYPE(FTProtocol::ASCII, FTProtocol::Nonprint, _timeout)) != FTProtocol::Code200)
    {
        // failed
        return code;
    }

    FTPURL url(_url);
    StreamSocket connection;
    connection.SetRemoteAddress(ip);
    connection.Connect();
    connection.SetBufferSize();

    if(!connection.IsConnected())
    {
        return FTProtocol::Code0;
    }

    String<> dir = url.GetAbsPath();

    if(!dir.IsEmpty() && ((code = SendCommandCWD(dir)) < FTProtocol::Code100 || code >= FTProtocol::Code300))
    {
        // failed to retrive the file
        return code;
    }

    if((code = SendCommandLIST(String<>())) < FTProtocol::Code100 || code >= FTProtocol::Code300)
    {
        // failed to retrive the file
        return code;
    }

    // get the list
    const ushort _buffer_size_ = 4096;
    const ushort _line_size_   = 1024;
    //
    ushort count;
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
            return FTProtocol::Code201;
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
            StrNCopy(term, line, 5);
            term[5] = 0;
            
            if(StrICompare(term, "total") != 0)
            {
                _file.Write(line, StrLen(line));
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

ftpcode FTPClient::GetListFirewallFree(File<>& _file, const tchar* _url, uint _timeout)
{
    xassertr(_url != null, FTProtocol::Code0);
    //
    const short _attempts_ = 128;
    //
    ftpcode code;
    ushort  port = static_cast<ushort>(1024+(time(null)%1024)); // arbitrary

    for(short i = 0; i < _attempts_; ++i)
    {
        IPv4Address ip(uint(0), port);
        StreamSocket listener;
        listener.SetLocalAddress(ip);
        listener.Listen();

        if((code = SendCommandTYPE(FTProtocol::ASCII, FTProtocol::Nonprint, _timeout)) != FTProtocol::Code200)
        {
            // failed
            break;
        }

        if((code = SendCommandPORT(Connection.GetLocalAddress().GetIPv4Address(), port, _timeout)) != FTProtocol::Code200)
        {
            // keep going
            ++port;
            continue;
        }

        FTPURL url(_url);
        String<> dir = url.GetAbsPath();

        if(!dir.IsEmpty() && ((code = SendCommandCWD(dir)) < FTProtocol::Code100 || code >= FTProtocol::Code300))
        {
            // failed to retrive the file
            return code;
        }

        if((code = SendCommandLIST(String<>())) < FTProtocol::Code100 || code >= FTProtocol::Code300)
        {
            // failed to retrive the file
            break;
        }

        StreamSocket connection;
        listener.Accept(connection);
        connection.SetBufferSize();

        // get the list
        const ushort _buffer_size_ = 4096;
        const ushort _line_size_   = 1024;
        //
        ushort count;
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
                return FTProtocol::Code201;
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
            
                if(StrICompare(term, "total") != 0)
                {
                    _file.Write(line, StrLen(line));
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
    return FTProtocol::Code0;
}

ftpcode FTPClient::GetList(const tchar* _filename, const tchar* _url, const tchar* _proxy, bool _passv, uint _timeout)
{
    try
    {
        FTPURL url(_url);
        FTPClient client(url);
        File<> file(_filename, File<>::eCreateNew|File<>::eAccessReadWrite|File<>::eShareRead);

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        return client.GetList(file, _url, _passv, _timeout);
    }
    catch(...)
    {
        return FTProtocol::Code0;
    }
}

ftpcode FTPClient::Login(const char* _username, const char* _password, const char* _account, uint _timeout)
{
    xassertr(Connection.IsConnected(), FTProtocol::Code0);
    //
    ftpcode code = SendCommandUSER(_username == null || _username[0] == 0 ? "anonymous" : _username, _timeout);

    if(code == FTProtocol::Code331)
    {
        // password is required
        code = SendCommandPASS(_password == null || _password[0] == 0 ? "guest" : _password, _timeout);

        if(code == FTProtocol::Code332)
        {
            // account is required
            code = SendCommandACCT(_account, _timeout);
        }
    }
    else if(code == FTProtocol::Code332)
    {
        // account is required
        code = SendCommandACCT(_account, _timeout);
    }
    return code;
}

ftpcode FTPClient::SendCommandUSER(const String<>& _username, uint _timeout)
{
    // returns:
    //  230, 530, 500, 501, 421, 331, 332
    xassertr(!_username.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  USER <SP> <username> <CRLF>
    String<> request  = "USER ";
             request += _username;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout, true);
}

ftpcode FTPClient::SendCommandPASS(const String<>& _password, uint _timeout)
{
    // returns:
    //  230, 202, 530, 500, 501, 503, 421, 332
    xassertr(!_password.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  PASS <SP> <password> <CRLF>
    String<> request  = "PASS ";
             request += _password;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout, true);
}

ftpcode FTPClient::SendCommandACCT(const String<>& _account, uint _timeout)
{
    // returns:
    //  230, 202, 530, 500, 501, 503, 421
    xassertr(!_account.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  ACCT <SP> <account-information> <CRLF>
    String<> request  = "ACCT ";
             request += _account;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandCWD(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  250, 500, 501, 502, 421, 530, 550
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  CWD  <SP> <pathname> <CRLF>
    String<> request  = "CWD ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandCDUP(uint _timeout)
{
    // returns:
    //  200, 500, 501, 502, 421, 530, 550
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  CDUP <CRLF>
    String<> request  = "CDUP";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSMNT(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  202, 250, 500, 501, 502, 421, 530, 550
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  SMNT <SP> <pathname> <CRLF>
    String<> request  = "SMNT ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandQUIT(uint _timeout)
{
    // returns:
    //  221, 500
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  QUIT <CRLF>
    const ushort _buffer_size_ = 1024;
    //
    String<> request  = "QUIT";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandREIN(uint _timeout)
{
    // returns:
    //  120, 220, 220, 421, 500, 502
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  REIN <CRLF>
    String<> request  = "REIN";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandPORT(uint _ip, ushort _port, uint _timeout)
{
    // returns:
    //  200, 500, 501, 530, 421
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    char buffer[32];
    FTProtocol::BuildPortRequest(_ip, _port, buffer);

    // send request
    //  PORT <SP> <host-port> <CRLF>
    String<> request  = "PORT ";
             request += buffer;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandPASV(IPv4Address& _address, uint _timeout)
{
    // returns:
    //  227, 500, 501, 502, 421, 530
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  PASV <CRLF>
    const ushort _buffer_size_ = 1024;
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    InitMemory(buffer, _buffer_size_);

    String<> request  = "PASV";
             request += Char::CRLF;

    uint count;

    Connection.Discard(_timeout);

    if((count = Connection.Send((byte*)request.GetData(), request.GetCount(), _timeout)) != request.GetCount())
    {
        return FTProtocol::Code0;
    }

    count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);

    if(count == 0)
    {
        return FTProtocol::Code0;
    }

    ftpcode code = FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));

    if(code == 227)
    {
        // syntax is as follows:
        //  227 Entering Passive Mode (h1,h2,h3,h4,p1,p2)
        const char* p_buff = reinterpret_cast<char*>(buffer.GetP());
              char* p_curr = StrChar(p_buff, Char::ParenLeft);

        if(p_curr == null)
        {
            // stupid server does not complient with RFC 959
            // try to work around this stuff
            p_curr = SkipSymbols(p_curr, Char::SPTAB);

            // skip response code
            while(*p_curr != 0 && isdigit(*p_curr))
            {
                ++p_curr;
            }

            // skip stuff between response code and actual address
            while(*p_curr != 0 && !isdigit(*p_curr))
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
            short n = 0; // number of commas
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
            ushort port = 0;

            if(*p_curr != 0)
            {
                ++p_curr;

                port = static_cast<ushort>(StrToInteger(p_curr)) << 8;

                while(*p_curr != 0 && isdigit(*p_curr))
                {
                    ++p_curr;
                }

                while(*p_curr != 0 && !isdigit(*p_curr))
                {
                    ++p_curr;
                }

                port += static_cast<ushort>(StrToInteger(p_curr));
            }
           _address = IPv4Address(ip, port);
        }
    }
    return code;
}

ftpcode FTPClient::SendCommandTYPE(FTProtocol::EFileType _type, FTProtocol::EFileFormat _format, uint _timeout)
{
    // returns:
    //  200, 500, 501, 504, 421, 530
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    char param[4];
    param[0] = _type;
    param[1] = Char::Space;
    param[2] = _format;
    param[3] = 0;

    if(_type == FTProtocol::Binary || _type == FTProtocol::Local)
    {
        param[1] = 0;
    }

    // send request
    //  TYPE <SP> <type-code> <CRLF>
    String<> request  = "TYPE ";
             request += param;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSTRU(FTProtocol::EDataStructure _structure, uint _timeout)
{
    // returns:
    //  200, 500, 501, 504, 421, 530
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    char param[2];
    param[0] = _structure;
    param[1] = 0;

    // send request
    //  STRU <SP> <structure-code> <CRLF>
    String<> request  = "STRU ";
             request += param;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandMODE(FTProtocol::ETransmissionMode _mode, uint _timeout)
{
    // returns:
    //  200, 500, 501, 504, 421, 530
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    char param[2];
    param[0] = _mode;
    param[1] = 0;

    // send request
    //  MODE <SP> <mode-code> <CRLF>
    String<> request  = "MODE ";
             request += param;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandRETR(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 450, 550, 500, 501, 421, 530
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  RETR <SP> <pathname> <CRLF>
    String<> request  = "RETR ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSTOR(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 551, 552, 532, 450, 452, 553, 500, 501, 421, 530
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  STOR <SP> <pathname> <CRLF>
    String<> request  = "STOR ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSTOU(uint _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 551, 552, 532, 450, 452, 553, 500, 501, 421, 530
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  STOU <CRLF>
    String<> request  = "STOU";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandAPPE(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  125, 150, (110), 226, 250, 425, 426, 451, 551, 552, 532, 450, 452, 553, 500, 501, 421, 530
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  APPE <SP> <pathname> <CRLF>
    const ushort _buffer_size_ = 1024;
    //
    String<> request  = "APPE ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandALLO(uint _size, uint _timeout)
{
    // returns:
    //  200, 202, 500, 501, 504, 421, 530
    xassertr(_size > 0, FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  ALLO <SP> <decimal-integer>
    //       [<SP> R <SP> <decimal-integer>] <CRLF>
    char term[16];
    sprintf(term, "%ld", _size);

    String<> request  = "ALLO ";
             request += term;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandREST(uint _marker, uint _timeout)
{
    // returns:
    //  500, 501, 502, 421, 530, 350
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  REST <SP> <marker> <CRLF>
    char term[16];
    sprintf(term, "%ld", _marker);

    String<> request  = "REST ";
             request += term;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandRNFR(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  450, 550, 500, 501, 502, 421, 530, 350
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  RNFR <SP> <pathname> <CRLF>
    String<> request  = "RNFR ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandRNTO(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  250, 532, 553, 500, 501, 502, 503, 421, 530
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  RNTO <SP> <pathname> <CRLF>
    String<> request  = "RNTO ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandABOR(uint _timeout)
{
    // returns:
    //  225, 226, 500, 501, 502, 421
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  ABOR <CRLF>
    String<> request  = "ABOR";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandDELE(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  250, 450, 550, 500, 501, 502, 421, 530
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  DELE <SP> <pathname> <CRLF>
    String<> request  = "DELE ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandRMD(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  250, 500, 501, 502, 421, 530, 550
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  RMD <SP> <pathname> <CRLF>
    String<> request  = "RMD ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandMKD(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  257, 500, 501, 502, 421, 530, 550
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  MKD <SP> <pathname> <CRLF>
    String<> request  = "MKD ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandPWD(uint _timeout)
{
    // returns:
    //  257, 500, 501, 502, 421, 550
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  PWD <CRLF>
    String<> request  = "PWD";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandLIST(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  125, 150, 226, 250, 425, 426, 451, 450, 500, 501, 502, 421, 530
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  LIST <SP> <pathname> <CRLF>
    String<> request = "LIST";

    if(!_pathname.IsEmpty())
    {
        request += Char::Space;
        request += _pathname;
    }
    request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandNLST(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  125, 150, 226, 250, 425, 426, 451, 450, 500, 501, 502, 421, 530
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  NLST <SP> <pathname> <CRLF>
    String<> request  = "NLST ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSITE(const String<>& _string, uint _timeout)
{
    // returns:
    //  200, 202, 500, 501, 530
    xassertr(!_string.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  SITE <SP> <string> <CRLF>
    String<> request  = "SITE ";
             request += _string;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSYST(uint _timeout)
{
    // returns:
    //  215, 500, 501, 502, 421
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  SYST <CRLF>
    String<> request  = "SYST";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSTAT(const String<>& _pathname, uint _timeout)
{
    // returns:
    //  211, 212, 213, 450, 500, 501, 502, 421, 530
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  STAT <SP> <string> <CRLF>
    String<> request  = "STAT ";
             request += _pathname;
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::SendCommandSIZE(const String<>& _pathname, fsize_t_& _size, uint _timeout)
{
    // returns:
    //
    xassertr(!_pathname.IsEmpty(), FTProtocol::Code0);
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  SIZE <SP> <pathname> <CRLF>
    String<> request  = "SIZE ";
             request += _pathname;
             request += Char::CRLF;

    //
    const ushort _buffer_size_ = 128;
    //
    AutoPtrArray<char> buffer = new char[_buffer_size_];
    InitMemory(buffer, _buffer_size_);

    uint count;

    Connection.Discard(_timeout);

    if((count = Connection.Send((byte*)request.GetData(), request.GetCount(), _timeout)) != request.GetCount())
    {
        return FTProtocol::Code0;
    }

    count = Connection.ReceiveLine((byte*)buffer.GetP(), _buffer_size_, _timeout);

    if(count == 0)
    {
        return FTProtocol::Code0;
    }
    return FTProtocol::GetResourceSize(buffer, _size);
}

ftpcode FTPClient::SendCommandHELP(const String<>&, uint)
{
    // not relevant
    return FTProtocol::Code0;
}

ftpcode FTPClient::SendCommandNOOP(uint _timeout)
{
    // returns:
    //  200, 500 421
    xassertr(Connection.IsConnected(), FTProtocol::Code0);

    // send request
    //  NOOP <CRLF>
    String<> request  = "NOOP";
             request += Char::CRLF;
    return ProcessRequest(request.GetData(), _timeout);
}

ftpcode FTPClient::ProcessRequest(const char* _request, uint _timeout, bool _eat_multiline)
{
    uint len;
    xassertr(_request != null, FTProtocol::Code0);
    xassertr((len = StrLen(_request)) > 0, FTProtocol::Code0);
    //
    const ushort _buffer_size_ = 1024;
    //
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];
    InitMemory(buffer, _buffer_size_);

    uint count;

    Connection.Discard(_timeout);

    if((count = Connection.Send((byte*)_request, len, _timeout)) != len)
    {
        return FTProtocol::Code0;
    }

    // skip stupid greetings from the server
    do
    {
        count = Connection.ReceiveLine(buffer, _buffer_size_, _timeout);
    }
    while(_eat_multiline && FTProtocol::IsMultiLineResponse((char*)buffer.GetP()));// && Connection.GetAvailable() > 0);

    if(count == 0)
    {
        return FTProtocol::Code0;
    }
    return FTProtocol::GetResponseCode(reinterpret_cast<char*>(buffer.GetP()));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

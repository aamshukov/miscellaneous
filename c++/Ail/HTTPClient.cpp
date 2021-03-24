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

#ifndef __HTTP_CLIENT_INC__
#   include <HTTPClient.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPClient
// ----- ----------
HTTPClient::HTTPClient(const HTTPURL& _url) : Resource(_url), Terminated(false), Filter(null), SocksVersion(4)
{
}

HTTPClient::~HTTPClient()
{
    Connection.Disconnect();
}

void HTTPClient::Connect()
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
                return;
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
            b[2] = Password == null ? 0x00 : 0x02; // gss-api - '01'; username/password - '02'
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
                return;
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
}

void HTTPClient::Disconnect()
{
    Connection.Disconnect();
}

httpcode HTTPClient::CheckLink(HTTProtocol::HTTPContext& _context, uint _timeout)
{
    File<> file;
    return GetResource(file, _context, true, _timeout);
}

httpcode HTTPClient::CheckLink(const tchar* _url, const tchar* _proxy, const tchar* _socks, uint _timeout)
{
    try
    {
        HTTPURL url(_url);
        HTTPClient client(url);
        HTTProtocol::HTTPContext context;

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        else if(_socks != null)
        {
            client.SetSOCKSServer(_socks);
        }
        return client.CheckLink(context, _timeout);
    }
    catch(...)
    {
        return HTTProtocol::Code0;
    }
}

httpcode HTTPClient::GetResource(File<>& _file, HTTProtocol::HTTPContext& _context, bool _check, uint _timeout)
{
    //
    const ushort _line_size_   = 1024;
    const ushort _buffer_size_ = 4096;
    //
    AutoPtrArray<byte> line = new byte[_line_size_];
    AutoPtrArray<byte> buffer = new byte[_buffer_size_];

    // build request:
    //  Request =  Request-line *(general header request header) CRLF CRLF
    //  Request-line = Method SP Request-URI SP http-version CRLF
    //  if we have proxy the Request-URI should be in absoluteURI form
    const char* _delim_        = " \r\n\t";
    const char* _http_version_ = " HTTP/1.1";
    const char* _crlf_         = "\r\n";
    const char* _http_host_    = "Host: ";
    const char* _http_head_    = "HEAD ";
    const char* _http_get_     = "GET ";
    const char* _http_date_    = "Last-Modified:";
    const char* _http_location_= "Location:";
    //
_start:

    if(!Connection.IsConnected())
    {
        Connect();
    }

    String<> request;
    request = _check ? _http_head_ : _http_get_;

    if(ProxyServer.GetURL().IsEmpty())
    {
        request += '/';
        request += Resource.GetPath();
        request += Resource.GetQuery();
     // referer is unknown
    }
    else
    {
        request += Resource.GetURL();
     // referer is unknown
    }

    request += _http_version_;
    request += _crlf_;
    request += _http_host_;
    request += Resource.GetHost();
    request += _crlf_;
    request += "User-Agent: ";
    request += HTTProtocol::GetUserAgentField();
    request += _crlf_;
    request += "Accept: */*";
    request += _crlf_;
    request += "Accept-Language: en; *";
    request += _crlf_;

    if(!ProxyServer.GetURL().IsEmpty())
    {
        request += "Proxy-Connection: keep-alive";
        request += _crlf_;
    }

    request += _context.Request; // if available
    request += _crlf_;
    //
    uint count_read;
    uint count_write;

    if((count_write = Connection.Send((byte*)(request.GetData()), request.GetCount(), _timeout)) != request.GetCount() || count_write == SOCKET_ERROR)
    {
        return HTTProtocol::Code0;
    }

    // receive & parse response:
    //  response = Status-line *(general header request header) CRLF CRLF [message-body]
    //  Status-line = http-version SP Status-code SP reason-phrase CRLF
    InitMemory(buffer, _buffer_size_);
    if((count_read = Connection.Receive(buffer, _buffer_size_, _timeout)) == 0 || count_read == SOCKET_ERROR)
    {
        return HTTProtocol::Code0;
    }

    // check status code
    byte*    p_line = line;
    byte*    p_buff = buffer;
    byte*    p_curr = reinterpret_cast<byte*>(HTTProtocol::GetLine(reinterpret_cast<char*>(p_buff), (char*)line.GetP()));
    httpcode code   = HTTProtocol::GetResponseCode(reinterpret_cast<char*>(line.GetP()));

    if(code == HTTProtocol::Code100)
    {
        // "Continue", just discard this response and try again
        InitMemory(buffer, _buffer_size_);
        if((count_read = Connection.Receive(buffer, _buffer_size_, _timeout)) == 0)
        {
            return code;
        }

        p_line = line;
        p_buff = buffer;
        p_curr = reinterpret_cast<byte*>(HTTProtocol::GetLine(reinterpret_cast<char*>(p_buff), (char*)line.GetP()));
        code   = HTTProtocol::GetResponseCode(reinterpret_cast<char*>(line.GetP()));
    }

    // p_curr points to the next field or to CRLF
    if(*p_curr == Char::CR || *p_curr == Char::CR)
    {
        // if we are here, we could not get anything
        return code;
    }

    // build header
    String<> header;

    for(;;)
    {
        p_curr  = reinterpret_cast<byte*>(HTTProtocol::GetLine(reinterpret_cast<char*>(p_curr), (char*)line.GetP()));
        header += reinterpret_cast<char*>(line.GetP());

        if(p_curr == null || *line == 0 || *p_curr == Char::CR || *p_curr == Char::LF)
        {
            break;
        }
    }

    HTTProtocol::ProcessHeader(header, _context);

    // get entity boundary
    if(!_check && (p_curr = (byte*)HTTProtocol::GetEntityBoundary(reinterpret_cast<char*>(buffer.GetP()))) == null)
    {
        // try again, ms iis
        count_read += Connection.Receive(buffer.GetP()+count_read, _buffer_size_, _timeout);
    }

    uint64 size = 0;

    if(code == HTTProtocol::Code200)
    {
        if(_check)
        {
            return code;
        }

        if(_context.TransferEncoding != null && _context.Chunked)
        {
            // chunked stuff
            uint   chunk_size  = 0;
            uint   chunk_count = 0;
            bool   keep_crlf   = HTTProtocol::IsKeepCRLF(_context.ContentType);

            p_line = line.GetP();

            for(;;)
            {
                uint length = 0;

                if(Terminated)
                {
                    return code;
                }
            
                while(p_curr < p_buff+count_read && !(*p_curr == Char::CR || *p_curr == Char::LF))
                {
                    *p_line++ = *p_curr++;
                    ++chunk_count;
                }

                if(p_curr >= p_buff+count_read)
                {
                    // we are outside the buffer, alert
                    if((count_read = Connection.Receive(buffer.GetP(), _buffer_size_, _timeout)) == 0)
                    {
                        *p_line = 0;
                        length = StrLen(reinterpret_cast<char*>(line.GetP()));

                        // save rest and quit
                        if(length > 0)
                        {
                            Write(_file, line.GetP(), length);
                            size += length;
                        }
                        break;
                    }

                    p_curr = p_buff;
                    continue;
                }

                // skip CRLF or CR or LF
                if(*p_curr == Char::CR || *p_curr == Char::LF)
                {
                    if(keep_crlf && chunk_size > 0 && chunk_count < chunk_size) // ignore last CRLF
                    {
                        *p_line++ = *p_curr++, ++chunk_count;

                        if(*p_curr == Char::CR || *p_curr == Char::LF)
                        {
                            *p_line++ = *p_curr++, ++chunk_count;
                        }
                    }
                    else
                    {
                        ++p_curr, ++chunk_count;

                        if(*p_curr == Char::CR || *p_curr == Char::LF)
                        {
                            ++p_curr, ++chunk_count;
                        }
                    }
                }

               *p_line = 0;
                p_line = line.GetP();
                length = StrLen(reinterpret_cast<char*>(line.GetP()));

                if(chunk_size == 0)
                {
                    // the line MUST contain chunk's size
                    chunk_count = 0;

                    if((chunk_size = HTTProtocol::GetChunkSize(reinterpret_cast<char*>(line.GetP()))) == 0)
                    {
                        break;
                    }
                }
                else if(chunk_count >= chunk_size)
                {
                    // process and get chunk's size
                    if(length > 0)
                    {
                        Write(_file, line.GetP(), length);
                        size += length;
                    }

                    chunk_size = 0;

                    while(p_curr < p_buff+count_read)
                    {
                        if(*p_curr != Char::CR && *p_curr != Char::LF)
                        {
                            break;
                        }

                        ++p_curr, ++chunk_count;
                    }
                }
                else if(length > 0)
                {
                    Write(_file, line.GetP(), length);
                    size += length;
                }
            }

            // set size
           _context.Size = size;
        }
        else if(_context.ContentLength != null)
        {
            // just grab it ! ...
            size = StrToInteger(_context.ContentLength);
           _context.Size = size;

            if(count_read > 0)
            {
                uint hdr_size = (uint)(p_curr-p_buff);
                Write(_file, buffer.GetP()+hdr_size, count_read-hdr_size);
                size -= count_read-hdr_size;

                while(size > 0 && (count_read = Connection.Receive(buffer.GetP(), _buffer_size_, _timeout)) != 0)
                {
                    Write(_file, buffer.GetP(), count_read);
                    size = count_read > size ? 0 : size-count_read;

                    if(Terminated)
                    {
                        return code;
                    }
                }
            }
        }
        else
        {
            // just dump everything
            if(count_read > 0)
            {
                uint hdr_size = (uint)(p_curr-p_buff);
                size = count_read-hdr_size;

                while((count_read = Connection.Receive(buffer.GetP(), _buffer_size_, _timeout)) != 0)
                {
                    Write(_file, buffer.GetP(), count_read);
                    size += count_read;

                    if(Terminated)
                    {
                        return code;
                    }
                }

               _context.Size = size;
            }
        }
        return code;
    }
    else if(code == HTTProtocol::Code300 || code == HTTProtocol::Code301 || code == HTTProtocol::Code302 || code == HTTProtocol::Code303)
    {
        // multiple choices, moved permanently, found or see other
        // the new uri is given by 'Location' field
        if(_context.Location != null)
        {
            // reestablish connection
            Resource = _context.Location.GetP();
            Disconnect();
            goto _start; // start over
        }
        return code;
    }
    else if(code == HTTProtocol::Code305)
    {
        // use proxy, who will expose his proxy to the internet ?! stupid ?!
        // the new uri is given by 'Location' field
        if(_context.Location != null)
        {
            // reestablish connection
            ProxyServer = _context.Location.GetP();
            Disconnect();
            goto _start; // start over
        }
        return code;
    }
    else if(code == HTTProtocol::Code304)
    {
        return code;
    }
    else if(code == HTTProtocol::Code401 || code == HTTProtocol::Code403)
    {
        // unauthrized or forbidden
        // haa... znachit tam, suka
        return code;
    }
    return HTTProtocol::Code0;
}

httpcode HTTPClient::GetResource(const tchar* _filename, const tchar* _url, const tchar* _proxy, const tchar* _socks, uint _timeout)
{
    try
    {
        HTTPURL url(_url);
        HTTPClient client(url);
        HTTProtocol::HTTPContext context;
        File<> file(_filename, File<>::eCreateNew|File<>::eAccessReadWrite|File<>::eShareRead);

        if(_proxy != null)
        {
            client.SetProxyServer(_proxy);
        }
        else if(_socks != null)
        {
            client.SetSOCKSServer(_socks);
        }
        return client.GetResource(file, context, false, _timeout);
    }
    catch(...)
    {
        return HTTProtocol::Code0;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

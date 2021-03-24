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

#ifndef __HTT_PROTOCOL_INC__
#   include <HTTProtocol.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPContext
// ----- -----------
HTTProtocol::HTTPContext::HTTPContext() : Size(0), Chunked(false)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class HTTProtocol
// ----- -----------
HTTProtocol::HTTProtocol()
{
}

HTTProtocol::~HTTProtocol()
{
}

httpcode HTTProtocol::GetResponseCode(const char* _line)
{
    xassert(_line != null, HTTProtocol::Code0);

    // status-line = http-version SP status-code SP reason-phrase CRLF
    char* p_curr = StrChar(_line, Char::Space);

    if(p_curr == null)
    {
        return HTTProtocol::Code0;
    }

    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    if(*p_curr == Char::ParenLeft)
    {
        p_curr = HTTProtocol::SkipComments(p_curr);
    }

    return static_cast<httpcode>(StrToInteger(p_curr));
}

int HTTProtocol::GetMajorVersion(const char* _line)
{
    // status-line = http-version SP status-code SP reason-phrase CRLF
    // http-version = "HTTP" "/" 1*DIGIT "." 1*DIGIT
    xassert(_line != null, null);
    //
    const char* p_buff = _line;
    char* p_curr = StrChar(p_buff, Char::Slash);

    if(p_curr == null)
    {
        return true;
    }

    p_curr = SkipSymbols(p_curr, Char::SPTAB);
    return StrToInteger(p_curr);
}

int HTTProtocol::GetMinorVersion(const char* _line)
{
    // status-line = http-version SP status-code SP reason-phrase CRLF
    // http-version = "HTTP" "/" 1*DIGIT "." 1*DIGIT
    xassert(_line != null, null);
    //
    const char* p_buff = _line;
    char* p_curr = StrChar(p_buff, Char::Slash);

    if(p_curr == null)
    {
        return true;
    }

    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    // skip major version
    while(*p_curr != 0 && isdigit(*p_curr))
    {
        ++p_curr;
    }

    ++p_curr; // skip '.'
    return StrToInteger(p_curr);
}

Time HTTProtocol::GetDate(const char* _line)
{
    // http allows three different formats for the representation of
    // date/time stamps:
    //  Sun, 06 Nov 1994 08:49:37 GMT; RFCs 822/1123 (MUST be)
    //  Sunday, 06-Nov-94 08:49:37 GMT; RFCs 850/1036
    //  Sun Nov 6 08:49:37 1994; ANSI C's asctime() format
    if(_line == null)
    {
        return Time();
    }
    //
    char term[32];

    const char* p_buff = _line;
    char* p_curr = StrChar(p_buff, Char::Colon);
    char* p_term;

    ushort year   = 0;
    ushort month  = 0;
    ushort wday   = 0;
    ushort day    = 0;
    ushort hour   = 0;
    ushort minute = 0;
    ushort second = 0;

    if(p_curr == null)
    {
        return Time();
    }

    ++p_curr; // skip ':'

    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    // get day
    p_term = term;

    while(*p_curr != 0 && isalpha(*p_curr))
    {
        *p_term++ = *p_curr++;
    }
    *p_term = 0;

    for(short i = 0; i < 7; i++)
    {
        if(StrICompare(term, Time::GetWeekDaysAbbr()[i]) == 0 || StrICompare(term, Time::GetWeekDays()[i]) == 0 )
        {
            wday = i;
            break;
        }
    }

    // get rest
    p_curr++;
    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    if(isdigit(*p_curr))
    {
        // 06 Nov 1994 08:49:37 GMT
        // 06-Nov-94 08:49:37 GMT
        p_term = term;

        while(*p_curr != 0 && isdigit(*p_curr))
        {
            *p_term++ = *p_curr++;
        }
        *p_term = 0;

        day = static_cast<ushort>(StrToInteger(term));
        ++p_curr; // skip ' ' or '-'
    }
    else
    {
        // Nov 6 08:49:37 1994
        p_term = term;

        while(*p_curr != 0 && isalpha(*p_curr))
        {
            *p_term++ = *p_curr++;
        }
        *p_term = 0;

        for(short i = 0; i < 12; i++)
        {
            if(StrICompare(term, Time::GetMonthsAbbr()[i]) == 0 || StrICompare(term, Time::GetMonths()[i]) == 0)
            {
                month = i+1;
                break;
            }
        }
    }

    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    if(isalpha(*p_curr))
    {
        // Nov 1994 08:49:37 GMT
        // Nov-94 08:49:37 GMT
        p_term = term;

        while(*p_curr != 0 && isalpha(*p_curr))
        {
            *p_term++ = *p_curr++;
        }
        *p_term = 0;

        for(short i = 0; i < 12; i++)
        {
            if(StrICompare(term, Time::GetMonthsAbbr()[i]) == 0 || StrICompare(term, Time::GetMonths()[i]) == 0)
            {
                month = i+1;
                break;
            }
        }

        ++p_curr; // skip ' ' or '-'
        p_curr = SkipSymbols(p_curr, Char::SPTAB);

        // 1994 08:49:37 GMT
        // 94 08:49:37 GMT
        p_term = term;

        while(*p_curr != 0 && isdigit(*p_curr))
        {
            *p_term++ = *p_curr++;
        }
        *p_term = 0;

        year = static_cast<ushort>(StrToInteger(term));
    }
    else
    {
        // 6 08:49:37 1994
        p_term = term;

        while(*p_curr != 0 && isdigit(*p_curr))
        {
            *p_term++ = *p_curr++;
        }
        *p_term = 0;
        day = static_cast<ushort>(StrToInteger(term));
    }

    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    // get time
    // 08:49:37 GMT
    // 08:49:37 1994
    p_term = term;

    while(*p_curr != 0 && isdigit(*p_curr))
    {
        *p_term++ = *p_curr++;
    }
    *p_term = 0;

    hour = static_cast<ushort>(StrToInteger(term));

    p_curr = SkipSymbols(p_curr, Char::SPTAB);
    p_curr = SkipSymbol(p_curr, Char::Colon);
    p_term = term;

    while(*p_curr != 0 && isdigit(*p_curr))
    {
        *p_term++ = *p_curr++;
    }
    *p_term = 0;

    minute = static_cast<ushort>(StrToInteger(term));

    p_curr = SkipSymbols(p_curr, Char::SPTAB);
    p_curr = SkipSymbol(p_curr, Char::Colon);
    p_term = term;

    while(*p_curr != 0 && isdigit(*p_curr))
    {
        *p_term++ = *p_curr++;
    }
    *p_term = 0;

    second = static_cast<ushort>(StrToInteger(term));

    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    // GMT
    // 1994
    if(isdigit(*p_curr))
    {
        p_term = term;

        while(*p_curr != 0 && isdigit(*p_curr))
        {
            *p_term++ = *p_curr++;
        }
        *p_term = 0;

        year = static_cast<ushort>(StrToInteger(term));
    }

    return Time(year, month, day, hour, minute, second);
}

bool HTTProtocol::IsKeepCRLF(const char* _type)
{
    return _type != null && StrSubstr(_type, "text") == _type;
}
     
bool HTTProtocol::IsChunked(const char* _line)
{
    xassert(_line != null, false);
    //
    const ushort _line_size_ = 1024;
    const char*  _chunked_   = "chunked";
    //
    AutoPtrArray<char> line = new char[_line_size_];
    HTTProtocol::GetLine(_line, line);
    StrLower(line);
    return HasToken(line, _chunked_, " \r\n\t") != null;
}

uint HTTProtocol::GetChunkSize(const char* _line)
{
    // chunk = chunk-size [chunk-extention] CRLF
    // chunk-size = 1*HEX
    xassert(_line != null, 0);
    //
    const char* p_buff = _line;
    char* p_curr = const_cast<char*>(p_buff);

    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    if(*p_curr == Char::ParenLeft)
    {
        p_curr = SkipComments(p_curr);
    }
    return StrToInteger(p_curr, null, 16);
}

fsize_t_ HTTProtocol::GetContentSize(const char* _line)
{
    // Content-Length = "Content-Length" ":" 1*DIGIT
    xassert(_line != null, 0);
    //
    const char* p_buff = _line;
    char* p_curr = StrChar(p_buff, Char::Colon);

    if(p_curr == null)
    {
        return 0;
    }

    p_curr++; // skip ':'
    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    if(*p_curr == Char::ParenLeft)
    {
        p_curr = SkipComments(p_curr);
    }
    return StrToInteger(p_curr);
}

void HTTProtocol::GetContentRange(const char* _line, fsize_t_& _first_byte_pos, fpos_t_& _last_byte_pos, fpos_t_& _total_byte_pos)
{
    // Content-Range = "Content-Range" ":" spec
    // Content-Range: bytes 0-499/500
   _first_byte_pos = _last_byte_pos = _total_byte_pos = 0;

    xassertv(_line != null);
    //
    const char* p_buff = _line;
    char* p_curr = StrChar(p_buff, Char::Colon);

    if(p_curr == null)
    {
        return;
    }

    p_curr++; // skip ':'

    // skip spec (e.g. "bytes")
    while(*++p_curr != 0 && !isdigit(*p_curr))
    {
    }

    // get first
   _first_byte_pos = StrToInteger(p_curr);

    // skip first number
    while(*++p_curr != 0 && isdigit(*p_curr))
    {
    }

    // skip '-'
    while(*++p_curr != 0 && !isdigit(*p_curr))
    {
    }

    // get last
   _last_byte_pos = StrToInteger(p_curr);

    // skip last number & '/'
    p_curr = StrChar(p_curr, Char::Slash);

    if(p_curr != null)
    {
        _total_byte_pos = StrToInteger(p_curr);
    }
}

const tchar* HTTProtocol::GetUserAgentField()
{
    static const tchar* _user_agent_ = _t("UI Soft");
    return _user_agent_;
}

tchar* HTTProtocol::GetLocation(const tchar* _line, tchar* _location)
{
    xassert(_line != null && _location != null, null);
    *_location = 0;
    //
    char* p_buff = StrChar(_line, Char::Colon);
    char* p_curr = _location;

    if(p_buff != null)
    {
        ++p_buff; // skip ':'

        p_curr = SkipSymbols(p_curr, Char::SPTAB);

        while(*p_buff != 0 && *p_buff != Char::Space && *p_buff != Char::CR && *p_buff != Char::LF)
        {
            *p_curr++ = *p_buff++;
        }
        *p_curr = 0;
    }

    return p_buff;
}

tchar* HTTProtocol::GetType(const char* _line, char* _type)
{
    // Content-Type = "Content-Type" ":" type "/" subtype
    //                *(";" parameter)
    xassert(_line != null && _type != null, null);
    *_type = 0;

    //
    const char* p_buff = _line;
    char* p_type = _type;
    char* p_curr = StrChar(p_buff, Char::Colon);

    if(p_curr == null)
    {
        return null;
    }

    p_curr++; // skip ':'
    p_curr = SkipSymbols(p_curr, Char::SPTAB);

    if(*p_curr == Char::ParenLeft)
    {
        p_curr = SkipComments(p_curr);
    }

    while(*p_curr != 0 && *p_curr != ';' && *p_curr != ' ' && *p_curr != '\t' && *p_curr != '\r' && *p_curr != '\n')
    {
        *p_type++ = *p_curr++;
    }
    *p_type = 0;
    return p_curr;
}

char* HTTProtocol::GetEntityBoundary(const char* _buffer)
{
    xassert(_buffer != null, null);
    //
    const char* p_buff = _buffer;

    while(*p_buff != 0)
    {
        if(*p_buff == Char::CR || *p_buff == Char::LF)
        {
            ++p_buff;

            if((*p_buff == Char::CR || *p_buff == Char::LF) && (*(p_buff+1) == Char::CR || *(p_buff+1) == Char::LF))
            {
                ++p_buff;

                while(*p_buff == Char::CR || *p_buff == Char::LF)
                {
                    ++p_buff;
                }

                break;
            }
        }
        ++p_buff;
    }

    return const_cast<char*>(p_buff);
}

char* HTTProtocol::SkipComments(char* _p)
{
    // syntax is as follows:
    //  (xxx(xxx)xxx)xxx
    //  inP pointers to '('
    xassert(_p != null, null);
    //
    char* p_curr = _p;

    while(*p_curr != 0 && *p_curr != Char::ParenRight)
    {
        if(*(++p_curr) == Char::ParenLeft)
        {
            p_curr = SkipComments(p_curr);
        }
    }

    if(*p_curr == Char::ParenRight)
    {
        ++p_curr; // skip ')'
    }

    return p_curr;
}

char* HTTProtocol::GetLine(const char* _buffer, char* _line, bool _crlf)
{
    xassert(_buffer != null && _line != null, null);
    // the outLine will include CRLF or CR or LF
    const char* p_buff = _buffer;
    char* p_curr = _line;

    while(*p_buff != 0 && *p_buff != Char::CR && *p_buff != Char::LF)
    {
        *p_curr++ = *p_buff++;
    }

    if(_crlf && (*p_buff == Char::CR || *p_buff == Char::LF))
    {
        *p_curr++ = *p_buff++;

        if(*p_buff == Char::CR || *p_buff == Char::LF)
        {
            *p_curr++ = *p_buff++;
        }
    }

   *p_curr = 0;
    return const_cast<char*>(p_buff);
}

void HTTProtocol::ProcessHeader(const char* _header, HTTProtocol::HTTPContext& _context)
{
    //
    static const tchar* _http_fields_[] = 
    {
        "Accept:",
        "Accept-Charset:",
        "Accept-Encoding:",
        "Accept-Language:",
        "Accept-Ranges:",
        "Age:",
        "Allow:",
        "Authentication:",
        "Authorization:",
        "Cache-Control:",
        "Connection:", 
        "Content-Base:",
        "Content-Encoding:", 
        "Content-Language:", 
        "Content-Length:",
        "Content-Location:", 
        "Content-MD5:", 
        "Content-Range:",
        "Content-Transfer-Encoding:",
        "Content-Type:",
        "Cookie:",
        "Date:",
        "Derived-From:",
        "ETag:",
        "Expect:",
        "Expires:",
        "From:",
        "Forwarded:",
        "Host:",
        "If-Match:",
        "If-Match-Any:",
        "If-Modified-Since:",
        "If-None-Match:",
        "If-None-Match-Any:",
        "If-Range:",
        "If-Unmodified-Since:",
        "Keep-Alive:",
        "Last-Modified:",
        "Link:",
        "Location:",
        "Max-Forwards:",
        "Message-Id:",
        "MIME:",
        "Pragma:",
        "Proxy-Authenticate:",
        "Proxy-Authorization:",
        "Range:",
        "Referer:",
        "Retry-After:",
        "Server:",
        "Set-Cookie:",
        "TE:",
        "Trailer:",
        "Transfer-Encoding:",
        "Upgrade:",
        "URI:",
        "User-Agent:",
        "Vary:",
        "Version:",
        "Via:",
        "Warning:",
        "WWW-Authenticate:",
        null
    };
    //
    const char*  _delim_ = " \r\n\t";
    const ushort _buffer_size_ = 1024;
    //
    AutoPtrArray<char> buffer = new char[_buffer_size_];

    const char* p_hdr = _header;
    char* p_curr;

    // phase I (process http standard fields)
    for(int i = 0; _http_fields_[i] != null; i++)
    {
        if((p_curr = HasToken(p_hdr, _http_fields_[i], _delim_)) != null)
        {
            p_curr = StrChar(p_curr, Char::Colon);
          ++p_curr;
            p_curr = SkipSymbols(p_curr, Char::SPTAB);
            //
            HTTProtocol::GetLine(p_curr, buffer, false);

            ////////////////////////
            #define entry(_x)       \
             _x = StrClone(buffer); \
              break;
            ////////////////////////

            switch(i)
            {
                case 0:
                    entry(_context.Accept)
                case 1:
                    entry(_context.AcceptCharset)
                case 2:
                    entry(_context.AcceptEncoding)
                case 3:
                    entry(_context.AcceptLanguage)
                case 4:
                    entry(_context.AcceptRanges)
                case 5:
                    entry(_context.Age)
                case 6:
                    entry(_context.Allow)
                case 7:
                    entry(_context.Authentication)
                case 8:
                    entry(_context.Authorization)
                case 9:
                    entry(_context.CacheControl)
                case 10:
                    entry(_context.Connection) 
                case 11:
                    entry(_context.ContentBase)
                case 12:
                    entry(_context.ContentEncoding) 
                case 13:
                    entry(_context.ContentLanguage) 
                case 14:
                    entry(_context.ContentLength)
                case 15:
                    entry(_context.ContentLocation) 
                case 16:
                    entry(_context.ContentMD5) 
                case 17:
                    entry(_context.ContentRange)
                case 18:
                    entry(_context.ContentTransferEncoding)
                case 19:
                    entry(_context.ContentType)
                case 20:
                    entry(_context.Cookie)
                case 21:
                    entry(_context.Date)
                case 22:
                    entry(_context.DerivedFrom)
                case 23:
                    entry(_context.ETag)
                case 24:
                    entry(_context.Expect)
                case 25:
                    entry(_context.Expires)
                case 26:
                    entry(_context.From)
                case 27:
                    entry(_context.Forwarded)
                case 28:
                    entry(_context.Host)
                case 29:
                    entry(_context.IfMatch)
                case 30:
                    entry(_context.IfMatchAny)
                case 31:
                    entry(_context.IfModifiedSince)
                case 32:
                    entry(_context.IfNoneMatch)
                case 33:
                    entry(_context.IfNoneMatchAny)
                case 34:
                    entry(_context.IfRange)
                case 35:
                    entry(_context.IfUnmodifiedSince)
                case 36:
                    entry(_context.KeepAlive)
                case 37:
                    entry(_context.LastModified)
                case 38:
                    entry(_context.Link)
                case 39:
                    entry(_context.Location)
                case 40:
                    entry(_context.MaxForwards)
                case 41:
                    entry(_context.MessageId)
                case 42:
                    entry(_context.MIME)
                case 43:
                    entry(_context.Pragma)
                case 44:
                    entry(_context.ProxyAuthenticate)
                case 45:
                    entry(_context.ProxyAuthorization)
                case 46:
                    entry(_context.Range)
                case 47:
                    entry(_context.Referer)
                case 48:
                    entry(_context.RetryAfter)
                case 49:
                    entry(_context.Server)
                case 50:
                    entry(_context.SetCookie)
                case 51:
                    entry(_context.TE)
                case 52:
                    entry(_context.Trailer)
                case 53:
                    entry(_context.TransferEncoding)
                   _context.Chunked = true;
                case 54:
                    entry(_context.Upgrade)
                case 55:
                    entry(_context.URI)
                case 56:
                    entry(_context.UserAgent)
                case 57:
                    entry(_context.Vary)
                case 58:
                    entry(_context.Version)
                case 59:
                    entry(_context.Via)
                case 60:
                    entry(_context.Warning)
                case 61:
                    entry(_context.WWWAuthenticate)
            }
            ////////////////////////
            #undef entry
            ////////////////////////
        }
    }

    // phase II (process http NON-standard fields)
    p_curr = const_cast<char*>(p_hdr);

    for(;;)
    {
        p_curr = HTTProtocol::GetLine(p_curr, buffer);

        if(p_curr == null || *buffer == 0 || *p_curr == Char::CR || *p_curr == Char::LF)
        {
            break;
        }

        bool has = false;
        char* p;

        for(int i = 0; _http_fields_[i] != null; i++)
        {
            if((p = HasToken(buffer, _http_fields_[i], _delim_)) != null && p == buffer)
            {
                has = true;
                break;
            }
        }

        if(!has)
        {
            _context.Unknown += buffer;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

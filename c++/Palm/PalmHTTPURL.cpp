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

#ifndef __PALM_HTTP_URL_INC__
#   include <PalmHTTPURL.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPURL
// ----- -------
HTTPURL::HTTPURL()
{
}

HTTPURL::HTTPURL(const HTTPURL& _other)
{
    operator = (_other);
}

HTTPURL::HTTPURL(const char* _url) : URL(_url)
{
}

HTTPURL::~HTTPURL()
{
}

_string HTTPURL::GetHost() const
{
    const char* p_buff = GetPtrToSpecpart();

    if(p_buff == null)
    {
        return _string();
    }

   _string str;

    while(*p_buff != 0 && !URL::IsDelimiter(*p_buff))
    {
        str += *p_buff++;
    }
    return str;
}

uint16 HTTPURL::GetPort() const
{
    //
    const uint16 _port_ = 80;
    //
    const char* p_buff = GetPtrToSpecpart();

    if(p_buff != null)
    {
        const char* p_curr = PalmText::StrChar(p_buff, Char::Colon);

        if(p_curr != null && *++p_curr != 0)
        {
            uint16 port = static_cast<uint16>(PalmText::StrAToI(p_curr));
            return port == 0 ? _port_ : port;
        }
    }
    return _port_;
}

_string HTTPURL::GetPath() const
{
    const char* p_buff = GetPtrToSpecpart();
    const char* p_curr;

    if(p_buff == null || (p_curr = PalmText::StrChar(p_buff, Char::Slash)) == null)
    {
        return _string();
    }
    else
    {
        // skip '/', because '/' does not belong to <url-path>, RFC1738 p.5
        ++p_curr;

       _string str;

        while(*p_curr != 0 && *p_curr != Char::Question)
        {
            str += *p_curr++;
        }
        return str;
    }
}

_string HTTPURL::GetAbsPath() const
{
   _string s = "/"; // Char::Slash
    s += GetPath();
    return s;
}

_string HTTPURL::GetDirectory() const
{
    _string str = GetPath();

    if(str.empty())
    {
        return _string();
    }

    const char* p_buff = str.c_str();
    const char* p_curr = PalmText::StrRChar(p_buff, Char::Slash);

    if(p_curr == null)
    {
        // just a filename
        return _string();
    }

    str.resize(str.size()-(p_curr-p_buff)+1);
    return str;
}

_string HTTPURL::GetFilename() const
{
    // here we assume that last segment of the path is file name,
    // if not bye-bye
    _string str = GetPath();

    if(str.empty())
    {
        return _string();
    }

    const char* p_buff = str.c_str();
    const char* p_curr = PalmText::StrRChar(p_buff, Char::Slash);

    if(p_curr == null)
    {
        // just a filename
        return str;
    }
    return _string(str, static_cast<uint32>(p_curr-p_buff+1), str.size()-(p_curr-p_buff));
}

_string HTTPURL::GetParam() const
{
    return _string();
}

_string HTTPURL::GetQuery() const
{
    const char* p_buff = GetPtrToSpecpart();

    if(p_buff == null || (p_buff = PalmText::StrRChar(p_buff, Char::Question)) == null)
    {
        return _string();
    }
    else
    {
        return _string(/*++*/p_buff); // '?' included
    }
}

_string HTTPURL::GetRef() const 
{
    const char* p_buff = GetPtrToSpecpart();
    //                                            '#'
    if(p_buff == null || (p_buff = PalmText::StrStr(p_buff, "%23")) == null)
    {
        return _string();
    }
    else
    {
        // skip '#'
        p_buff += 3;
        return _string(p_buff);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

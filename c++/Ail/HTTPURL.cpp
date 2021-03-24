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

#ifndef __HTTP_URL_INC__
#   include <HTTPURL.inc>
#endif

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

HTTPURL::HTTPURL(const tchar* _url) : URL(_url)
{
}

HTTPURL::~HTTPURL()
{
}

String<> HTTPURL::GetHost() const
{
    const tchar* p_buff = GetPtrToSpecpart();

    if(p_buff == null)
    {
        return String<>();
    }

    // 32 is apriory size for domain name,
    // who will register domain with more than 32 chars !...
    const short _reserve_ = 32;
    //
    String<> str;
    str.Reserve(_reserve_);

    while(*p_buff != 0 && !URL::IsDelimiter(*p_buff))
    {
        str += *p_buff++;
    }

    return str;
}

ushort HTTPURL::GetPort() const
{
    //
    const ushort _port_ = 80;
    //
    const tchar* p_buff = GetPtrToSpecpart();

    if(p_buff != null)
    {
        const tchar* p_curr = StrChar(p_buff, ':');

        if(p_curr != null && *++p_curr != 0)
        {
            ushort port = static_cast<ushort>(StrToInteger(p_curr));
            return port == 0 ? _port_ : port;
        }
    }

    return _port_;
}

String<> HTTPURL::GetPath() const
{
    const tchar* p_buff = GetPtrToSpecpart();
    const tchar* p_curr;

    if(p_buff == null || (p_curr = StrChar(p_buff, '/')) == null)
    {
        return String<>();
    }
    else
    {
        // skip '/', because '/' does not belong to <url-path>, RFC1738 p.5
        ++p_curr;

        String<> str;

        while(*p_curr != 0 && *p_curr != '?')
        {
            str += *p_curr++;
        }

        return str;
    }
}

String<> HTTPURL::GetAbsPath() const
{
    String<> s = '/';
    s += GetPath();
    return s;
}

String<> HTTPURL::GetDirectory() const
{
    String<> str = GetPath();

    if(str.IsEmpty())
    {
        return String<>();
    }

    const tchar* p_buff = str;
    const tchar* p_curr = StrRChar(p_buff, '/');

    if(p_curr == null)
    {
        // just a filename
        return String<>();
    }

    str.Resize(str.GetCount()-(p_curr-p_buff)+1);
    return str;
}

String<> HTTPURL::GetFilename() const
{
    // here we assume that last segment of the path is file name,
    // if not bye-bye
    String<> str = GetPath();

    if(str.IsEmpty())
    {
        return String<>();
    }

    const tchar* p_buff = str;
    const tchar* p_curr = StrRChar(p_buff, '/');

    if(p_curr == null)
    {
        // just a filename
        return str;
    }

    return String<>(str, (uint)(p_curr-p_buff+1), str.GetCount()-(p_curr-p_buff));
}

String<> HTTPURL::GetParam() const
{
    return String<>();
}

String<> HTTPURL::GetQuery() const
{
    const tchar* p_buff = GetPtrToSpecpart();

    if(p_buff == null || (p_buff = StrRChar(p_buff, '?')) == null)
    {
        return String<>();
    }
    else
    {
        return String<>(/*++*/p_buff); // '?' included
    }
}

String<> HTTPURL::GetRef() const 
{
    const tchar* p_buff = GetPtrToSpecpart();
    //                                            '#'
    if(p_buff == null || (p_buff = StrSubstr(p_buff, "%23")) == null)
    {
        return String<>();
    }
    else
    {
        // skip '#'
        p_buff += 3;
        return String<>(p_buff);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

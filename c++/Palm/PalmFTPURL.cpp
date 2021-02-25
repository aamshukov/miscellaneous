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

#ifndef __PALM_FTP_URL_INC__
#   include <PalmFTPURL.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPURL
// ----- ------
FTPURL::FTPURL()
{
}

FTPURL::FTPURL(const FTPURL& _other)
{
    operator = (_other);
}

FTPURL::FTPURL(const char* _url) : URL(_url)
{
}

FTPURL::~FTPURL()
{
}

_string FTPURL::GetHost() const
{
    const char* p_buff = GetPtrToSpecpart();

    if(p_buff == null)
    {
        return _string();
    }

    const char* p_curr = PalmText::StrChar(p_buff, Char::At);

    if(p_curr == null)
    {
        // no <username>:<password> case
        static const char* _delimiters_ = "/:@?";
        //
        const char* p = _delimiters_;

        while(*p != 0) // mimic strpbrk
        {
            if((p_curr = PalmText::StrChar(p_buff, *p++)) != null)
            {
                break;
            }
        }
    
        if(p_curr == null)
        {
            // everything is a host
            return _string(p_buff);
        }

        p_curr = p_buff;
    }
    else
    {
        // <username>:<password> case
        ++p_curr; // skip '@'
    }

   _string str;

    while(*p_curr != 0 && !URL::IsDelimiter(*p_curr))
    {
        str += *p_curr++;
    }
    return str;
}

uint16 FTPURL::GetPort() const
{
    //
    const uint16 _port_ = 21;
    //
    const char* p_buff = GetPtrToSpecpart();

    if(p_buff != null)
    {
        const char* p_curr = PalmText::StrChar(p_buff, Char::At);
        p_curr = PalmText::StrChar(p_curr != null ? ++p_curr : p_buff, Char::Colon);

        if(p_curr != null && *++p_curr != 0)
        {
            uint16 port = static_cast<uint16>(PalmText::StrAToI(p_curr));
            return port == 0 ? _port_ : port;
        }
    }
    return _port_;
}

_string FTPURL::GetUsername() const
{
    const char* p_buff = GetPtrToSpecpart();

    if(p_buff == null || PalmText::StrChar(p_buff, Char::At) == null)
    {
        return _string();
    }
    else
    {
        // <username>:<password> case
        const short _reserve_ = 16;
        //
       _string str;

        while(!URL::IsDelimiter(*p_buff))
        {
            str += *p_buff++;
        }
        return str;
    }
}

_string FTPURL::GetPassword() const
{
    const char* p_buff = GetPtrToSpecpart();
    const char* p_curr;

    if(p_buff == null || (p_curr = PalmText::StrChar(p_buff, Char::At)) == null)
    {
        return _string();
    }
    else
    {
        // <username>:<password> case
        // could be <username>:, BUT never just <password>
        --p_curr; // skip Char::At

        if(*p_curr == Char::Colon)
        {
            // no <password>
            return _string();
        }

        while(p_curr != p_buff && !URL::IsDelimiter(*p_curr))
        {
            --p_curr;
        }

        ++p_curr; // skip delimiter

       _string str;

        while(p_curr != null && !URL::IsDelimiter(*p_curr))
        {
            str += *p_curr++;
        }
        return str;
    }
}

_string FTPURL::GetPath() const
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

        while(*p_curr != 0 && *p_curr != Char::Semicolon)
        {
            str += *p_curr++;
        }
        return str;
    }
}

_string FTPURL::GetAbsPath() const
{
   _string s = "/"; // Char::Slash
    s += GetPath();
    return s;
}

_string FTPURL::GetDirectory() const
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
        return str;
    }

    str.resize(str.size()-(p_curr-p_buff)+1);
    return str;
}

_string FTPURL::GetFilename() const
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

_string FTPURL::GetType() const
{
    const char* p_buff = GetPtrToSpecpart();
    const char* p_curr;

    if(p_buff == null || (p_curr = PalmText::StrRChar(p_buff, Char::Semicolon)) == null)
    {
        return _string();
    }
    else
    {
        ++p_curr; // skip ';'
        ++p_curr; // skip '='
        return _string(p_curr);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

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

#ifndef __FTP_URL_INC__
#   include <FTPURL.inc>
#endif

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

FTPURL::FTPURL(const tchar* _url) : URL(_url)
{
}

FTPURL::~FTPURL()
{
}

String<> FTPURL::GetHost() const
{
    const tchar* p_buff = GetPtrToSpecpart();

    if(p_buff == null)
    {
        return String<>();
    }

    const tchar* p_curr = StrChar(p_buff, '@');

    if(p_curr == null)
    {
        // no <username>:<password> case
        static tchar* _delimiters_ = _t("/:@?");
        //
        if((p_curr = Strpbrk(p_buff, _delimiters_)) == null)
        {
            // everything is a host
            return String<>(p_buff);
        }
        else
        {
            p_curr = p_buff;
        }
    }
    else
    {
        // <username>:<password> case
        ++p_curr; // skip '@'
    }

    // 32 is apriory size for domain name,
    // who will register domain with more than 32 chars !...
    const ushort _reserve_ = 32;
    //
    String<> str;
    str.Reserve(_reserve_);

    while(*p_curr != 0 && !URL::IsDelimiter(*p_curr))
    {
        str += *p_curr++;
    }
    return str;
}

ushort FTPURL::GetPort() const
{
    //
    const ushort _port_ = 21;
    //
    const tchar* p_buff = GetPtrToSpecpart();

    if(p_buff != null)
    {
        const tchar* p_curr = StrChar(p_buff, '@');
        p_curr = StrChar(p_curr != null ? ++p_curr : p_buff, ':');

        if(p_curr != null && *++p_curr != 0)
        {
            ushort port = static_cast<ushort>(atol(p_curr));
            return port == 0 ? _port_ : port;
        }
    }
    return _port_;
}

String<> FTPURL::GetUsername() const
{
    const tchar* p_buff = GetPtrToSpecpart();

    if(p_buff == null || StrChar(p_buff, '@') == null)
    {
        return String<>();
    }
    else
    {
        // <username>:<password> case
        // 16 is apriory size for username,
        // who will type username with more than 16 chars !...
        const short _reserve_ = 16;
        //
        String<> str;
        str.Reserve(_reserve_);

        while(!URL::IsDelimiter(*p_buff))
        {
            str += *p_buff++;
        }
        return str;
    }
}

String<> FTPURL::GetPassword() const
{
    const tchar* p_buff = GetPtrToSpecpart();
    const tchar* p_curr;

    if(p_buff == null || (p_curr = StrChar(p_buff, '@')) == null)
    {
        return String<>();
    }
    else
    {
        // <username>:<password> case
        // could be <username>:, BUT never just <password>
        --p_curr; // skip '@'

        if(*p_curr == ':')
        {
            // no <password>
            return String<>();
        }

        while(p_curr != p_buff && !URL::IsDelimiter(*p_curr))
        {
            --p_curr;
        }

        ++p_curr; // skip delimiter

        // 16 is apriory size for username,
        // who will type username with more than 16 chars !...
        const short _reserve_ = 16;
        //
        String<> str;
        str.Reserve(_reserve_);

        while(p_curr != null && !URL::IsDelimiter(*p_curr))
        {
            str += *p_curr++;
        }
        return str;
    }
}

String<> FTPURL::GetPath() const
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

        while(*p_curr != 0 && *p_curr != ';')
        {
            str += *p_curr++;
        }
        return str;
    }
}

String<> FTPURL::GetAbsPath() const
{
    String<> s = '/';
    s += GetPath();
    return s;
}

String<> FTPURL::GetDirectory() const
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
        return str;
    }

    str.Resize(str.GetCount()-(p_curr-p_buff)+1);
    return str;
}

String<> FTPURL::GetFilename() const
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
    return String<>(str, (int)(p_curr-p_buff+1), str.GetCount()-(p_curr-p_buff));
}

String<> FTPURL::GetType() const
{
    const tchar* p_buff = GetPtrToSpecpart();
    const tchar* p_curr;

    if(p_buff == null || (p_curr = StrRChar(p_buff, ';')) == null)
    {
        return String<>();
    }
    else
    {
        ++p_curr; // skip ';'
        ++p_curr; // skip '='
        return String<>(p_curr);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

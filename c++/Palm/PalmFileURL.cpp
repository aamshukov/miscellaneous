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

#ifndef __PALM_FILE_URL_INC__
#   include <PalmFileURL.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FileURL
// ----- -------
FileURL::FileURL()
{
}

FileURL::FileURL(const FileURL& _other)
{
    if(this != &_other)
    {
        URL_ = _other.URL_;
    }
}

FileURL::FileURL(const char* _url)
       : URL(_url)
{
}

FileURL::~FileURL()
{
}

_string FileURL::GetHost() const
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

_string FileURL::GetPath() const
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

_string FileURL::GetAbsPath() const
{
   _string s = "/"; // Char::Slash
    s += GetPath();
    return s;
}

_string FileURL::GetDirectory() const
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

    str.resize(static_cast<uint32>(p_curr-p_buff));
    return str;
}

_string FileURL::GetFilename() const
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
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

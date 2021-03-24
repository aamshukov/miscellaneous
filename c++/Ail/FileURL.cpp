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

#ifndef __FILE_URL_INC__
#   include <FileURL.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FileURL
// ----- -------
FileURL::FileURL()
{
}

FileURL::FileURL(const FileURL& _other)
{
    operator = (_other);
}

FileURL::FileURL(const tchar* _url) : URL(_url)
{
}

FileURL::~FileURL()
{
}

String<> FileURL::GetHost() const
{
    // 32 is apriory size for domain name,
    // who will register domain with more than 32 chars !...
    const short _reserve_ = 32;
    //
    const char* p_buff = GetPtrToSpecpart();

    if(p_buff == null)
    {
        return String<>();
    }

    String<> str;
    str.Reserve(_reserve_);

    while(*p_buff != 0 && !URL::IsDelimiter(*p_buff))
    {
        str += *p_buff++;
    }
    return str;
}

String<> FileURL::GetPath() const
{
    const char* p_buff = GetPtrToSpecpart();
    const char* p_curr;

    if(p_buff == null || (p_curr = StrChar(p_buff, Char::Slash)) == null)
    {
        return String<>();
    }
    else
    {
        // skip '/', because '/' does not belong to <url-path>, RFC1738 p.5
        ++p_curr;

        String<> str;

        while(*p_curr != 0 && *p_curr != Char::Semicolon)
        {
            str += *p_curr++;
        }
        return str;
    }
}

String<> FileURL::GetAbsPath() const
{
    String<> s = '/';
    s += GetPath();
    return s;
}

String<> FileURL::GetDirectory() const
{
    String<> str = GetPath();

    if(str.IsEmpty())
    {
        return String<>();
    }

    const char* p_buff = str;
    const char* p_curr = StrRChar(p_buff, Char::Slash);

    if(p_curr == null)
    {
        // just a filename
        return String<>();
    }

    str.Resize(p_curr-p_buff);
    return str;
}

String<> FileURL::GetFilename() const
{
    // here we assume that last segment of the path is file name,
    // if not bye-bye
    String<> str = GetPath();

    if(str.IsEmpty())
    {
        return String<>();
    }

    const tchar* p_buff = str;
    const tchar* p_curr = StrRChar(p_buff, Char::Slash);

    if(p_curr == null)
    {
        // just a filename
        return str;
    }

    return String<>(str, p_curr-p_buff+1, str.GetCount()-(p_curr-p_buff));
}

String<> FileURL::GetLocalFile() const
{
    AutoPtrArray<tchar> buffer = StrClone(URL_);
    RemoveEsc(buffer);
    //
    char* p_buff = buffer;
    char* p_curr = p_buff;

    p_curr += 7; // 'file://'
    p_curr++;	 // '/'

    String<> str;

    while(*p_curr != 0)
    {
        if(*p_curr == Char::Bar)
        {
            str += Char::Colon;
        }
        else if(*p_curr == Char::Slash)
        {
            str += Char::BackSlash;
        }
        else
        {
            str += *p_curr;
        }

        ++p_curr;
    }

    if(StrChar(p_buff, Char::Colon) == null)
    {
        int count = ::GetCurrentDirectory(0, null);
        AutoPtrArray<tchar> path = new tchar[count];
        count = ::GetCurrentDirectory(count, path);
        path[count] = 0;
        //
        String<> tmp(path, 3);
        tmp += str;
        str  = tmp;
    }
    return str;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

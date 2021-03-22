////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FTP_URL_H__
#define __FTP_URL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPURL
// ----- ------
class __DECLSPEC__ FTPURL : public URL
{
    // <URL>:<ftp>://<username>:<password>@<host>:<port>/<url-path>
    // <url-path> -> <cwd1>/<cwd2>/.../<cwdn>/<name>;type=<typecode>
    typedef String<> _String;

    public:
     // ctor/dtor
                FTPURL();
                FTPURL(const FTPURL&);
                FTPURL(const tchar*);
     virtual   ~FTPURL();

     // operators
     bool       operator == (const FTPURL&)     const;
     bool       operator == (const tchar*)      const;
     bool       operator != (const FTPURL&)     const;
     bool       operator != (const tchar*)      const;

     // protocol
    _String     GetHost()                       const;
     ushort     GetPort()                       const;
    _String     GetUsername()                   const;
    _String     GetPassword()                   const;
    _String     GetPath()                       const;
    _String     GetAbsPath()                    const;
    _String     GetDirectory()                  const;
    _String     GetFilename()                   const;
    _String     GetType()                       const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FTP_URL_H__


////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FTP_URL_H__
#define __PALM_FTP_URL_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPURL
// ----- ------
class __DECLSPEC__ FTPURL : public URL
{
    // <url>:<ftp>://<username>:<password>@<host>:<port>/<url-path>
    // <url-path> -> <cwd1>/<cwd2>/.../<cwdn>/<name>;type=<typecode>
    public:
     // ctor/dtor
                FTPURL();
                FTPURL(const FTPURL&);
                FTPURL(const char*);
     virtual   ~FTPURL();

     // operators
     bool       operator == (const FTPURL&)     const;
     bool       operator == (const char*)       const;
     bool       operator != (const FTPURL&)     const;
     bool       operator != (const char*)       const;

     // api
    _string     GetHost()                       const;
     uint16     GetPort()                       const;
    _string     GetUsername()                   const;
    _string     GetPassword()                   const;
    _string     GetPath()                       const;
    _string     GetAbsPath()                    const;
    _string     GetDirectory()                  const;
    _string     GetFilename()                   const;
    _string     GetType()                       const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FTP_URL_H__


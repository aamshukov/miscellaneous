////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_HTTP_URL_H__
#define __PALM_HTTP_URL_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPURL
// ----- -------
class __DECLSPEC__ HTTPURL : public URL
{
    // <url>:<http>://<host>:<port>/<path>?<searchpart>
    public:
     // ctor/dtor
                HTTPURL();
                HTTPURL(const HTTPURL&);
                HTTPURL(const char*);
     virtual   ~HTTPURL();

     // operators
     bool       operator == (const HTTPURL&)        const;
     bool       operator == (const char*)           const;
     bool       operator != (const HTTPURL&)        const;
     bool       operator != (const char*)           const;

     // api
    _string     GetHost()                           const;
     uint16     GetPort()                           const;
    _string     GetPath()                           const;
    _string     GetAbsPath()                        const;
    _string     GetDirectory()                      const;
    _string     GetFilename()                       const;
    _string     GetParam()                          const;
    _string     GetQuery()                          const;
    _string     GetRef()                            const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_HTTP_URL_H__


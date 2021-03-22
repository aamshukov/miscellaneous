////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HTTP_URL_H__
#define __HTTP_URL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HTTPURL
// ----- -------
class __DECLSPEC__ HTTPURL : public URL
{
    // <URL>:<http>://<host>:<port>/<path>?<searchpart>
    typedef String<> _String;

    public:
     // ctor/dtor
                HTTPURL();
                HTTPURL(const HTTPURL&);
                HTTPURL(const tchar*);
     virtual   ~HTTPURL();

     // operators
     bool       operator == (const HTTPURL&)        const;
     bool       operator == (const tchar*)          const;
     bool       operator != (const HTTPURL&)        const;
     bool       operator != (const tchar*)          const;

     // protocol
    _String     GetHost()                           const;
     ushort     GetPort()                           const;
    _String     GetPath()                           const;
    _String     GetAbsPath()                        const;
    _String     GetDirectory()                      const;
    _String     GetFilename()                       const;
    _String     GetParam()                          const;
    _String     GetQuery()                          const;
    _String     GetRef()                            const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HTTP_URL_H__


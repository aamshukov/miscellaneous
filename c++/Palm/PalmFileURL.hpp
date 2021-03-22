////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FILE_URL_H__
#define __PALM_FILE_URL_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FileURL
// ----- -------
class __DECLSPEC__ FileURL : public URL
{
    // <url>:<file>://<host|"localhost">/<file-path>
    // url:file:///C|/cwd1/cwd2/file.txt
    public:
     // ctor/dtor
                FileURL();
                FileURL(const FileURL&);
                FileURL(const char*);
     virtual   ~FileURL();

     // operators
     bool       operator == (const FileURL&)        const;
     bool       operator == (const char*)           const;
     bool       operator != (const FileURL&)        const;
     bool       operator != (const char*)           const;

     // api
    _string     GetHost()                           const;
    _string     GetPath()                           const;
    _string     GetAbsPath()                        const;
    _string     GetDirectory()                      const;
    _string     GetFilename()                       const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FILE_URL_H__


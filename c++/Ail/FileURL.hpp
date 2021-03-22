////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FILE_URL_H__
#define __FILE_URL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FileURL
// ----- -------
class __DECLSPEC__ FileURL : public URL
{
    // <URL>:<file>://<host|"localhost">/<file-path>
    // URL:file:///C|/cwd1/cwd2/file.txt
    typedef String<> _String;

    public:
                FileURL();
                FileURL(const FileURL&);
                FileURL(const tchar*);
     virtual   ~FileURL();

     bool       operator == (const FileURL&)    const;
     bool       operator == (const tchar*)      const;
     bool       operator != (const FileURL&)    const;
     bool       operator != (const tchar*)      const;

    _String     GetHost()                       const;
    _String     GetPath()                       const;
    _String     GetAbsPath()                    const;
    _String     GetDirectory()                  const;
    _String     GetFilename()                   const;
    _String     GetLocalFile()                  const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FILE_URL_H__


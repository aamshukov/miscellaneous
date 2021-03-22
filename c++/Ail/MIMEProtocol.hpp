////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MIME_PROTOCOL_H__
#define __MIME_PROTOCOL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MIMEProtocol
// ----- ------------
class __DECLSPEC__ MIMEProtocol
{
    public:
     static bool    GetContentType(const tchar*, tchar*, uint);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MIME_PROTOCOL_H__

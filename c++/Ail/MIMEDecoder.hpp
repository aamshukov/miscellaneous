////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MIME_DECODER_H__
#define __MIME_DECODER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MIMEDecoder
// ----- -----------
class __DECLSPEC__ MIMEDecoder
{
    protected:
     // base-64
     static uint    Get3To4(uint);
     static uint    Get4To3(uint);
     static byte    GetTableEntry(byte);
    public:
     // base-64
     static void    EncodeBase64(const byte*, uint, byte*);
     static void    DecodeBase64(const byte*, uint, byte*);

     // uuencode (quoted-printable)
     static void    UUEncode(const byte*, uint, byte*);
     static void    UUDecode(const byte*, uint, byte*);

     // binhex
     static void    BinHexEncode(const byte*, uint, byte*);
     static void    BinHexDecode(const byte*, uint, byte*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MIME_DECODER_H__

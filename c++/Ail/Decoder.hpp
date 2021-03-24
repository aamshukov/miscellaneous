////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __DECODER_H__
#define __DECODER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Decoder
// ----- -------
// GOST (USSR) algorithm
class Decoder
{
    private:
     uint         K[8];

     static byte  K87[256];
     static byte  K65[256];
     static byte  K43[256];
     static byte  K21[256];
    private:
     uint         F(uint);
     void         Encode(uint*);
     void         Decode(uint*);
    public:
                  Decoder();
                 ~Decoder();

     void         SetupKey(const byte*);
     void         DestroyKey();

     void         Encode(byte*, uint);
     void         Decode(byte*, uint);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __DECODER_H__

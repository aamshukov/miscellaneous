////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef _Decoder_INC__
#   include <Decoder.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Decoder
// ----- -------
byte Decoder::K87[] = { 0 };
byte Decoder::K65[] = { 0 };
byte Decoder::K43[] = { 0 };
byte Decoder::K21[] = { 0 };

Decoder::Decoder()
{
    InitMemory(K, sizeof(K));
    
    if(Decoder::K87[0] == 0)
    {
        // init
        const byte k8[16] = { 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7 };
        const byte k7[16] = { 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10 };
        const byte k6[16] = { 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8 };
        const byte k5[16] = {  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15 };
        const byte k4[16] = {  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9 };
        const byte k3[16] = { 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11 };
        const byte k2[16] = {  4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1 };
        const byte k1[16] = { 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7 };

        for(register ushort i = 0; i < 256; i++)
        {
            Decoder::K87[i] = k8[i >> 4] << 4 | k7[i & 15];
            Decoder::K65[i] = k6[i >> 4] << 4 | k5[i & 15];
            Decoder::K43[i] = k4[i >> 4] << 4 | k3[i & 15];
            Decoder::K21[i] = k2[i >> 4] << 4 | k1[i & 15];
        }
    }
}

Decoder::~Decoder()
{
}

uint Decoder::F(uint _x)
{
    _x = (Decoder::K87[_x >> 24 & 255] << 24) | (Decoder::K65[_x >> 16 & 255] << 16) | (Decoder::K43[_x >> 8 & 255] << 8) | Decoder::K21[_x & 255];

    // rotate left 11 bits
    return (_x << 11) | (_x >> (32-1));
}

void Decoder::Encode(uint* _d)
{
    register uint n1 = _d[0];
    register uint n2 = _d[1];;

    n2 ^= F(n1+Decoder::K[0]), n1 ^= F(n2+Decoder::K[1]);
    n2 ^= F(n1+Decoder::K[2]), n1 ^= F(n2+Decoder::K[3]);
    n2 ^= F(n1+Decoder::K[4]), n1 ^= F(n2+Decoder::K[5]);
    n2 ^= F(n1+Decoder::K[6]), n1 ^= F(n2+Decoder::K[7]);

    n2 ^= F(n1+Decoder::K[0]), n1 ^= F(n2+Decoder::K[1]);
    n2 ^= F(n1+Decoder::K[2]), n1 ^= F(n2+Decoder::K[3]);
    n2 ^= F(n1+Decoder::K[4]), n1 ^= F(n2+Decoder::K[5]);
    n2 ^= F(n1+Decoder::K[6]), n1 ^= F(n2+Decoder::K[7]);

    n2 ^= F(n1+Decoder::K[0]), n1 ^= F(n2+Decoder::K[1]);
    n2 ^= F(n1+Decoder::K[2]), n1 ^= F(n2+Decoder::K[3]);
    n2 ^= F(n1+Decoder::K[4]), n1 ^= F(n2+Decoder::K[5]);
    n2 ^= F(n1+Decoder::K[6]), n1 ^= F(n2+Decoder::K[7]);

    n2 ^= F(n1+Decoder::K[7]), n1 ^= F(n2+Decoder::K[6]);
    n2 ^= F(n1+Decoder::K[5]), n1 ^= F(n2+Decoder::K[4]);
    n2 ^= F(n1+Decoder::K[3]), n1 ^= F(n2+Decoder::K[2]);
    n2 ^= F(n1+Decoder::K[1]), n1 ^= F(n2+Decoder::K[0]);

    _d[0] = n2;
    _d[1] = n1;
}

void Decoder::Decode(uint* _d)
{
    register uint n1 = _d[0];
    register uint n2 = _d[1];;

    n2 ^= F(n1+Decoder::K[0]), n1 ^= F(n2+Decoder::K[1]);
    n2 ^= F(n1+Decoder::K[2]), n1 ^= F(n2+Decoder::K[3]);
    n2 ^= F(n1+Decoder::K[4]), n1 ^= F(n2+Decoder::K[5]);
    n2 ^= F(n1+Decoder::K[6]), n1 ^= F(n2+Decoder::K[7]);

    n2 ^= F(n1+Decoder::K[7]), n1 ^= F(n2+Decoder::K[6]);
    n2 ^= F(n1+Decoder::K[5]), n1 ^= F(n2+Decoder::K[4]);
    n2 ^= F(n1+Decoder::K[3]), n1 ^= F(n2+Decoder::K[2]);
    n2 ^= F(n1+Decoder::K[1]), n1 ^= F(n2+Decoder::K[0]);

    n2 ^= F(n1+Decoder::K[7]), n1 ^= F(n2+Decoder::K[6]);
    n2 ^= F(n1+Decoder::K[5]), n1 ^= F(n2+Decoder::K[4]);
    n2 ^= F(n1+Decoder::K[3]), n1 ^= F(n2+Decoder::K[2]);
    n2 ^= F(n1+Decoder::K[1]), n1 ^= F(n2+Decoder::K[0]);

    n2 ^= F(n1+Decoder::K[7]), n1 ^= F(n2+Decoder::K[6]);
    n2 ^= F(n1+Decoder::K[5]), n1 ^= F(n2+Decoder::K[4]);
    n2 ^= F(n1+Decoder::K[3]), n1 ^= F(n2+Decoder::K[2]);
    n2 ^= F(n1+Decoder::K[1]), n1 ^= F(n2+Decoder::K[0]);

    _d[0] = n2;
    _d[1] = n1;
}

void Decoder::SetupKey(const byte* _key)
{
    byte key[32];

    register ushort k = 0;

    while(_key[k] != 0)
    {
        key[k] = _key[k];
        ++k;
    }

    while(k+1 < 32)
    {
        key[k++] = 1;
    }

    for(register ushort i = 0, j = 0; i < 32; i += 4)
    {
        K[j]  = key[i+0] << 24;
        K[j] |= key[i+1] << 16;
        K[j] |= key[i+2] << 8;
        K[j] |= key[i+3];

        ++j;
    }
}

void Decoder::DestroyKey()
{
    InitMemory(K, sizeof(K));
}

void Decoder::Encode(byte* _buffer, uint _size)
{
    if(_buffer != null)
    {
        register uint offset = 0;

        for(register uint i = 0; i < _size/8; i++)
        {
            Encode(reinterpret_cast<uint*>(_buffer+offset));
            offset += 8;
        }
    }
}

void Decoder::Decode(byte* _buffer, uint _size)
{
    if(_buffer != null)
    {
        register uint offset = 0;

        for(register uint i = 0; i < _size/8; i++)
        {
            Decode(reinterpret_cast<uint*>(_buffer+offset));
            offset += 8;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

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

#ifndef __MIME_DECODER_INC__
#   include <MIMEDecoder.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MIMEDecoder
// ----- -----------
uint MIMEDecoder::Get3To4(uint _count)
{
    return (_count/3+(_count%3 ? 1 : 0))*4;
}

uint MIMEDecoder::Get4To3(uint _count)
{
    return (_count/4+(_count%4 ? 1 : 0))*3;
}

byte MIMEDecoder::GetTableEntry(byte _in)
{
    switch(_in)
    {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
        case 'I':
            return 8;
        case 'J':
            return 9;
        case 'K':
            return 10;
        case 'L':
            return 11;
        case 'M':
            return 12;
        case 'N':
            return 13;
        case 'O':
            return 14;
        case 'P':
            return 15;
        case 'Q':
            return 16;
        case 'R':
            return 17;
        case 'S':
            return 18;
        case 'T':
            return 19;
        case 'U':
            return 20;
        case 'V':
            return 21;
        case 'W':
            return 22;
        case 'X':
            return 23;
        case 'Y':
            return 24;
        case 'Z':
            return 25;
        case 'a':
            return 26;
        case 'b':
            return 27;
        case 'c':
            return 28;
        case 'd':
            return 29;
        case 'e':
            return 30;
        case 'f':
            return 31;
        case 'g':
            return 32;
        case 'h':
            return 33;
        case 'i':
            return 34;
        case 'j':
            return 35;
        case 'k':
            return 36;
        case 'l':
            return 37;
        case 'm':
            return 38;
        case 'n':
            return 39;
        case 'o':
            return 40;
        case 'p':
            return 41;
        case 'q':
            return 42;
        case 'r':
            return 43;
        case 's':
            return 44;
        case 't':
            return 45;
        case 'u':
            return 46;
        case 'v':
            return 47;
        case 'w':
            return 48;
        case 'x':
            return 49;
        case 'y':
            return 50;
        case 'z':
            return 51;
        case '0':
            return 52;
        case '1':
            return 53;
        case '2':
            return 54;
        case '3':
            return 55;
        case '4':
            return 56;
        case '5':
            return 57;
        case '6':
            return 58;
        case '7':
            return 59;
        case '8':
            return 60;
        case '9':
            return 61;
        case '+':
            return 62;
        case '/':
            return 63;
        case '=':
            return 64;
    }

    return 0xFF;
}

// 'in'    should be 3              ! ...
// 'out'   should be 3+1            ! ...
// 'count' should be count % 3 = 0  ! ...
void MIMEDecoder::EncodeBase64(const byte* _in, uint _length, byte* _out)
{
    static const byte _table_[] =
    {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
        '='
    };
    //
    xassertv(_in != null && _length > 0 && _out != null);
    //
    *_out = 0;

    // Phase I - up to length/3
    uint _count  = _length/3;
         _count *= 3;
     
    for(uint i = 0, j = 0; i < _count; i += 3, j += 4)
    {
        _out[j+0] = _table_[(_in[i+0] >> 2) & 0x3F];
        _out[j+1] = _table_[(((_in[i+0] & 0x03) << 4) | ((_in[i+1] & 0xF0) >> 4)) & 0x3F];
        _out[j+2] = _table_[(((_in[i+1] & 0x0F) << 2) | ((_in[i+2] & 0xC0) >> 6)) & 0x3F];
        _out[j+3] = _table_[_in[i+2] & 0x3F];
    }

    // Phase II - padding
    if(_length%3)
    {
        byte tmp0 = _in[i+0];
        byte tmp1 = _length%3 == 2 ? _in[i+1] : 0;
        byte tmp2 = 0;

        _out[j+0] = _table_[(tmp0 >> 2) & 0x3F];
        _out[j+1] = _table_[(((tmp0 & 0x03) << 4) | ((tmp1 & 0xF0) >> 4)) & 0x3F];
        
        if(tmp1 != 0)
        {
            _out[j+2] = _table_[(((tmp1 & 0x0F) << 2) | ((tmp2 & 0xC0) >> 6)) & 0x3F];
        }

        j += 4;

        short padding = 3-_length%3;

        while(padding--)
        {
            _out[j-padding-1] = Char::Equal;
        }
    }
}

// 'in'    should be 3+1           ! ...
// 'out'   should be 3             ! ...
// 'count' should be count % 4 = 0 ! ...
void MIMEDecoder::DecodeBase64(const byte* _in, uint _count, byte* _out)
{
    xassertv(_in != null && _count > 0 && _out != null);
    //
    *_out = 0;

    if(_in == 0 || _out == 0 || _count == 0)
    {
        return;
    }

    for(uint i = 0, j = 0; i < _count; i += 4, j += 3)
    {
        byte tmp0 = GetTableEntry(_in[i+0]);
        byte tmp1 = GetTableEntry(_in[i+1]);
        byte tmp2 = GetTableEntry(_in[i+2]);
        byte tmp3 = GetTableEntry(_in[i+3]);

        if(tmp2 == 64) // ConstSymbolEqual
        {
            tmp2 = 0;
        }
        if(tmp3 == 64) // ConstSymbolEqual
        {
            tmp3 = 0;
        }

        _out[j+0] = (tmp0 << 2) | (tmp1 >> 4);
        _out[j+1] = ((tmp1 & 0x0F) << 4) | ((tmp2 >> 2) & 0x0F);
        _out[j+2] = (tmp2 << 6) | tmp3;
    }
}

// routines to convert a buffer of bytes to/from RFC 1113 printable encoding format
// takes up 33% more bytes
// borrowed form wwwlib
static const byte _six2pr_[] =
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};
//
void MIMEDecoder::UUEncode(const byte* _in, uint _count, byte* _out)
{
    xassertv(_in != null && _count <= 48 && _out != null);
    //
    byte* p_in  = const_cast<byte*>(_in);
    byte* p_out = _out;

    for(uint i = 0; i < _count; i += 3)
    {
       *p_out++ = _six2pr_[*_in >> 2];                                      // c1
       *p_out++ = _six2pr_[((*_in << 4) & 060) | ((_in[1] >> 4) & 017)];    // c2
       *p_out++ = _six2pr_[((_in[1] << 2) & 074) | ((_in[2] >> 6) & 03)];   // c3
       *p_out++ = _six2pr_[_in[2] & 077];                                   // c4
       _in += 3;
    }

    // if nbytes was not a multiple of 3, then we have encoded too many characters - adjust appropriately
    if(i == _count+1)
    {
        // there were only 2 bytes in that last group
        p_out[-1] = Char::Equal;
    }
    else if(i == _count+2)
    {
        // there was only 1 byte in that last group
        p_out[-1] = Char::Equal;
        p_out[-2] = Char::Equal;
    }
   *p_out = 0;
}

void MIMEDecoder::UUDecode(const byte* _in, uint _count, byte* _out)
{
    xassertv(_in != null && _count > 0 && _out != null);
    //
    static bool _init_ = 1;
    static byte _pr2six_[256];
    //
    byte* p_in  = const_cast<byte*>(_in);
    byte* p_out = _out;

    // phase I (init table)
    if(_init_)
    {
        _init_ = false;

        for(ushort j = 0; j < sizeof(_pr2six_); j++)
        {
            _pr2six_[j] = 63+1;
        }

        for(ushort k = 0; k < 64; k++)
        {
            _pr2six_[_six2pr_[k]] = static_cast<byte>(k);
        }
    }

    // phase II (process)
    while(*p_out == Char::Space || *_out == Char::HTab)
    {
        ++p_out;
    }

    p_in = p_out;

    while(_pr2six_[*(p_in++)] <= 63)
    {
    }

    uint prcount = p_in-p_out-1;
    uint decodedcount = ((prcount+3)/4)*3;

    if(decodedcount > _count)
    {
        prcount = (_count*4)/3;
    }

    p_in = p_out;
   
    while(prcount > 0)
    {
       *p_out++ = static_cast<byte>(_pr2six_[*p_in]   << 2 | _pr2six_[p_in[1]] >> 4);
       *p_out++ = static_cast<byte>(_pr2six_[p_in[1]] << 4 | _pr2six_[p_in[2]] >> 2);
       *p_out++ = static_cast<byte>(_pr2six_[p_in[2]] << 6 | _pr2six_[p_in[3]]);
        p_in += 4, prcount -= 4;
    }
}

void MIMEDecoder::BinHexEncode(const byte* _in, uint _count, byte* _out)
{
    xassertv(_in != null && _count > 0 && _out != null);
    //
    static const byte _table_[] =
    {
        '!', '\"', '#', '$', '%', '&', '\'', '(',
        ')', '*', '+', ',', '-', ' ', '0',  '1',
        '2', '3', '4', '5', '6', '8', '9',  '@',
        'A', 'B', 'C', 'D', 'E', 'F', 'G',  'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'P',  'Q',
        'R', 'S', 'T', 'U', 'V', 'X', 'Y',  'Z',
        '[', '`', 'a', 'b', 'c', 'd', 'e',  'f',
        'h', 'i', 'j', 'k', 'l', 'm', 'p',  'q', 'r'
    };
}

void MIMEDecoder::BinHexDecode(const byte* _in, uint _count, byte* _out)
{
    xassertv(_in != null && _count <= 48 && _out != null);
    //
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

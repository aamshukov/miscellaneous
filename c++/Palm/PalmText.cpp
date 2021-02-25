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

#ifndef __PALM_TEXT_INC__
#   include <PalmText.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmText
// ----- --------
/////////////////////////////////
#define ishex(_x)               \
    (_x >= '0' && _x <= '9' ||  \
     _x == 'a' || _x == 'A' ||  \
     _x == 'b' || _x == 'B' ||  \
     _x == 'c' || _x == 'C' ||  \
     _x == 'd' || _x == 'D' ||  \
     _x == 'e' || _x == 'E' ||  \
     _x == 'f' || _x == 'F')    \
/////////////////////////////////

int32 PalmText::StrCompareWithEsc(const char* _s1, const char* _s2)
{
    int16 ret = 0;

    if(_s1 != null && _s2 != null)
    {
        for(;;)
        {
            char c1;
            char c2;
            char term[4];

            if(*_s1 == Char::Percent)
            {
                term[0] = *++_s1;
                term[1] = *++_s1;
                term[2] = 0;
                c1 = static_cast<char>(PalmText::StrAToI(reinterpret_cast<const char*>(&term)));
            }
            else
            {
                c1 = *_s1;
            }

            ++_s1;

            if(*_s2 == Char::Percent)
            {
                term[0] = *++_s2;
                term[1] = *++_s2;
                term[2] = 0;
                c2 = static_cast<char>(PalmText::StrAToI(reinterpret_cast<const char*>(&term)));
            }
            else
            {
                c2 = *_s2;
            }

            ++_s2;

            ret = static_cast<int16>(c1-c2);

            if(c1 == 0 || c2 == 0)
            {
                break;
            }
        }
    }
    return ret;
}

int32 PalmText::StrICompareWithEsc(const char* _s1, const char* _s2)
{
    int16 ret = 0;

    if(_s1 != null && _s2 != null)
    {
        for(;;)
        {
            char c1;
            char c2;
            char term[4];

            if(*_s1 == Char::Percent)
            {
                term[0] = *++_s1;
                term[1] = *++_s1;
                term[2] = 0;
                c1 = static_cast<char>(PalmText::StrAToI(reinterpret_cast<const char*>(&term)));
            }
            else
            {
                c1 = *_s1;
            }

            ++_s1;

            if(*_s2 == Char::Percent)
            {
                term[0] = *++_s2;
                term[1] = *++_s2;
                term[2] = 0;
                c2 = static_cast<char>(PalmText::StrAToI(reinterpret_cast<const char*>(&term)));
            }
            else
            {
                c2 = *_s2;
            }

            ++_s2;

            term[0] = c1;
            term[1] = 0;
            term[2] = c2;
            term[3] = 0;

            if(c1 > 32 && c1 < 128)
            {
                char tmp[2];
                tmp[0] = term[0];
                tmp[1] = 0;
                PalmText::StrToLower(reinterpret_cast<char*>(&term[0]), reinterpret_cast<char*>(&tmp[0]));
            }

            if(c2 > 32 && c2 < 128)
            {
                char tmp[2];
                tmp[0] = term[2];
                tmp[1] = 0;
                PalmText::StrToLower(reinterpret_cast<char*>(&term[2]), reinterpret_cast<char*>(&tmp[0]));
            }

            ret = static_cast<int16>(term[0]-term[2]);

            if(c1 == 0 || c2 == 0)
            {
                break;
            }
        }
    }
    return ret;
}

void PalmText::ConvertEsc(char* _s, bool _strict)
{
    // the goal of the function is as follows (RFC 1738):
    //  trim leading, trailing and internal spaces
    //  encode all non US-ASCII chars 80-FF with escape (%xx)
    //  encode all ctl chars 00-1F & 7F with escape (%xx)
    //  if %xx is %hexhex DO NOT touch
    //  indeed, coonverts just unsafe chars!
    if(_s == null)
    {
        return;
    }
    // for non windows 
    AutoPtrArray<char> buffer = new char[PalmText::StrLen(_s)*3+1]; // *3 -> %xx
    buffer[0] = 0;

    char* p_buff = buffer;
    char* p_curr = _s;

    // do not touch username/password
    if(PalmText::StrChar(p_curr, Char::At) != null)
    {
        while(*p_curr != 0 && *p_curr != Char::At)
        {
            *p_buff++ = *p_curr++;
        }
    }

    while(*p_curr != 0)
    {
        if(IsUnsafeChar(*p_curr))
        {
            if(*p_curr == Char::Percent && _strict ? ishex(*(p_curr+1)) && ishex(*(p_curr+2)) : true)
            {
                // do not touch
                *p_buff++ = *p_curr++;
                *p_buff++ = *p_curr++;
                *p_buff++ = *p_curr++;
                continue;
            }

            char term[8];
            compose(term, _t("%x"), *p_curr);

           *p_buff++ = Char::Percent;
           *p_buff++ = term[0];
           *p_buff++ = term[1];
            p_curr++;

            p_curr = PalmText::SkipSymbols(p_curr, Char::SPTAB);
        }
        else if(*p_curr != Char::Space && *p_curr != Char::HTab)
        {
            *p_buff++ = *p_curr++;
        }
        else
        {
            ++p_curr;
        }
    }

    *p_buff = 0;

    PalmText::StrCopy(_s, buffer);
}

void PalmText::RemoveEsc(char* _s, bool _strict)
{
    // extra condition:
    //  if %xx is !%hexhex && _strict DO NOT touch
    if(_s == null)
    {
        return;
    }
    //
    AutoPtrArray<char> buffer = new char[PalmText::StrLen(_s)+1];
    buffer[0] = 0;

    char* p_buff = buffer;
    char* p_curr = _s;

    while(*p_curr != 0)
    {
        if(*p_curr == Char::Percent && _strict ? (ishex(*(p_curr+1)) && ishex(*(p_curr+2))) : true)
        {
            char term[4];
            term[0] = *++p_curr;
            term[1] = *p_curr++;
            term[3] = 0;
            *p_buff++ = char(PalmText::StrAToI(term));
             p_curr++;
        }
        else
        {
            *p_buff++ = *p_curr++;
        }
    }

    *p_buff = 0;

    PalmText::StrCopy(_s, buffer);
}

/////////////////////////////////////////
#undef ishex
/////////////////////////////////////////

bool PalmText::IsUnsafeChar(char _symbol)
{
    // internet related
    static const char* _unsafechars_ = " <>\"%{}|\\^[]`\033"; // 033 for printers
    return PalmText::StrChar(_unsafechars_, _symbol) != null;
}

bool PalmText::IsNonAsciiChar(char _symbol)
{
    // returns true if _symbol is: 00-1F & 7F | >= 0x80 
    return _symbol >= 0x00 && _symbol <= 0x1F || _symbol == 0x7F || _symbol >= 0x80;
}

void PalmText::TrimSpace(char* _s, uint16 _level)
{
    // level 0 - left, 1 - right, 2 - left & right
    if(_s)
    {
        char* p;
        int16 l;

        if(_level == 0 || _level == 2)
        {
            l = PalmText::StrLen(_s);

            if(l > 0)
            {
                p = _s;

                while(*p && *p == Char::Space)
                {
                    ++p;
                }

                int16 o = static_cast<int16>(p-_s);

                if(o > 0 && l-o > 0)
                {
                    PalmText::StrNCopy(_s, p, static_cast<int16>(l-o));
                }

                *(_s+(l-o)) = 0;
            }
        }

        if(_level == 1 || _level == 2)
        {
            l = PalmText::StrLen(_s);

            if(l > 0)
            {
                p = _s+l-1;

                while(p != _s && *p == Char::Space)
                {
                    --p;
                }

                if(p == _s && *p == Char::Space)
                {
                    *p = 0;
                }
                else
                {
                    *++p = 0;
                }
            }
        }
    }
}

char* PalmText::SkipSymbol(char* _p, char _symbol)
{
    if(_p != null)
    {
        while(*_p && *_p == _symbol)
        {
            ++_p;
        }
        return _p;
    }
    return null;
}

char* PalmText::SkipSymbols(char* _p, const char* _delim)
{
    if(_p == null)
    {
        return null;
    }

    const char* p_del = _delim != null ? _delim : _t(" \t");

    if(_delim == null)
    {
        // common case
        while(*_p != 0 && (*_p == *(p_del+0) || *_p == *(p_del+1)))
        {
            ++_p;
        }
    }
    else
    {
        // init map
        byte map[32];
        PalmOS::MemSet(&map, sizeof(map));

        do
        {
            map[*p_del >> 3] |= byte(1 << (*p_del & 7));
        }
        while(*p_del++ != 0);

        //
        while(*_p != 0 && (map[*_p >> 3] & (1 << (*_p & 7))) != 0)
        {
            ++_p;
        }
    }
    return _p;
}

char* PalmText::SkipTo(char* _p, char _symbol)
{
    if(_p != null)
    {
        while(*_p != 0 && *_p != _symbol)
        {
            ++_p;
        }
        return _p;
    }
    return null;
}

char* PalmText::SkipLWS(char* _p)
{
    if(_p != null)
    {
        char* p_curr = _p;
        
        while(*p_curr == Char::Space || *p_curr == Char::HTab || *p_curr == Char::CR || *p_curr == Char::LF)
        {
            ++p_curr;
        }

        return p_curr;
    }
    return null;
}

char* PalmText::GetLine(const char* _buffer, char* _line)
{
    if(_buffer == null || _line == null)
    {
        return null;
    }

    // the _line will include CRLF or CR or LF
    char* p_buff = const_cast<char*>(_buffer);
    char* p_curr = _line;

    while(*p_buff != 0 && *p_buff != Char::CR && *p_buff != Char::LF)
    {
        *p_curr++ = *p_buff++;
    }

    if(*p_buff == Char::CR || *p_buff == Char::LF)
    {
        *p_curr++ = *p_buff++;

        if(*p_buff == Char::CR || *p_buff == Char::LF)
        {
            *p_curr++ = *p_buff++;
        }
    }

    *p_curr = 0;
    return p_buff;
}

_string PalmText::GetString(const char* _p, uint32 _len)
{
    uint32 len = _len == 0 ? StrLen(_p) : _len;
   _string str;

    for(uint32 i = 0; i < len && *_p != 0; i++)
    {
        str += *_p++;
    }
    return str;
}

char* PalmText::HasToken(const char* _buffer, const char* _sample, const char* _delimiters, bool _lower)
{
    if(_buffer == null || _sample == null)
    {
        return null;
    }

    //
    const char* _delimiters_ = _delimiters == null ? _t(" ") : _delimiters;
    //
    char term[128];    // should be enough
    char sample[128];  // should be enough

    const char* p_del  = _delimiters_;
          char* p_buff = const_cast<char*>(_buffer);
          char* p_tok;
          char* p_term;

    PalmText::StrNCopy(sample, _sample, Min(PalmText::StrLen(_sample), static_cast<int16>(128)));
    sample[Min(PalmText::StrLen(_sample), static_cast<int16>(127))] = 0;
    PalmText::StrToLower(sample, sample);

    byte map[32];

    for(byte i = 0; i < sizeof(map); i++)
    {
        map[i] = 0;
    }

    do
    {
        map[*p_del >> 3] |= byte(1 << (*p_del & 7));
    }
    while(*p_del++ != 0);

    while(*p_buff != 0)
    {
        // skip garbage
        while(*p_buff != 0 && (map[*p_buff >> 3] & (1 << (*p_buff & 7))))
        {
            ++p_buff;
        }

        p_tok  = p_buff;
        p_term = term;

        while(*p_buff != 0 && !(map[*p_buff >> 3] & (1 << (*p_buff & 7))))
        {
            *p_term++ = *p_buff++;
        }

        *p_term = 0;

        if(_lower)
        {
            PalmText::StrToLower(term, term);
        }

        if(PalmText::StrCompare(term, sample) == 0)
        {
            return p_tok;
        }
    }
    return null;
}

char* PalmText::StrChar(const char* _s, char _ch)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    //
    while(*_s != 0 && *_s != _ch)
    {
        _s++;
    }
    return *_s == _ch ? const_cast<char*>(_s) : null;
}

char* PalmText::StrRChar(const char* _s, char _ch)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    //
    const char* start = _s;

    while(*_s++)
    {
        ;
    }
    
    while(--_s != start && *_s != _ch)
    {
        ;
    }
    return *_s == _ch ? const_cast<char*>(_s) : null;
}

uint32 PalmText::StrHToI(const char* _s)
{
    palmxassert(_s != null, Error::eInvalidArg, Error);
    //
    const char* p;

    char   c; // current char
    uint32 n; // result number
    uint32 d; // digit value

    p = _s;
    n = 0;

    c = *p++;
    
    while(TxtCharIsSpace(c))
    {
        c = *p++;
    }

    // skip 0x
    if(c == '0' && (*p == 'x' || *p == 'X'))
    {
        ++p;
        c = *p++; // next char
    }

    for(;;)
    {
        if(TxtCharIsDigit(c))
        {
            d = static_cast<uint32>(c-'0');
        }
        else if(TxtCharIsAlpha(c))
        {
            char term[2];
                 term[0] = c;
                 term[1] = 0;
            
            StrToLower(term, term);

            d = static_cast<uint32>(term[0]-'a'+10);
        }
        else
        {
            break;
        }

        if(d >= 16) // only base 16
        {
            break;
        }

        n = n*16+d;
        c = *p++;
    }
    return n;
}

void PalmText::Str64ToA(uint64 _x, char* _buffer)
{
    palmxassert(_buffer != null, Error::eInvalidArg, Error);
    //
    char* p_buff = _buffer;
    char* p_curr = _buffer;

    do
    {
        uint16 d; // digit

        d  = static_cast<uint16>(_x % 16);
       _x /= 16;

        if(d > 9)
        {
            *p_curr++ = static_cast<char>(d-10+'a');
        }
        else
        {
            *p_curr++ = static_cast<char>(d+'0');
        }
    }
    while(_x > 0);

    *p_curr-- = 0;

    while(p_buff < p_curr)
    {
        char ch = *p_curr;
        *p_curr = *p_buff;
        *p_buff = ch;

        --p_curr, ++p_buff;
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

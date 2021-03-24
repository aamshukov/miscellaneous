////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __VALIDATOR_INC__
#   include <Validator.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
const tchar  ConstStrFreeInput[]    = _t("[@|&*]");
const byte   ConstDeepLevel         = 64;
const byte   ConstMaxSizeNumber     = 8;
const ushort ConstMaxNumberOfRepeat = 4096;
////////////////////////////////////////////////////////////////////////////////////////
// class ValidatorEntry
// ----- --------------
ValidatorEntry::ValidatorEntry(tchar _c, uint _o)
{
    Entry = _c;
    Flags = _o;
    Index = -1;
}

ValidatorEntry::~ValidatorEntry()
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class Validator
// ----- ---------
Validator::Validator(tchar* _mask, tchar _plstr, tchar _plgrp, tchar _plmsk, tchar _plpswd, uint _flags, bool _init) : ListString(KeyExtractor, Comparator), Bits(CHARACTER_COUNT)
{
    FreeInput           = false;
    PlaceholderString   = _plstr;
    PlaceholderGroup    = _plgrp;
    PlaceholderMask     = _plmsk;
    PlaceholderPassword = _plpswd;
    Position            = -1;
    Flags               = _flags;

    if(_init)
    {
        Init(_mask);
    }
}

Validator::~Validator()
{
    ListString.Destroy();
}

void Validator::Init(tchar* _p)
{
    BuildMask(_p);
    CorrectMask();
    CheckSyntax();
    BuildString();
    BuildFormatString();
    SetupDefault();
    FindFirstVacantPlace();
}

void Validator::BuildMask(tchar* _p)
{
    Mask = _p;

    if(Mask.IsEmpty())
    {
        Mask = ConstStrFreeInput;
        return;
    }
}

void Validator::CorrectMask()
{
    tchar* p = const_cast<tchar*>(Mask.GetData());
    tchar* p1;

    if(p == null)
    {
        return;
    }

    TCharStr str;

    while(*p != 0)
    {
        switch(*p)
        {
            case _t('{'): // Char::BraceLeft
                p = SkipMask(++p);
                break;
            case _t('['): // Char::BracketLeft:
                p1 = p;
                p  = GetFreeInput(++p);

                if(FreeInput)
                {
                    p = p1;
                    GetSubmask(str, p);
                    Mask = str;
                    return;
                }
                break;
            case _t('\\'): // Char::BackSlash:
                if(*(++p) != 0)
                {
                    ++p;
                }
                break;
            default:
                ++p;
                break;
        }
    }
}

tchar* Validator::GetFreeInput(tchar* _p, int _level)
{
    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    tchar* p = _p;

    if(p == null)
    {
        return null;
    }

    while(*p != 0)
    {
        switch(*p)
        {
            case _t('@'): // Char::At:
                FreeInput = true;
                ++p;
                break;
            case _t('['): // Char::BracketLeft:
                p = GetFreeInput(++p, _level+1);
                break;
            case _t(']'): // Char::BracketRight:
                return ++p;
            case _t('&'): // Char::Ampersand:
                if(*(++p) == 0 || (*p != 'A') && (*p != 'a') && (*p != 'L') && (*p != 'l') && (*p != '0') && (*p != '9') && (*p != Char::NumberSign) && (*p != 'E') && (*p != Char::Period) && (*p != Char::Asterisk))
                {
                    throw Validator::XValidator(XValidator::InvalidSyntax);
                }
                ++p;
                break;
            case _t('\\'): // Char::BackSlash:
                if(*(++p) != 0)
                {
                    ++p;
                }
                break;
            default:
                ++p;
                break;
        }
    }
    return p;
}

void Validator::CheckSyntax()
{
    // doesn`t support order ! ...
    if(Mask.IsEmpty())
    {
        return;
    }

    int brklevel = 0;
    int brclevel = 0;

    tchar* p = const_cast<tchar*>(Mask.GetData());

    if(p == null)
    {
        return;
    }

    while(*p != 0)
    {
        switch(*p++) 
        {
            case _t('['): // Char::BracketLeft: 
                ++brklevel;
                break;
            case _t(']'): // Char::BracketRight: 
                --brklevel;
                break;
            case _t('{'): // Char::BraceLeft 
                ++brclevel;
                break;
            case _t('}'): // Char::BraceRight: 
                --brclevel;
                break;
            case _t('\\'): // Char::BackSlash:
                if(*p != 0)
                {
                    ++p;
                }
                break;
        }
    }

    if(brklevel != 0 || brclevel != 0)
    {
        throw Validator::XValidator(XValidator::InvalidSyntax);
    }
}

tchar* Validator::GetNextSubstring(tchar* _p, TCharStr& _str)
{
    bool   flag = false;
    tchar* p = _p;

    if(p == null)
    {
        return null;
    }

    while(*p != 0)
    {
        switch(*p)
        {
            case _t('['): // Char::BracketLeft:
                p = SkipGroup(++p);
                
                if(flag)
                {
                    return p;
                }
                break;
            case _t('{'): // Char::BraceLeft
                p = SkipMask(++p);
                
                if(flag)
                {
                    return p;
                }
                break;
            case _t('\\'): // Char::BackSlash:
                if(*(++p) != 0)
                {
                    _str += *p++;
                }
                
                flag = true;
                break;
            default:
                _str += *p++;
                flag = true;
                break;
        }
    }
    return p;
}

tchar* Validator::BuildString(tchar* _p, bool _ismask, int _level)
{
    if(FreeInput)
    {
        return null;
    }

    tchar* p = _p ? _p : const_cast<tchar*>(Mask.GetData());
    int    n;

    if(p == null)
    {
        return null;
    }

    TCharStr str;

    while(*p != 0)
    {
        switch(*p)
        {
            case _t('{'): // Char::BraceLeft
                p = BuildString(++p, true, _level+1);
                break;
            case _t('}'): // Char::BraceRight
                return ++p;
            case _t('['): // Char::BracketLeft
                GetSubmask(str, p); 

                if(_ismask)
                {
                    p = SkipGroup(++p);
                    AddEntry(str, (Flags & DisplayAsPassword) ? PlaceholderPassword : PlaceholderMask, ValidatorEntry::Mask|ValidatorEntry::Letter);
                }
                else
                {
                    n = 0; 
                    p = GetRepeatSymbolsFromGroup(++p, n);

                    for(int i = 0; i < (n == 0 ? 1 : n); i++)
                    {
                        AddEntry(str, (Flags & DisplayAsPassword) ? PlaceholderPassword : PlaceholderGroup, ValidatorEntry::Group|ValidatorEntry::Letter);
                    }
                }
                break;
            case _t('\\'): // Char::BackSlash
                if(*(++p) != 0)
                {
                    AddEntry(str, *p, _ismask ? ValidatorEntry::Mask|ValidatorEntry::Separator : ValidatorEntry::Substring|ValidatorEntry::Letter);
                    ++p;
                }
                break;
            default:
                AddEntry(str, *p, _ismask ? ValidatorEntry::Mask|ValidatorEntry::Separator : ValidatorEntry::Substring|ValidatorEntry::Letter);
                ++p;
                break;
        }
        str.SetEmpty();
    }
    return p;
}

void Validator::SetupDefault()
{
    TCharStr str;

    if((Flags & AutoDefault) && DefaultValue(str) && !str.IsEmpty() && !FormatString.IsEmpty() && !MirrorString.IsEmpty())
    {
        tchar  c;
        tchar* p = const_cast<tchar*>(str.GetData());
        uint   f;

        for(int i = 0; i < int(ListString.GetCount()), p, *p; i++)
        {
            f = ListString[i].GetFlags();

            if(f & ValidatorEntry::Letter)
            {
                if(Flags & DisplayAsPassword)
                {
                    c = PlaceholderPassword;
                }
                else
                {
                    c = *p;
                }
                FormatString.SetAt(i, c);
                MirrorString.SetAt(i, *p);
                ++p;
            }
        }
    }
}

void Validator::AddEntry(TCharStr& _str, tchar _c, uint _f)
{
    ValidatorEntry* e = new ValidatorEntry(_c, _f);

    if(!_str.IsEmpty())
    {
        for(int i = 0; i < int(ListString.GetCount()); i++)
        {
            if(ListString[i].Submask == _str)
            {
                e->SetSubmaskAsIndex(i);
                goto _skip;
            }
        }
        e->SetSubmaskAsStr(_str);
    }

_skip:
    ListString.LinkTail(e);
}

tchar* Validator::GetSubmask(TCharStr& _str, tchar* _p, int _level)
{
    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    tchar* p = _p;

    if(p == null)
    {
        return null;
    }

    _str += *p++;

    while(*p != 0)
    {
        switch(*p)
        {
            case _t('['): // Char::BracketLeft
                p = GetSubmask(_str, p, _level+1);
                break;
            case _t(']'): // Char::BracketRight
                _str += *p++;
                return p;
            default:
                _str += *p++;
                break;
        }
    }
    return p;
}

void Validator::BuildFormatString(int _start, int _end, bool _flag)
{
    if(FreeInput) 
    {
        return;
    }

    tchar c;
    uint  f;

    if(_flag)
    {
        f = ListString[_start].GetFlags();

        if((f & ValidatorEntry::Substring) != 0)
        {
            if((f & ValidatorEntry::Letter) != 0)
            {
                if((Flags & DisplayAsPassword) != 0)
                {
                    c = PlaceholderPassword;
                }
                else if(Flags & AutoHint)
                {
                    c = ListString[_start].GetEntry();
                }
                else
                {
                    c = PlaceholderString;
                }
            }
        }
        else
        {
            c = ListString[_start].GetEntry();
        }

        if(_start < static_cast<int>(FormatString.GetCount()))
        {
            FormatString.SetAt(_start, c);
            MirrorString.SetAt(_start, ListString[_start].GetEntry());
        }
        else
        {
            FormatString += c;
            MirrorString += ListString[_start].GetEntry();
        }
    }
    else
    {
        int i = Max(0, _start);
        int n = _end > 0 ? _end : ListString.GetCount();

        for(; i < n; i++)
        {
            f = ListString[i].GetFlags();

            if((f & ValidatorEntry::Substring) != 0)
            {
                if((f & ValidatorEntry::Letter) != 0)
                {
                    if((Flags & DisplayAsPassword) != 0)
                    {
                        c = PlaceholderPassword;
                    }
                    else if(Flags & AutoHint)
                    {
                        c = ListString[i].GetEntry();
                    }
                    else
                    {
                        c = PlaceholderString;
                    }
                }
            }
            else
            {
                c = ListString[i].GetEntry();
            }

            if(i < static_cast<int>(FormatString.GetCount()))
            {
                FormatString.SetAt(i, c);
                MirrorString.SetAt(_start, ListString[_start].GetEntry());
            }
            else
            {
                FormatString += c;
                MirrorString += ListString[i].GetEntry();
            }
        }
    }
}

tchar* Validator::GetRepeatSymbolsFromGroup(tchar* _p, int& _n, int _level)
{
    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    tchar* p = _p;
    tchar  buff[ConstMaxSizeNumber];

    if(p == null)
    {
        return null;
    }

    while(*p != 0 && *p != Char::BracketRight)
    {
        if(*p == Char::Dollar)
        {
            if(*(++p) != 0)
            {
                if(iswdigit(*p))
                {
                    for(int i = 0; i < ConstMaxSizeNumber, *p, iswdigit(*p); i++, p++)
                    {
                        buff[i] = *p;
                    }

                    buff[i] = 0;
                    
                    tchar* ptr;

                    _n = StrToInteger(buff, &ptr, 10);

                    if(_n > ConstMaxNumberOfRepeat)
                    {
                        throw Validator::XValidator(XValidator::InvalidSyntax);
                    }
                }
            }
        }
        else if(*p == Char::BracketLeft)
        {
            p = GetRepeatSymbolsFromGroup(++p, _n, _level+1);
        }
        else 
        {
            ++p;
        }
    }
    return ++p;
}

bool Validator::IsInputValid(tchar _c)
{
    bool valid = false;

    if(FreeInput)
    {
        ArrangeBits();
        valid = Bits.IsON(_c);
        Bits.DisableAllItems();

        if(valid)
        {
            if(Flags & DisplayAsPassword)
            {
                FormatString += PlaceholderPassword;
            }
            else
            {
                FormatString += _c;
            }
            MirrorString += _c;
        }
        return valid;
    }

    if(Position > -1 && Position < static_cast<int>(ListString.GetCount()))
    {
        uint f = ListString[Position].GetFlags();
    
        if((f & ValidatorEntry::Disable) != 0)
        {
            return false;
        }

        if((f & ValidatorEntry::Substring) != 0 && (f & ValidatorEntry::Letter) != 0)
        {
            if(_c == ListString[Position].GetEntry())
            {
                valid = true;
            }
        }
        else
        {
            tchar* p;

            int i = ListString[Position].GetSubmaskAsIndex();

            if(i >= 0)
            {
                p = const_cast<tchar*>(ListString[i].Submask.GetData());
            }
            else
            {
                p = const_cast<tchar*>(ListString[Position].Submask.GetData());
            }

            if(p != 0)
            {
                ArrangeBits(++p);
                valid = Bits.IsON(_c);
                Bits.DisableAllItems();
            }
        }

        if(valid)
        {
            if(Position > -1 && Position < static_cast<int>(ListString.GetCount()))
            {
                if((Flags & DisplayAsPassword) != 0)
                {
                    FormatString.SetAt(Position, PlaceholderPassword);
                }
                else
                {
                    FormatString.SetAt(Position, _c);
                }
                MirrorString.SetAt(Position, _c);
            }
            else
            {
                if(Flags & DisplayAsPassword)
                {
                    FormatString += PlaceholderPassword;
                }
                else
                {
                    FormatString += _c;
                }
                MirrorString += _c;
            }
        }

        if(valid && (Flags & AutoFeed) != 0)
        {
            GetNextPosition();
        }
    }
    return valid;
}

tchar* Validator::ArrangeBits(tchar* _p, int _level) 
{
#ifdef _UNICODE
    const ushort _default_bits_size = 8192; // in bytes
#else
    const ushort _default_bits_size = 32;   // in bytes
#endif

    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    ushort c;
    tchar* p = _p ? _p : const_cast<tchar*>(Mask.GetData());

    if(p == null)
    {
        return null;
    }

    while(*p != 0 && *p != Char::BracketRight)
    {
        switch(*p)
        {
            case _t('['): // Char::BracketLeft
                p = ArrangeBits(++p, _level+1);
                break;
            case _t(']'): // Char::BracketRight:
                return ++p;
            case _t('{'): // Char::BraceLeft:
                while(*p != 0 && *p++ != Char::BraceRight)
                {
                }
                break;
            case _t('@'): // Char::At
            case _t('|'): // Char::Bar
                ++p;
                break;
            case _t('$'): // Char::Dollar
                if(*(++p) != 0)
                {
                    while(*p != 0 && iswdigit(*(++p)))
                    {
                    }
                }
                else
                {
                    throw Validator::XValidator(XValidator::InvalidSyntax);
                }
                break;
            case _t('!'): // Char::Exclam
                if(*(++p) != 0)
                {
                    Bits.DisableItem(*p++);
                }
                else
                {
                    throw Validator::XValidator(XValidator::InvalidSyntax);
                }
                break; 
            case _t('&'): // Char::Ampersand
                if(*(++p) != 0)
                {
                    switch(*p)
                    {
                        case 'A':
                        case 'a':
                        case 'L':
                        case 'l':
                        case '0':
                        case '9':
                        case _t('#'): // Char::NumberSign
                        case 'E':
                        case _t('.'): // Char::Period
                            for(c = 0; c < _default_bits_size*8; c++)
                            {
                                if(*p == 'A')
                                {
                                    if(iswupper(c) && (iswalnum(c) || iswspace(c)))
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == 'a')
                                {
                                    if(iswlower(c) && (iswalnum(c) || iswspace(c)))
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == 'L')
                                {
                                    if(iswupper(c))
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == 'l')
                                {
                                    if(iswlower(c))
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == '0')
                                {
                                    if(iswdigit(c))
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == '9')
                                {
                                    if(iswdigit(c) || iswspace(c))
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == Char::NumberSign)
                                {
                                    if(iswdigit(c) || iswspace(c) || c == Char::Plus || c == Char::Minus)
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == 'E')
                                {
                                    if(iswdigit(c) || iswspace(c) || c == Char::Plus || c == Char::Minus || c == Char::Period || c == 'E' || c == 'e')
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                                else if(*p == Char::Period)
                                {
                                    if(iswpunct(c))
                                    {
                                        Bits.EnableItem(c);
                                    }
                                }
                            }
                            break;
                        case _t('*'): // Char::Asterisk
                            Bits.EnableAllItems();
                            break;
                        default:
                            throw Validator::XValidator(XValidator::InvalidSyntax);
                    }

                    ++p;
                }
                else
                {
                    throw Validator::XValidator(XValidator::InvalidSyntax);
                }
                break;  
            case _t('\\'): // Char::BackSlash:
                if(*(++p) != 0)
                {
                    Bits.EnableItem(*p++);
                }
                break;
            default:
                if(*p == Char::Minus && p > _p && *(p-1) != Char::Bar && *(p-1) != Char::BackSlash && *(p-1) != Char::BracketLeft && *(p+1))
                {
                    ++p;

                    for(c = *(p-2); c < *p; c++)
                    {
                        Bits.EnableItem(c);
                    }
                }

                Bits.EnableItem(*p++);
                break;
        }
    }
    return ++p;
}

bool Validator::CorrectPosition(int _start)
{
    if(Position < 0)                  
    {
        return false;
    }

    int pos = Position;
    int i   = _start ? _start : 0;

    for(; i < static_cast<int>(ListString.GetCount()); i++)
    {
        if(ListString[i].Flags & ValidatorEntry::Letter)
        {   
            Position = i;
            return Position != pos;
        }
    }

    GetLastPosition();
    return Position != pos;
}

bool Validator::GetFirstPosition()
{
    if(Position < 0)
    {
        return false;
    }

    int pos = Position;

    for(int i = 0; i < static_cast<int>(ListString.GetCount()); i++)
    {
        if(ListString[i].Flags & ValidatorEntry::Letter)
        {
            Position = i;
            break;
        }
    }
    return Position != pos;
}

bool Validator::GetLastPosition()
{
    if(Position < 0)
    {
        return false;
    }

    int pos = Position;

    for(int i = static_cast<int>(ListString.GetCount()-1); i >= 0; i--)
    {
        if(ListString[i].Flags & ValidatorEntry::Letter)
        {
            Position = ++i;
            return Position != pos;
        }
    }

    Position = i;
    return Position != pos;
}

bool Validator::GetNextPosition()
{
    if(Position < 0) 
    {
        return false;
    }

    int pos = Position;

    for(int i = Position+1; i < static_cast<int>(ListString.GetCount()); i++)
    {
        if(ListString[i].Flags & ValidatorEntry::Letter)
        {
            Position = i;
            return Position != pos;
        }
    }

    GetLastPosition();
    return Position != pos;
}

bool Validator::GetPrevPosition()
{
    if(Position < 0)
    {
        return false;
    }

    int pos = Position;

    for(int i = Position-1; i >= 0; i--)
    {
        if(ListString[i].Flags & ValidatorEntry::Letter)
        {
            Position = i;
            break;
        }
    }

    return Position != pos;
}

void Validator::FindFirstVacantPlace()
{
    for(int i = 0; i < static_cast<int>(ListString.GetCount()); i++)
    {
        if(ListString[i].Flags & ValidatorEntry::Letter)
        {   
            if((ListString[i].Flags & ValidatorEntry::Substring) != 0 && (Flags & AutoHint) != 0)
            {
                continue;
            }

            Position = i;
            break;
        }
    }
}

tchar* Validator::SkipGroup(tchar* _p, int _level)
{
    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    tchar* p = _p;

    while(*p != 0)
    {
        switch(*p)
        {
            case _t('['): // Char::BracketLeft:
                p = SkipGroup(++p, _level+1);
                break;
            case _t(']'): // Char::BracketRight:
                return ++p;
            default:
                ++p;
                break;
        }
    }
    return p;
}

tchar* Validator::SkipMask(tchar* _p, int _level)
{
    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    tchar* p = _p;

    if(p == null)
    {
        return null;
    }

    while(*p != 0)
    {
        switch(*p)
        {
            case _t('{'): // Char::BraceLeft:
                p = SkipMask(++p, _level+1);
                break;
            case _t('}'): // Char::BraceRight:
                return ++p;
            default:
                ++p;
                break;
        }
    }
    return p;
}

void Validator::ResetMask(tchar* _newmask)
{
    if(!ListString.IsEmpty())
    {
        ListString.Destroy();
    }
    Init(_newmask);
}

bool Validator::Delete(int _startsel, int _endsel, bool _flag)
{
    if(_startsel <= _endsel && !FormatString.IsEmpty() && _startsel < static_cast<int>(FormatString.GetCount()))
    {
        if(_startsel < _endsel)
        {
            BuildFormatString(_startsel, _endsel, _startsel == _endsel);
            CorrectPosition(_startsel);
            return true;
        }
        else if(ListString[Position].Flags & ValidatorEntry::Letter)
        {
            BuildFormatString(_startsel, _endsel, _startsel == _endsel);

            if(!CorrectPosition(_startsel) && _flag != 0 && (Flags & AutoFeed) != 0)
            {
                GetNextPosition();
            }

            return true;
        }
        else
        {
            CorrectPosition(_startsel);
        }
    }

    return false;
}

bool Validator::IsSeparator()
{
    if(Position > -1 && Position < int(ListString.GetCount()))
    {
        uint f = ListString[Position].Flags;

        if(Position < static_cast<int>(ListString.GetCount()))
        {
            return (f & ValidatorEntry::Separator) == ValidatorEntry::Separator;
        }
    }
    return true;
}

bool Validator::IsValid()
{
    tchar* pmsk  = const_cast<tchar*>(Mask.GetData());
    tchar* pfrmt = const_cast<tchar*>(FormatString.GetData());

    TCharStr str;

    while(*pmsk != 0 && (pmsk = GetNextSubstring(pmsk, str)) != null)
    {
        pfrmt = StrSubstr(pfrmt, const_cast<tchar*>(str.GetData()));
        str.SetEmpty();

        if(pfrmt == 0)
        {
            return false;
        }
    }
    return true;
}

uint Validator::GetEntryFlags(int _pos)
{
    if(_pos < 0)
    {
        if(Position > -1 && Position < int(ListString.GetCount()))
        {
            return ListString[Position].Flags;
        }
    }
    else if(_pos > 0 && _pos < static_cast<int>(ListString.GetCount()))
    {
        return ListString[_pos].Flags;
    }
    return 0;
}

bool Validator::DefaultValue(TCharStr&)
{
    return false;
}

bool Validator::GetData()
{
    return false;
}

ushort Validator::GetFirstLeftDisableEntry()
{
    if(Position > -1 && Position < static_cast<int>(ListString.GetCount()))
    {
        ushort pos = Position;

        while(pos != 0 && (GetEntryFlags(pos) & ValidatorEntry::Disable) != 0)
        {
            --pos;
        }

        return pos;
    }
    return -1;
}

ushort Validator::GetLastRightDisableEntry()
{
    if(Position > -1 && Position < static_cast<int>(ListString.GetCount()))
    {
        ushort pos = Position;

        while(pos < ushort(ListString.GetCount()) && (GetEntryFlags(pos) & ValidatorEntry::Disable) != 0)
        {
            pos++;
        }

        return pos;
    }
    return -1;
}

Validator::XValidator::XValidator(uint _error) : X(_error)
{
}
////////////////////////////////////////////////////////////////////////////////////////
// class BaseTimeValidator
// ----- -----------------
// July '7' October '10'
const tchar Submask_M[]    = _t("[1][&0]");
// July '07' October '10'
const tchar Submask_MM[]   = _t("[0|1][&0]");
// July 'Jul' 
const tchar Submask_MMM[]  = _t("[J|F|M|A|S|O|N|D][a|e|p|u|c|o][n|b|r|y|l|g|p|t|v]");
// July 'July' 
const tchar Submask_MMMM[] = _t("[J|F|M|A|S|O|N|D][&l][&l][&l][&l][&l][&l][&l][&l]");

// Day of a month '6' '12'
const tchar Submask_d[]    = _t("[1|2|3][&0]");
// Day of a month '06' '12'
const tchar Submask_dd[]   = _t("[0|1|2|3][&0]");
// Day of a month 'Mon'
const tchar Submask_ddd[]  = _t("[M|T|W|F|S][o|u|e|h|r|a][n|e|d|u|i|t]");
// Day of a month 'Monday'
const tchar Submask_dddd[] = _t("[M|T|W|F|S][&l][&l][&l][&l][&l][&l][&l][&l]");

// Year '09' '97'
const tchar Submask_yy[]   = _t("[&0][&0]");
// Year '2009' '1997'
const tchar Submask_yyyy[] = _t("[&0][&0][&0][&0]");

// Hour 0-12 '9' '12'
const tchar Submask_h[]    = _t("[0|1|2][&0]");
// Hour 0-12 '09' '12'
const tchar Submask_hh[]   = _t("[0|1|2][&0]");
// Hour 0-23 '9' '12'
const tchar Submask_H[]    = _t("[0|1|2][&0]");
// Hour 0-23 '09' '12'
const tchar Submask_HH[]   = _t("[0|1|2][&0]");

// Minute '2' '15'
const tchar Submask_m[]    = _t("[&0|!9!8!7!6][&0]");
// Minute '02' '15'
const tchar Submask_mm[]   = _t("[&0|!9!8!7!6][&0]");

// Second '08' '35'
const tchar Submask_ss[]   = _t("[&0|!9!8!7!6][&0]");

// AM PM
const tchar Submask_AMPM[] = _t("[A|P]M");
// am pm
const tchar Submask_ampm[] = _t("[a|p]m");
// A P
const tchar Submask_AP[]   = _t("[A|P]");
// a p
const tchar Submask_ap[]   = _t("[a|p]");

BaseTimeValidator::BaseTimeValidator(tchar* mask, tchar plstr, tchar plgrp, tchar plmsk, tchar plpswd, uint f, bool init)
                 : Validator(null, plstr, plgrp, plmsk, plpswd, f, init)
{
    OriginalMask = mask;

    Init(mask);
}

BaseTimeValidator::~BaseTimeValidator()
{
}

void BaseTimeValidator::BuildMask(tchar* ptr)
{
    Mask.SetEmpty();

    tchar* p = ptr ? ptr : const_cast<tchar*>(Mask.GetData());

    if(!p)
    {
        return;
    }

    while(*p)
    {
        switch(*p)
        {
            case _t('{'): // Char::BraceLeft:
                Mask += Char::BraceLeft;
                p = BuildSubmask(++p);
                break;
            case _t('\\'): // Char::BackSlash:
                Mask += *p;
                if(*(++p))
                {
                    Mask += *p++;
                }
                break;
            default:
                Mask += *p++;
                break;
        }
    }
}

tchar* BaseTimeValidator::BuildSubmask(tchar* ptr, int _level)
{
    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    tchar*   p = ptr;
    int      i;

    if(!p)
    {
        return null;
    }

    TCharStr str;

    while(*p)
    {
        switch(*p)
        {
            case _t('&'): // Char::Ampersand:
                if(*(++p))
                {
                    switch(*p)
                    {
                        case 'M':
                            i = 0;   
                            while(*p && *p == 'M')
                            {
                                i++, p++;
                            }
                            if(i == 1)                                           
                            {
                                Mask += Submask_M;                                  
                            }
                            else if(i == 2)                                      
                            {
                                Mask += Submask_MM;                                 
                            }
                            else if(i == 3)                                      
                            {
                                Mask += Submask_MMM;                                
                            }
                            else if(i == 4)                                      
                            {
                                Mask += Submask_MMMM;                               
                            }
                            else                                                 
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;                                               
                        case 'D':
                        case 'd':                                             
                            i = 0;                                               
                            while(*p && (*p == 'D' || *p == 'd'))                
                            {
                                i++, p++;                                           
                            }
                            if(i == 1)                                           
                            {
                                Mask += Submask_d;                                  
                            }
                            else if(i == 2)                                      
                            {
                                Mask += Submask_dd;                                 
                            }
                            else if(i == 3)                                      
                            {
                                Mask += Submask_ddd;                                
                            }
                            else if(i == 4)                                      
                            {
                                Mask += Submask_dddd;                               
                            }
                            else                                                 
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;                                               
                        case 'Y':                                             
                        case 'y':                                             
                            i = 0;                                               
                            while(*p && (*p == 'Y' || *p == 'y'))                
                            {
                                i++, p++;                                           
                            }
                            if(i == 1)                                           
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            else if(i == 2)                                      
                            {
                                Mask += Submask_yy;                                 
                            }
                            else if(i == 3)                                      
                            { 
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            else if(i == 4)                                      
                            {
                                Mask += Submask_yyyy;                               
                            }
                            else
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;                                               
                        case 'H':                                             
                            i = 0;                                               
                            while(*p && *p == 'H')                               
                            {
                                i++, p++;                                           
                            }
                            if(i == 1)                                           
                            {
                                Mask += Submask_H;                                  
                            }
                            else if(i == 2)                                      
                            {
                                Mask += Submask_HH;                                 
                            }
                            else                                                 
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;
                        case 'h':                                             
                            i = 0;                                               
                            while(*p && *p == 'h')                               
                            {
                                i++, p++;                                           
                            }
                            if(i == 1)                                           
                            {
                                Mask += Submask_h;                                  
                            }
                            else if(i == 2)                                      
                            {
                                Mask += Submask_hh;                                 
                            }
                            else                                                 
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;                                               
                        case 'm':                                             
                            i = 0;                                               
                            while(*p && *p == 'm')                               
                            {
                                i++, p++;                                           
                            }
                            if(i == 1)
                            {
                                Mask += Submask_m;                                  
                            }
                            else if(i == 2)                                      
                            {
                                Mask += Submask_mm;                                 
                            }
                            else                                                 
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;                                               
                        case 's':                                             
                            i = 0;                                               
                            while(*p && *p == 's')                               
                            {
                                i++, p++;                                           
                            }
                            if(i == 1)                                           
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            else if(i == 2)                                      
                            {
                                Mask += Submask_ss;                                 
                            }
                            else                                                 
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;                                               
                        case 'A':                                             
                            Mask += Submask_AMPM;                                
                            p++;                                                 
                            break;                                               
                        case 'a':                                             
                            Mask += Submask_ampm;                                
                            p++;                                                 
                            break;                                               
                        case 'P':                                             
                            Mask += Submask_AP;                                  
                            p++;                                                 
                            break;
                        case 'p':
                            Mask += Submask_ap;
                            p++;
                            break;
                        default:
                            throw Validator::XValidator(XValidator::InvalidSyntax);
                    }
                }
                break;
            case _t('['): // Char::BracketLeft:
                GetSubmask(str, p); 
                Mask += str;
                p = SkipGroup(++p);
                break;
            case _t('{'): // Char::BraceLeft:
                Mask += Char::BraceLeft;
                p = BuildSubmask(++p, _level+1);
                break;
            case _t('}'): // Char::BraceRight:
                Mask += Char::BraceRight;
                return ++p;
            case _t('\\'): // Char::BackSlash:
                Mask += *p;
                if(*(++p))
                {
                    Mask += *p++;
                }
                break;
            default:
                Mask += *p++;
                break;
        }
    }
    return p;
}

bool BaseTimeValidator::IsValid()
{
    if(TimeValueMin != TimeValueMax)
    {
        if(TimeValue < TimeValueMin || TimeValue > TimeValueMax)
        {
            return false;
        }
    }
    return true;
}

bool BaseTimeValidator::DefaultValue(TCharStr& str)
{
    tchar* p = const_cast<tchar*>(OriginalMask.GetData());
    int    n, i;

    if(!p)
    {
        return false;
    }

    while(*p)
    {
        switch(*p)
        {
            case _t('{'): // Char::BraceLeft:
                p = BuildDefaultValue(++p, str);
                break;
            case _t('['): // Char::BracketLeft:
                n = 0;
                p = GetRepeatSymbolsFromGroup(++p, n);
                if(!n)
                {
                    n++;
                }
                for(i = 0; i < n; i++)
                {
                    if(Flags & Validator::DisplayAsPassword)
                    {
                        str += PlaceholderPassword;
                    }
                    else
                    {
                        str += PlaceholderGroup;
                    }
                }
                break;
            case _t('\\'): // Char::BackSlash:
                if(*(++p))
                {
                    str += *p++;
                }
                break;
            default:
                str += *p++;
                break;
        }
    }
    return true;
}

tchar* BaseTimeValidator::BuildDefaultValue(tchar* ptr, TCharStr& str, int _level)
{
    _xassert(Validator::XValidator, _level < ConstDeepLevel, null, XValidator::InvalidSyntax);
    //
    tchar  buffer[2];
    tchar* p = ptr;
    int    i, h;

    if(!p)
    {
        return null;
    }

    while(*p)
    {
        switch(*p)
        {
            case _t('&'): // Char::Ampersand:
                if(*(++p))
                {
                    switch(*p)
                    {
                        case 'M':
                            i = 0;
                            while(*p && *p == 'M')
                            {
                                i++, p++;
                            }
                            if(i == 1)
                            {
                                compose(buffer, _t("%u"), TimeValue.GetMonth());

                                if(TimeValue.GetMonth() < 10)
                                {
                                    if(Flags & DisplayAsPassword)
                                    {
                                        str += PlaceholderPassword;
                                    }
                                    else
                                    {
                                        str += PlaceholderMask;
                                    }
                                }

                                str += buffer;
                            }
                            else if(i == 2)
                            {
                                compose(buffer, _t("%u"), TimeValue.GetMonth());

                                if(TimeValue.GetMonth() < 10)
                                {
                                    str += '0';
                                }

                                str += buffer;
                            }
                            else if(i == 3)
                            {
                                str += Time::GetMonthsAbbr()[TimeValue.GetMonth()-1];
                            }
                            else if(i == 4)
                            {
                                int n = 9-StrLen(Time::GetMonths()[TimeValue.GetMonth()-1]);

                                str += Time::GetMonths()[TimeValue.GetMonth()-1];

                                for(int i = 0; i < n; i++)
                                {
                                    if(Flags & DisplayAsPassword)
                                    {
                                        str += PlaceholderPassword;
                                    }
                                    else
                                    {
                                        str += PlaceholderMask;
                                    }
                                }
                            }
                            else
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;
                        case 'D':
                        case 'd':
                            i = 0;
                            while(*p && (*p == 'D' || *p == 'd'))
                            {
                                i++, p++;
                            }

                            if(i == 1)
                            {
                                compose(buffer, _t("%u"), TimeValue.GetDay());

                                if(TimeValue.GetDay() < 10)
                                {
                                    if(Flags & DisplayAsPassword)
                                    {
                                        str += PlaceholderPassword;
                                    }
                                    else
                                    {
                                        str += PlaceholderMask;
                                    }
                                }
                                str += buffer;
                            }
                            else if(i == 2)
                            {
                                compose(buffer, _t("%u"), TimeValue.GetDay());
                                
                                if(TimeValue.GetDay() < 10)
                                {
                                    str += '0';
                                }
                                str += buffer;
                            }
                            else if(i == 3)
                            {
                                str += Time::GetWeekDaysAbbr()[TimeValue.GetDayOfWeek()-1];
                            }
                            else if(i == 4)
                            {
                                int n = 9-StrLen(Time::GetWeekDays()[TimeValue.GetDayOfWeek()-1]);

                                str += Time::GetWeekDays()[TimeValue.GetDayOfWeek()-1];

                                for(int i = 0; i < n; i++)
                                {
                                    if(Flags & DisplayAsPassword)
                                    {
                                        str += PlaceholderPassword;
                                    }
                                    else
                                    {
                                        str += PlaceholderMask;
                                    }
                                }
                            }
                            else
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;
                        case 'Y':
                        case 'y':
                            i = 0;

                            while(*p && (*p == 'Y' || *p == 'y'))
                            {
                                i++, p++;
                            }

                            if(i == 1)
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            else if(i == 2)
                            {
                                compose(buffer, _t("%u"), TimeValue.GetYear());

                                str += buffer[2];
                                str += buffer[3];
                            }
                            else if(i == 3)
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            else if(i == 4)
                            {
                                compose(buffer, _t("%u"), TimeValue.GetYear());
                                str += buffer;
                            }
                            else
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;
                        case 'H':
                            i = 0;
                            while(*p && *p == 'H')
                            {
                                i++, p++;
                            }

                            if(i > 2)
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }

                            h = TimeValue.GetHours(); 

                            if(h < 10)
                            {
                                if(i == 1)
                                {
                                    if(Flags & DisplayAsPassword)
                                    {
                                        str += PlaceholderPassword;
                                    }
                                    else
                                    {
                                        str += PlaceholderMask;
                                    }
                                }
                                else if(i == 2)
                                {
                                    str += '0';
                                }
                            }

                            compose(buffer, _t("%u"), h);

                            str += buffer;
                            break;
                        case 'h':
                            i = 0;
                            while(*p && *p == 'h')
                            {
                                i++, p++;
                            }
                            if(i > 2)
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }

                            h = TimeValue.GetHours();

                            if(h > 12)
                            {
                                h %= 12;
                            }

                            if(h < 10)
                            {
                                if(i == 1)
                                {
                                    if(Flags & DisplayAsPassword)
                                    {
                                        str += PlaceholderPassword;
                                    }
                                    else
                                    {
                                        str += PlaceholderMask;
                                    }
                                }
                                else if(i == 2)
                                {
                                    str += '0';
                                }
                            }

                            compose(buffer, _t("%u"), h);

                            str += buffer;
                            break;
                        case 'm':
                            i = 0;

                            while(*p && *p == 'm')
                            {
                                i++, p++;
                            }

                            if(i > 2)
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }

                            if(TimeValue.GetMinutes() < 10)
                            {
                                if(i == 1)
                                {
                                    if(Flags & DisplayAsPassword)
                                    {
                                        str += PlaceholderPassword;
                                    }
                                    else
                                    {
                                        str += PlaceholderMask;
                                    }
                                }
                                else if(i == 2)
                                {
                                    str += '0';
                                }
                            }

                            compose(buffer, _t("%u"), TimeValue.GetMinutes());

                            str += buffer;
                            break;
                        case 's':
                            i = 0;

                            while(*p && *p == 's')
                            {
                                i++, p++;
                            }

                            if(i == 1)
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            else if(i == 2)
                            {
                                if(TimeValue.GetSeconds() < 10) 
                                {
                                    str += '0';
                                }

                                compose(buffer, _t("%u"), TimeValue.GetSeconds());

                                str += buffer;
                            }
                            else
                            {
                                throw Validator::XValidator(XValidator::InvalidSyntax);
                            }
                            break;
                        case 'A':
                        case 'P':
                            if(TimeValue.GetHours() <= 12)
                            {
                                compose(buffer, _t("A"));
                            }
                            else
                            {
                                compose(buffer, _t("P"));
                            }

                            str += buffer;
                            p++;
                            break;
                        case 'a':
                        case 'p':
                            if(TimeValue.GetHours() <= 12)
                            {
                                compose(buffer, _t("a"));
                            }
                            else
                            {
                                compose(buffer, _t("p"));
                            }

                            str += buffer;
                            p++;
                            break;
                        default:
                            throw Validator::XValidator(XValidator::InvalidSyntax);
                    }
                }
                break;     
            case _t('{'): // Char::BraceLeft:
                p = BuildDefaultValue(++p, str, _level+1);
                break;
            case _t('}'): // Char::BraceRight:
                return ++p;
            case _t('['): // Char::BracketLeft:
                if(Flags & Validator::DisplayAsPassword)
                {
                    str += PlaceholderPassword;
                }
                else
                {
                    str += PlaceholderMask;
                }

                p = SkipGroup(++p);
                break;
            case _t('\\'): // Char::BackSlash:
                if(*(++p))
                {
                    p++;
                }
                break;
            default:
                p++;
                break;
        }
    }
    return p;
}
////////////////////////////////////////////////////////////////////////////////////////
// class TimeValidator
// ----- -------------
const tchar Submask_MMddyy[]            = _t("{&MM/&dd/&yy}");
const tchar Submask_MMddyyyy[]          = _t("{&MM/&dd/&yyyy}");
const tchar Submask_ddddMMMMddyyyy[]    = _t("{&dddd, &MMMM &dd, &yyyy}");
const tchar Submask_ddMMMMyyyy[]        = _t("{&dd &MMMM &yyyy}");
const tchar Submask_MMMddyyyy[]         = _t("{&MMM &dd, &yyyy}");
const tchar Submask_MMMMddyyyy[]        = _t("{&MMMM &dd, &yyyy}");
const tchar Submask_ddMMMyy[]           = _t("{&d-&MMM-&yy}");
const tchar Submask_MMMMyy[]            = _t("{&MMMM, &yy}");
const tchar Submask_MMMyy[]             = _t("{&MMM-&yy}");
const tchar Submask_MMddyyhhmmAM[]      = _t("{&MM/&dd/&yy &hh:&mm &A}");
const tchar Submask_MMddyyhhmmssAM[]    = _t("{&MM/&dd/&yy &hh:&mm:&ss &A}");
const tchar Submask_hhmmAM[]            = _t("{&hh:&mm &A}");
const tchar Submask_hhmmssAM[]          = _t("{&hh:&mm:&ss &A}");
const tchar Submask_HHmm[]              = _t("{&HH:&mm}");
const tchar Submask_HHmmss[]            = _t("{&HH:&mm:&ss}");

TimeValidator::TimeValidator(uint style)
{
    tchar* p;

    Style = style;

    switch(style)
    {
        case TimeValidator::MMddyy:
            p = const_cast<tchar*>(Submask_MMddyy);
            break;
        case MMddyyyy:
            p = const_cast<tchar*>(Submask_MMddyyyy);
            break;
        case TimeValidator::ddddMMMMddyyyy:
            p = const_cast<tchar*>(Submask_ddddMMMMddyyyy);
            break;
        case TimeValidator::ddMMMMyyyy:
            p = const_cast<tchar*>(Submask_ddMMMMyyyy);
            break;
        case TimeValidator::MMMMddyyyy:
            p = const_cast<tchar*>(Submask_MMMMddyyyy);
            break;
        case TimeValidator::MMMddyyyy:
            p = const_cast<tchar*>(Submask_MMMddyyyy);
            break;
        case TimeValidator::ddMMMyy:
            p = const_cast<tchar*>(Submask_ddMMMyy);
            break;
        case TimeValidator::MMMMyy:
            p = const_cast<tchar*>(Submask_MMMMyy);
            break;
        case TimeValidator::MMMyy:
            p = const_cast<tchar*>(Submask_MMMyy);
            break;
        case TimeValidator::MMddyyhhmmAM:
            p = const_cast<tchar*>(Submask_MMddyyhhmmAM);
            break;
        case TimeValidator::MMddyyhhmmssAM:
            p = const_cast<tchar*>(Submask_MMddyyhhmmssAM);
            break;
        case TimeValidator::hhmmAM:
            p = const_cast<tchar*>(Submask_hhmmAM);
            break;
        case TimeValidator::hhmmssAM:
            p = const_cast<tchar*>(Submask_hhmmssAM);
            break;
        case TimeValidator::HHmm:
            p = const_cast<tchar*>(Submask_HHmm);
            break;
        case TimeValidator::HHmmss:
            p = const_cast<tchar*>(Submask_HHmmss);
            break;
        default:
            p = null;
    }

    SetOriginalMask(p);
    Init(p);
}

TimeValidator::~TimeValidator()
{
    IsValid();
}

bool TimeValidator::TimeFrom_MMddyy(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[1])) && iswdigit(buffer[0]))
    {
        buffer[1] = buffer[0];
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    m = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[1])) && iswdigit(buffer[0]))
    {
        buffer[1] = buffer[0];
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+6);
    buffer[1] = *(p+7);

    if(!(iswdigit(buffer[1])) && iswdigit(buffer[0]))
    {
        buffer[1] = buffer[0];
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    y  = StrToInteger(buffer, &p2, 10);
    y += y < 70 ? 2000 : 1900;

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_MMddyyyy(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[1])) && iswdigit(buffer[0]))
    {
        buffer[1] = buffer[0];
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    m = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[1])) && iswdigit(buffer[0]))
    {
        buffer[1] = buffer[0];
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+6);
    buffer[1] = *(p+7);
    buffer[2] = *(p+8);
    buffer[3] = *(p+9);

    for(short i = 0; i < 4; i++)
    {
        if(!(iswdigit(buffer[i])))
        {
            buffer[i] = '0';
        }
    }

    y = StrToInteger(buffer, &p2, 10);

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_ddddMMMMddyyyy(tchar* string, const tchar* format)
{
    tchar  buffer[16];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d, dw;

    y = m = d = dw = 0;

    for(int i = 0; i < 9; i++)
    {
        if(iswalpha(*(p+i)))
        {
            buffer[i] = *(p+i);
        }
        else if(*(p+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;
    for(i = 0; i < 7; i++)
    {
        if(!StrCompare(buffer, Time::GetWeekDays()[i]))
        {
            dw = i+1;
            break;
        }
    }

    for(i = 0; i < 9; i++)
    {
        if(iswalpha(*(p+11+i)))
        {
            buffer[i] = *(p+11+i);
        }
        else if(*(p+11+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+11+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;
    for(i = 0; i < 12; i++)
    {
        if(!StrCompare(buffer, Time::GetMonths()[i]))
        {
            m = i+1;
            break;
        }
    }

    buffer[0] = *(p+21);
    buffer[1] = *(p+22);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+25);
    buffer[1] = *(p+26);
    buffer[2] = *(p+27);
    buffer[3] = *(p+28);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    if(!(iswdigit(buffer[2])))
    {
        buffer[2] = '0';
    }

    if(!(iswdigit(buffer[3])))
    {
        buffer[3] = '0';
    }

    y = StrToInteger(buffer, &p2, 10);

    if(GetTime().IsDateValid(y, m, d) && (dw == Time::GetDayOfWeek(y, m, d)))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_ddMMMMyyyy(tchar* string, const tchar* format)
{
    tchar  buffer[16];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    y = m = d = 0;

    for(int i = 0; i < 9; i++)
    {
        if(iswalpha(*(p+3+i)))
        {
            buffer[i] = *(p+3+i);
        }
        else if(*(p+3+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+3+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;
    for(i = 0; i < 12; i++)
    {
        if(!StrCompare(buffer, Time::GetMonths()[i]))
        {
            m = i+1;
            break;
        }
    }
    
    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+13);
    buffer[1] = *(p+14);
    buffer[2] = *(p+15);
    buffer[3] = *(p+16);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    if(!(iswdigit(buffer[2])))
    {
        buffer[2] = '0';
    }

    if(!(iswdigit(buffer[3])))
    {
        buffer[3] = '0';
    }

    y = StrToInteger(buffer, &p2, 10);
    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_MMMddyyyy(tchar* string, const tchar* format)
{
    tchar  buffer[16];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    y = m = d = 0;

    // get month
    for(int i = 0; i < 3; i++)
    {
        if(iswalpha(*(p+0+i)))
        {
            buffer[i] = *(p+0+i);
        }
        else if(*(p+0+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+0+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;

    for(i = 0; i < 12; i++)
    {
        if(!StrCompare(buffer, Time::GetMonthsAbbr()[i]))
        {
            m = i+1;
            break;
        }
    }

    // get day
    buffer[0] = *(p+4);
    buffer[1] = *(p+5);
    buffer[2] = 0;

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }
    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);

    // get year
    buffer[0] = *(p+8);
    buffer[1] = *(p+9);
    buffer[2] = *(p+10);
    buffer[3] = *(p+11);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    if(!(iswdigit(buffer[2])))
    {
        buffer[2] = '0';
    }

    if(!(iswdigit(buffer[3])))
    {
        buffer[3] = '0';
    }

    buffer[4] = 0;

    y = StrToInteger(buffer, &p2, 10);

    // validate
    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_MMMMddyyyy(tchar* string, const tchar* format)
{
    tchar  buffer[16];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    y = m = d = 0;

    for(int i = 0; i < 9; i++)
    {
        if(iswalpha(*(p+0+i)))
        {
            buffer[i] = *(p+0+i);
        }
        else if(*(p+0+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+0+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;
    for(i = 0; i < 12; i++)
    {
        if(!StrCompare(buffer, Time::GetMonths()[i]))
        {
            m = i+1;
            break;
        }
    }

    buffer[0] = *(p+10);
    buffer[1] = *(p+11);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }
    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+14);
    buffer[1] = *(p+15);
    buffer[2] = *(p+16);
    buffer[3] = *(p+17);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }
    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    if(!(iswdigit(buffer[2])))
    {
        buffer[2] = '0';
    }

    if(!(iswdigit(buffer[3])))
    {
        buffer[3] = '0';
    }

    y = StrToInteger(buffer, &p2, 10);

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_ddMMMyy(tchar* string, const tchar* format)
{
    tchar  buffer[16];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    y = m = d = 0;

    for(int i = 0; i < 3; i++)
    {
        if(iswalpha(*(p+3+i)))
        {
            buffer[i] = *(p+3+i);
        }
        else if(*(p+3+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+3+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;
    for(i = 0; i < 12; i++)
    {
        if(!StrCompare(buffer, Time::GetMonthsAbbr()[i]))
        {
            m = i+1;
            break;
        }
    }

    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+7);
    buffer[1] = *(p+8);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    y  = StrToInteger(buffer, &p2, 10);
    y += y < 70 ? 2000 : 1900;

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_MMMMyy(tchar* string, const tchar* format)
{
    tchar  buffer[16];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    y = m = d = 0;

    for(int i = 0; i < 9; i++)
    {
        if(iswalpha(*(p+0+i)))
        {
            buffer[i] = *(p+0+i);
        }
        else if(*(p+0+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+0+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;
    for(i = 0; i < 12; i++)
    {
        if(!StrCompare(buffer, Time::GetMonths()[i]))
        {
            m = i+1;
            break;
        }
    }

    d = 1;
    buffer[0] = *(p+11);
    buffer[1] = *(p+12);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    y = StrToInteger(buffer, &p2, 10);
    y += y < 70 ? 2000 : 1900;

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_MMMyy(tchar* string, const tchar* format)
{
    tchar  buffer[16];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;

    y = m = d = 0;

    for(int i = 0; i < 3; i++)
    {
        if(iswalpha(*(p+0+i)))
        {
            buffer[i] = *(p+0+i);
        }
        else if(*(p+11+i) == PlaceholderMask)
        {
            for(int j = i+1; j < 9; j++)
            {
                if(*(p+11+j) != PlaceholderMask)
                {
                    return false;
                }
            }
            break;
        }
    }

    buffer[i] = 0;
    for(i = 0; i < 12; i++)
    {
        if(!StrCompare(buffer, Time::GetMonthsAbbr()[i]))
        {
            m = i+1;
            break;
        }
    }

    d = 1;
    buffer[0] = *(p+4);
    buffer[1] = *(p+5);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    y = StrToInteger(buffer, &p2, 10);
    y += y < 70 ? 2000 : 1900;

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y);
#else
            sprintf(string, format, m, d, y);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_MMddyyhhmmAM(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;
    ushort hour, min, sec;

    y = m = d = 0;

    hour = min = sec = 0;
    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    m = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+6);
    buffer[1] = *(p+7);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }
    
    y = StrToInteger(buffer, &p2, 10);
    y += y < 70 ? 2000 : 1900;
    buffer[0] = *(p+9);
    buffer[1] = *(p+10);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    hour = ushort(StrToInteger(buffer, &p2, 10));

    if(*(p+15) == 'P')
    {
        hour += 12;
    }

    hour %= 24;
    buffer[0] = *(p+12);
    buffer[1] = *(p+13);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    min = ushort(StrToInteger(buffer, &p2, 10));

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d, hour, min);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y, hour, min);
#else
            sprintf(string, format, m, d, y, hour, min);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_MMddyyhhmmssAM(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    int    y, m, d;
    ushort hour, min, sec;

    y = m = d = 0;

    hour = min = sec = 0;
    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    m = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    d = StrToInteger(buffer, &p2, 10);
    buffer[0] = *(p+6);
    buffer[1] = *(p+7);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    y = StrToInteger(buffer, &p2, 10);
    y += y < 70 ? 2000 : 1900;
    buffer[0] = *(p+9);
    buffer[1] = *(p+10);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    hour = ushort(StrToInteger(buffer, &p2, 10));

    if(*(p+15) == 'P')
    { 
        hour += 12;
    }

    hour %= 24;
    buffer[0] = *(p+12);
    buffer[1] = *(p+13);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    min = ushort(StrToInteger(buffer, &p2, 10));
    buffer[0] = *(p+15);
    buffer[1] = *(p+16);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    sec = ushort(StrToInteger(buffer, &p2, 10));

    if(GetTime().IsDateValid(y, m, d))
    {
        GetTime().SetupTime(y, m, d, hour, min, sec);

        if(string && format)
        {
#ifdef _UNICODE
            wsprintf(string, format, m, d, y, hour, min, sec);
#else
            sprintf(string, format, m, d, y, hour, min, sec);
#endif
        }
        return true;
    }
    return false;
}

bool TimeValidator::TimeFrom_hhmmAM(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    ushort hour, min;

    hour = min = 0;

    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    hour = ushort(StrToInteger(buffer, &p2, 10));

    if(*(p+15) == 'P')
    {
        hour += 12;
    }

    hour %= 24;

    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    min = ushort(StrToInteger(buffer, &p2, 10));

    GetTime().SetupRealTime(hour, min);

    if(string && format)
    {
#ifdef _UNICODE
        wsprintf(string, format, hour, min);
#else
        sprintf(string, format, hour, min);
#endif
    }
    return true;
}

bool TimeValidator::TimeFrom_hhmmssAM(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    ushort hour, min, sec;
    hour = min = sec = 0;

    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    hour = ushort(StrToInteger(buffer, &p2, 10));

    if(*(p+15) == 'P')
    {
        hour += 12;
    }

    hour %= 24;
    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }
    
    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    min = ushort(StrToInteger(buffer, &p2, 10));
    buffer[0] = *(p+6);
    buffer[1] = *(p+7);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    sec = ushort(StrToInteger(buffer, &p2, 10));

    GetTime().SetupRealTime(hour, min, sec);

    if(string && format)
    {
#ifdef _UNICODE
        wsprintf(string, format, hour, min, sec);
#else
        sprintf(string, format, hour, min, sec);
#endif
    }
    return true;
}

bool TimeValidator::TimeFrom_HHmm(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    ushort hour, min;

    hour = min = 0;
    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    hour = ushort(StrToInteger(buffer, &p2, 10));
    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    min = ushort(StrToInteger(buffer, &p2, 10));

    GetTime().SetupRealTime(hour, min);

    if(string && format)
    {
#ifdef _UNICODE
        wsprintf(string, format, hour, min);
#else
        sprintf(string, format, hour, min);
#endif
    }
    return true;
}

bool TimeValidator::TimeFrom_HHmmss(tchar* string, const tchar* format)
{
    tchar  buffer[8];
    tchar* p = const_cast<tchar*>(MirrorString.GetData());
    tchar* p2;
    ushort hour, min, sec;

    hour = min = sec = 0;
    buffer[0] = *(p+0);
    buffer[1] = *(p+1);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }
    
    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    hour = ushort(StrToInteger(buffer, &p2, 10));
    buffer[0] = *(p+3);
    buffer[1] = *(p+4);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    }

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    min = ushort(StrToInteger(buffer, &p2, 10));
    buffer[0] = *(p+6);
    buffer[1] = *(p+7);

    if(!(iswdigit(buffer[0])))
    {
        buffer[0] = '0';
    } 

    if(!(iswdigit(buffer[1])))
    {
        buffer[1] = '0';
    }

    sec = ushort(StrToInteger(buffer, &p2, 10));

    GetTime().SetupRealTime(hour, min, sec);

    if(string && format)
    {
#ifdef _UNICODE
        wsprintf(string, format, hour, min, sec);
#else
        sprintf(string, format, hour, min, sec);
#endif
    }
    return true;
}

bool TimeValidator::IsTimeValid(tchar* string, const tchar* format)
{
    bool valid = BaseTimeValidator::IsValid();

    if(!valid)
    {
        return false;
    }

    switch(Style)
    {
        case TimeValidator::MMddyy:
            valid = TimeFrom_MMddyy(string, format);
            break;
        case TimeValidator::MMddyyyy:
            valid = TimeFrom_MMddyyyy(string, format);
            break;
        case TimeValidator::ddddMMMMddyyyy:
            valid = TimeFrom_ddddMMMMddyyyy(string, format);
            break;
        case TimeValidator::ddMMMMyyyy:
            valid = TimeFrom_ddMMMMyyyy(string, format);
            break;
        case TimeValidator::MMMMddyyyy:
            valid = TimeFrom_MMMMddyyyy(string, format);
            break;
        case TimeValidator::MMMddyyyy:
            valid = TimeFrom_MMMddyyyy(string, format);
            break;
        case TimeValidator::ddMMMyy:
            valid = TimeFrom_ddMMMyy(string, format);
            break;
        case TimeValidator::MMMMyy:
            valid = TimeFrom_MMMMyy(string, format);
            break;
        case TimeValidator::MMMyy:
            valid = TimeFrom_MMMyy(string, format);
            break;
        case TimeValidator::MMddyyhhmmAM:
            valid = TimeFrom_MMddyyhhmmAM(string, format);
            break;
        case TimeValidator::MMddyyhhmmssAM:
            valid = TimeFrom_MMddyyhhmmssAM(string, format);
            break;
        case TimeValidator::hhmmAM:
            valid = TimeFrom_hhmmAM(string, format);
            break;
        case TimeValidator::hhmmssAM:
            valid = TimeFrom_hhmmssAM(string, format);
            break;
        case TimeValidator::HHmm:
            valid = TimeFrom_HHmm(string, format);
            break;
        case TimeValidator::HHmmss:
            valid = TimeFrom_HHmmss(string, format);
            break;
        default:
            return false;
    }

    if(string && !valid)
    {
        string[0] = 0;
    }
    return valid;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

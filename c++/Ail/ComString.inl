////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMSTRING_INL__
#define __COMSTRING_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComString
// ----- ---------
__INLINE__ const ComString& ComString::operator = (const ComString& other)
{
    if(this != &other)
    {
        if(Str != null)
        {
          ::SysFreeString(Str);
        }

        Str = other.Copy();
    }
    
    return *this;
}

__INLINE__ const ComString& ComString::operator = (const wchar* _str)
{
    if(Str != null)
    {
      ::SysFreeString(Str);
    }
    
    Str = ::SysAllocString(_str);

    return *this;
}

__INLINE__ ComString::operator BSTR() const
{
    return Str;
}

__INLINE__ bool ComString::operator ! () const
{
    return Str == null;
}

__INLINE__ BSTR* ComString::operator & ()
{
    return &Str;
}

__INLINE__ ComString& ComString::operator += (const ComString& other)
{
    AppendBSTR(other.Str);
    return *this;
}

__INLINE__ bool ComString::operator < (BSTR _str) const
{
    if(_str == null && Str == NULL)
    {
        return false;
    }

    if(_str != null && Str != null)
    {
        return wcscmp(Str, _str) < 0;
    }

    return Str == null;
}

__INLINE__ bool ComString::operator == (BSTR _str) const
{
    if(_str == null && Str == null)
    {
        return true;
    }

    if(_str != null && Str != null)
    {
        return wcscmp(Str, _str) == 0;
    }

    return false;
}

__INLINE__ bool ComString::operator < (const char* _str)
{
    if(_str == null && Str == null)
    {
        return false;
    }

    if(_str != null && Str != null)
    {
        AutoPtrArray<wchar> p = _A2W(_str);
        return wcscmp(Str, p) < 0;
    }

    return Str == null;
}

__INLINE__ bool ComString::operator == (const char* _str)
{
    if(_str == null && Str == null)
    {
        return true;
    }

    if(_str != null && Str != null)
    {
        AutoPtrArray<wchar> p = _A2W(_str);
        return wcscmp(Str, p) == 0;
    }

    return false;
}

__INLINE__ bool ComString::IsEmpty() const
{
    return Str == null;
}

__INLINE__ char* ComString::GetAsText()
{
    if(Str != null)
    {
        return _W2A(Str);
    }

    return null;
}

__INLINE__ BSTR ComString::GetStr() const
{
    return Str;
}

__INLINE__ uint ComString::GetCount() const
{
    return (Str == null) ? 0 : ::SysStringLen(Str);
}

__INLINE__ BSTR ComString::Copy() const
{
    return ::SysAllocStringLen(Str, ::SysStringLen(Str));
}

__INLINE__ HRESULT ComString::CopyTo(BSTR* _str)
{
    if(_str == null)
    {
        return E_POINTER;
    }

    *_str = ::SysAllocStringLen(Str, ::SysStringLen(Str));

    if(*_str == null)
    {
        return E_OUTOFMEMORY;
    }
    
    return S_OK;
}

__INLINE__ void ComString::Attach(BSTR _str)
{
    if(Str == null)
    {
        Str = _str;
    }
}

__INLINE__ BSTR ComString::Detach()
{
    BSTR str = Str;
         Str = null;

    return str;
}

__INLINE__ void ComString::Empty()
{
    if(Str != null)
    {
      ::SysFreeString(Str), Str = null;
    }
}

__INLINE__ HRESULT ComString::Append(const wchar* _str)
{
    return Append(_str, wcslen(_str));
}

__INLINE__ HRESULT ComString::Append(const wchar* _str, uint _count)
{
    int count = GetCount();

    BSTR str = ::SysAllocStringLen(NULL, count+_count);

    if(_str == NULL)
    {
        return E_OUTOFMEMORY;
    }

    memcpy(str, Str, count*sizeof(wchar));
    memcpy(str+count, _str, _count*sizeof(wchar));

    str[count+_count] = null;

    ::SysFreeString(Str);

    Str = str;

    return S_OK;
}

__INLINE__ HRESULT ComString::Append(const ComString& other)
{
    return Append(other.Str, ::SysStringLen(other.Str));
}

__INLINE__ HRESULT ComString::AppendBSTR(BSTR _str)
{
    return Append(_str, ::SysStringLen(_str));
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMSTRING_INL__

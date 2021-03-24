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

#ifndef __COMSTRING_INC__
#   include <ComString.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComString
// ----- ---------
ComString::ComString()
{
    Str = null;
}

ComString::ComString(const ComString& _other)
{
    operator = (_other);
}

ComString::ComString(uint _count)
{
    Str = ::SysAllocStringLen(null, _count);
}

ComString::ComString(uint _count, const wchar* _str)
{
    Str = ::SysAllocStringLen(_str, _count);
}

ComString::ComString(const char* _str)
{
    AutoPtrArray<wchar> p = _A2W(_str);
    Str = ::SysAllocString(p);
}

ComString::ComString(const wchar* _str)
{
    Str = ::SysAllocString(_str);
}

ComString::ComString(const CLSID& _clsid)
{
    wchar* guid;

  ::StringFromCLSID(_clsid, &guid);

    Str = ::SysAllocString(guid);
    
  ::CoTaskMemFree(guid);
}

ComString::~ComString()
{
    if(Str != null)
    {
      ::SysFreeString(Str), Str = null;
    }
}

HRESULT ComString::ToLower()
{
    if(Str != null)
    {
        AutoPtrArray<char> _p = _W2A(Str);

        char* p = ::CharLowerA(_p);

        if(!p)
        {
            return E_OUTOFMEMORY;
        }

        AutoPtrArray<wchar> _p2 = _A2W(p);

        BSTR str = ::SysAllocString(_p2);

        if(!str)
        {
            return E_OUTOFMEMORY;
        }

      ::SysFreeString(Str);

        Str = str;
    }

    return S_OK;
}

HRESULT ComString::ToUpper()
{
    if(Str != null)
    {
        AutoPtrArray<char> _p = _W2A(Str);

        char* p = ::CharUpperA(_p);

        if(!p)
        {
            return E_OUTOFMEMORY;
        }

        AutoPtrArray<wchar> _p2 = _A2W(p);

        BSTR str = ::SysAllocString(_p2);

        if(!str)
        {
            return E_OUTOFMEMORY;
        }

      ::SysFreeString(Str);

        Str = str;
    }

    return S_OK;
}

bool ComString::LoadString(HINSTANCE hinst, uint id)
{
    const ushort const_count = 512;

    AutoPtrArray<tchar> buffer = new tchar[const_count];

    uint count = ::LoadString(hinst, id, buffer, const_count);

    if(Str != null)
    {
      ::SysFreeString(Str);
    }

#ifdef _UNICODE
    Str = (count != 0) ? SysAllocString(buffer) : null;
#else
    AutoPtrArray<wchar> wbuffer = _A2W(buffer);

    Str = (count != 0) ? SysAllocString(wbuffer) : null;
#endif
    return count > 0;
}

HRESULT ComString::ReadFromStream(IStream* _stream)
{
    if(_stream != null && Str == null) // should be empty
    {
        ulong count = 0;

        HRESULT hr = _stream->Read(reinterpret_cast<void*>(&count), sizeof(count), null);

        if((hr == S_OK) && (count > 0))
        {
            // subtract size for terminating NULL which we wrote out
            // since SysAllocStringByteLen overallocates for the NULL
            Str = SysAllocStringByteLen(null, count-sizeof(wchar));

            if(Str == null)
            {
                hr = E_OUTOFMEMORY;
            }
            else
            {
                hr = _stream->Read(reinterpret_cast<void*>(Str), count, null);
            }
        }

        if(hr == S_FALSE)
        {
            hr = E_FAIL;
        }

        return hr;
    }

    return E_FAIL;
}

HRESULT ComString::WriteToStream(IStream* _stream)
{
    if(_stream != null)
    {
        ulong count;
        ulong count2 = Str ? SysStringByteLen(Str)+sizeof(wchar) : 0;

        HRESULT hr = _stream->Write(reinterpret_cast<void*>(&count2), sizeof(count2), &count);

        if(FAILED(hr))
        {
            return hr;
        }

        return count2 ? _stream->Write(reinterpret_cast<void*>(Str), count2, &count) : S_OK;
    }

    return E_FAIL;
}

char* ComString::_W2A(BSTR _str)
{
    if(_str != null)
    {
        uint count;

        char* p = new char[(count = ::SysStringLen(_str))+1];

        count = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)_str, count, p, count, null, null);

        p[count] = 0;

        return p;
    }

    return null;
}

wchar* ComString::_A2W(const char* _str)
{
    if(_str != null)
    {
        uint count;

        wchar* p = new wchar[(count = strlen(_str))+1];

        count = MultiByteToWideChar(CP_ACP, 0, _str, count, p, count);

        p[count] = 0;

        return p;
    }

    return null;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

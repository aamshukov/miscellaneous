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

#ifndef __MIME_PROTOCOL_INC__
#   include <MIMEProtocol.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class MIMEProtocol
// ----- ------------
bool MIMEProtocol::GetContentType(const tchar* _ext, tchar* _type, uint _count)
{
    xassert(_ext != null && _type != null, false);
   _type[0] = 0;
    //
    const ushort _buffer_size_ = 256;
    const ushort _ext_size_    = 64;
    //
    AutoPtrArray<tchar> buffer = new tchar[_buffer_size_];
    AutoPtrArray<tchar> ext    = new tchar[_ext_size_];
    
    if(*_ext != Char::Period)
    {
        ext[0] = Char::Period;
        ext[1] = 0;
    }
    StrCopy(&ext[*_ext == Char::Period ? 0 : 1], _ext);
    //
    uint count = _buffer_size_;

    try
    {
        RegKey key(RegKey::GetClassRootKey(), ext);
        key.QueryValue(_t("Content Type"), null, reinterpret_cast<byte*>(buffer.GetP()), &count);
    }
    catch(RegKey::XRegKey&)
    {
        return false;
    }
    catch(...)
    {
        return false;
    }
    
    count = Min(_count-1, static_cast<uint>(StrLen(buffer)));
    StrNCopy(_type, buffer, count);
   _type[count] = 0;
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

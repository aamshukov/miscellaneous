////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RESOURCE_MANAGER_INL__
#define __RESOURCE_MANAGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ResourceManager
// ----- ---------------
template <typename _T, const tchar* _ResType> ResourceManager<_T, _ResType>::ResourceManager(HINSTANCE hmodule, uint id, LANGID lcid)
{
    MemHandle = null;
    MemPtr    = null;

    HRSRC hres = ::FindResourceEx(module, MAKEINTRESOURCE(id), _ResType, lcid);

    if(hres)
    {
        MemHandle = ::LoadResource(module, hres);

        if(MemHandle)
        {
            MemPtr = (_T*)::LockResource(MemHandle);
        }
    }
}

template <typename _T, const tchar* _ResType> ResourceManager<_T, _ResType>::~ResourceManager()
{
    MemHandle = null;
    MemPtr    = null;
}

template <typename _T, const tchar* _ResType> __INLINE_TEMPLATE__ ResourceManager<_T, _ResType>::operator _T* ()
{
    return MemPtr;
}

template <typename _T, const tchar* _ResType> __INLINE_TEMPLATE__ bool ResourceManager<_T, _ResType>::IsOK() const
{
    return (MemHandle != null && MemPtr != null);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RESOURCE_MANAGER_INL__

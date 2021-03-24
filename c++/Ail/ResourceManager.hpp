////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ResourceManager
// ----- ---------------
template <typename _T, pctchar _ResType> class ResourceManager
{
    protected:
     HGLOBAL    MemHandle;
    _T*         MemPtr;
    public:
     // ctor/dtor
                ResourceManager(HINSTANCE, uint, LANGID = 0);
     virtual   ~ResourceManager();

                operator _T* ();

     // access
     bool       IsOK()  const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __RESOURCE_MANAGER_H__

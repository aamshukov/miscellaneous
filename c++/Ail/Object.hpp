////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1998-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __OBJECT_H__
#define __OBJECT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// Object
// ------
class __DECLSPEC__ Object
{
    protected:
        uint32          Id;
    public:
        // ctor/dtor
                        Object();
        virtual        ~Object();

        // access
        uint32          GetId()         const;
        void            SetId(uint32);

        // api
        virtual Object* Clone()     = 0;
        virtual tchar*  ToString()  = 0;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __OBJECT_H__

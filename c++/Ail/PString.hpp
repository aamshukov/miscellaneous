////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1989-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PSTRING_H__
#define __PSTRING_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// PString
// -------
class __DECLSPEC__ PString : public Object, IComparable
{
    protected:
        tchar*          Data;
    public:
        // ctor/dtor
                        PString();
                        PString(const tchar*);
                        PString(const PString&);
        virtual        ~PString();

        // access
                        operator tchar* ();
                        operator const tchar* ();
                        
        tchar*          ToChar()                    const;

        bool            IsEmpty()                   const;
        uint32          GetLength()                 const;

        // api
        const PString&  operator = (const PString&);

        bool            operator == (const PString&);
        bool            operator < (const PString&);

        Object*         Clone();
        tchar*          ToString();

        int8            CompareTo(const Object&)    const;

        static uint32   StrLen(const tchar*);
        static tchar*   StrCopy(tchar*, const tchar*);
        static tchar*   StrCat(tchar*, const tchar*);
        static tchar*   StrChar(const tchar*, tchar);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PSTRING_H__

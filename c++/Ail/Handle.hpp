////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HANDLE_H__
#define __HANDLE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Handle
// ----- ------
template <typename _Handle = HANDLE> class Handle
{
    protected:
    _Handle         HValue;
    public:
     // ctor/dtor
                    Handle(_Handle = 0);
                    Handle(const Handle&);
                   ~Handle();

     const Handle&  operator = (const Handle&);

     // access
                    operator _Handle ();
                    operator const _Handle ()   const;

     bool           operator == (_Handle)       const;
     bool           operator != (_Handle)       const;

    _Handle         GetHandle();
     const _Handle  GetHandle()                 const;
     void           SetHandle(_Handle);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HANDLE_H__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1998-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IDELETEABLEIMPL_H__
#define __IDELETEABLEIMPL_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// IDeleteableImpl
// ---------------
class __DECLSPEC__ IDeleteableImpl : public IDeleteable
{
    public:

    enum EDelState
    {
        eDelete   = 1,
        eNoDelete = 2
    };

    protected:
        typedef EDelState _State;

       _State       State;
    public:
     // ctor/dtor
                    IDeleteableImpl(_State = eDelete);

     // access
     bool           ShouldDelete()                                  const;

    _State          GetDelState()                                   const;
     void           SetDelState(_State = IDeleteableImpl::eDelete);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IDELETEABLEIMPL_H__

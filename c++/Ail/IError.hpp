////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1989-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IERROR_H__
#define __IERROR_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// IError
// ------
interface __DECLSPEC__ IError
{
    virtual const ErrorList&    GetErrorList()   const          = 0;
    virtual void                AddError(uint32)                = 0;
    virtual void                AddError(uint32, const tchar*)  = 0;
    virtual void                Discard()                       = 0;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IERROR_H__

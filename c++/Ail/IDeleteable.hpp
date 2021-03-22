////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1989-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IDELETEABLE_H__
#define __IDELETEABLE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// IDeleteable
// -----------
interface __DECLSPEC__ IDeleteable
{
    virtual bool ShouldDelete() const = 0;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IDELETEABLE_H__

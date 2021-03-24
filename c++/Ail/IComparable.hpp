////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of UI Library.                                                      .
//  1998-2003 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ICOMPARABLE_H__
#define __ICOMPARABLE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// IComparable
// -----------
interface __DECLSPEC__ IComparable
{
    virtual int8 CompareTo(const Object&) const = 0;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ICOMPARABLE_H__

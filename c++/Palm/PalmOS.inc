////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_OS_INC__
#define __PALM_OS_INC__

#pragma once
////////////////
// configuration
// -------------
#define __PALM_OS_MEMORY_ALLOCATION__
#define __palm_debug_level__ 1 // 0 - no debug, 1 - full debug
////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifdef __PALM_OS__
#   include <PalmOS.h>
#   include <PalmCompatibility.h>
#   include <SysUtils.h>
#   include <typeinfo>
#   include <string>
#endif

#ifndef __AUTOPTR_INC__
#   include <AutoPtr.inc>
#endif

#ifndef __PALM_OS_H__
#   include <PalmOS.hpp>
#endif

#ifndef __PALM_OS_INL__
#   include <PalmOS.inl>
#endif

#endif // __PALM_OS_INC__
////////////////////////////////////////////////////////////////////////////////////////

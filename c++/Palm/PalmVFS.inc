////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_VFS_INC__
#define __PALM_VFS_INC__

#pragma once

#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#if (__PALM_OS__ >= 0x0400)
#   include <VFSMgr.h>
#endif

#ifndef __PALM_ERROR_INC__
#   include <PalmError.inc>
#endif

#ifndef __PALM_VFS_H__
#   include <PalmVFS.hpp>
#endif

#ifndef __PALM_VFS_INL__
#   include <PalmVFS.inl>
#endif

#endif // __PALM_VFS_INC__
////////////////////////////////////////////////////////////////////////////////////////

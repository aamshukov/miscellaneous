////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_MEMORY_H__
#define __PALM_MEMORY_H__

#ifdef __PALM_OS__

#pragma once

// no namespace
////////////////////////////////////////////////////////////////////////////////////////
#ifdef __PALM_OS_MEMORY_ALLOCATION__

void* operator new(size_t);
void* operator new[] (size_t);
void  operator delete(void*);
void  operator delete[] (void*);

#endif // __PALM_OS_MEMORY_ALLOCATION__
////////////////////////////////////////////////////////////////////////////////////////

#endif // __PALM_OS__
#endif // __PALM_MEMORY_H__

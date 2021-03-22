////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HIGH_PRECISION_H__
#define __HIGH_PRECISION_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
#ifdef __PIOLOGIE__
typedef Integer int_h;
#else // fmp library
typedef HPInteger int_h;
#endif
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HIGH_PRECISION_H__

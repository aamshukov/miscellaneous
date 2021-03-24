////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMINIT_INL__
#define __COMINIT_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComInit
// ----- -------
__INLINE__ HRESULT ComInit::Initialize(bool _ole)
{
    return _ole ? ::OleInitialize(null) : ::CoInitialize(null);
}

__INLINE__ void ComInit::Uninitialize(bool _ole)
{
    _ole ? ::OleUninitialize() : ::CoUninitialize();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMINIT_INL__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __XCOM_INC__
#   include <XCOM.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class XCOM
// ----- ----
XCOM::XCOM(HRESULT _hr, uint _error) : X(_error), HResult(_hr)
{
}

XCOM::~XCOM()
{
}

uint XCOM::GetHResult() const
{
    return HResult;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

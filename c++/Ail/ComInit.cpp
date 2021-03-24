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

#ifndef __COMINIT_INC__
#   include <ComInit.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComInit
// ----- -------
ComInit::ComInit(bool _init, bool _ole) : Init(_init)
{
    if(Init)
    {
        HRESULT hr = ComInit::Initialize(_ole);

        if(FAILED(hr))
        {
            throw ComInit::XComInit(hr);
        }
    }
}

ComInit::~ComInit()
{
    if(Init)
    {
        ComInit::Uninitialize();
    }
}

ComInit::XComInit::XComInit(HRESULT _hr) : XCOM(_hr)
{
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

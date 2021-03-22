////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __XCOM_H__
#define __XCOM_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class XCOM
// ----- ----
class __DECLSPEC__ XCOM : public X
{
    private:
     HRESULT    HResult;
    public:
                XCOM(HRESULT, uint = 0);
     virtual   ~XCOM();

     uint       GetHResult()    const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __XCOM_H__

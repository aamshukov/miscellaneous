////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMINIT_H__
#define __COMINIT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComInit
// ----- -------
class __DECLSPEC__ ComInit
{
    private:
     bool           Init;
    public:
                    ComInit(bool = true, bool = true);
                   ~ComInit();

     static HRESULT Initialize(bool = true);
     static void    Uninitialize(bool = true);
    public:

    class __DECLSPEC__ XComInit : public XCOM
    {
        public:
            XComInit(HRESULT);
    };

    friend class XComInit;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMINIT_H__

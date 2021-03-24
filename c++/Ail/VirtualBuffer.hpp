////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __VIRTUALBUFFER_H__
#define __VIRTUALBUFFER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class VirtualBufferHelper
// ----- -------------------
template <typename T> class VirtualBufferHelper
{
    public:
     virtual T* operator () (T*);
};
////////////////////////////////////////////////////////////////////////////////////////
// class VirtualBuffer
// ----- -------------
template <typename T = byte, uint _MaxCount = 4096> class VirtualBuffer
{
    protected:
     T*                                 Top;
     T*                                 Base;
     T*                                 Current;
    public:
     // ctor/dtor
                                        VirtualBuffer();
                                       ~VirtualBuffer();

     // operations
     const T&                           operator [] (int)           const;
                                        operator T* ();

     // protocol
     int                                Except(EXCEPTION_POINTERS*);

     void                               Seek(int);
     void                               SetAt(int, const T&);

     T&                                 Read();

     void                               Write(const T&);

     template <typename Helper> void    WriteBulk(Helper& _helper)
     {
        __try
        {
            Current = _helper(Base);
            Top     = Current > Top ? Current : Top;
        }
        __except(Except(GetExceptionInformation()))
        {
        }
     }
};

typedef VirtualBuffer<byte> VirtualStream;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __VIRTUALBUFFER_H__

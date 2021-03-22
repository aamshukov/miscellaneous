////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COMALLOCATOR_H__
#define __COMALLOCATOR_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ComAllocator
// ----- ------------
class __DECLSPEC__ ComAllocator : private SyncObject
{
    private:
     bool                   Init;

     ComPtr<IMalloc>        _Interface;
    private:
                            ComAllocator(const ComAllocator&);
     const ComAllocator&    operator = (const ComAllocator&);
    public:
                            ComAllocator(bool = true);
     virtual               ~ComAllocator();

     bool                   IsInitMemory()                      const;
     void                   SetInitMemory(bool = true);

     virtual void*          Allocate(ulong);
     virtual void*          Reallocate(void*, ulong);
     virtual void           Free(void*);

     virtual int            IsAllocated(void*);

     virtual ulong          GetSize(void*);

     virtual void           UpdateHeap();

     static ComAllocator& GetComAllocator();
    public:

    class __DECLSPEC__ XComAllocator : public XCOM
    {
        public:
            XComAllocator(HRESULT);
    };

    friend class XComAllocator;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COMALLOCATOR_H__

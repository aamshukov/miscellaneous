////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MEMORY_H__
#define __MEMORY_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(push, before, 2)
////////////////////////////////////////////////////////////////////////////////////////
// class MemAlloc
// ----- --------
template <typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAlocator> class MemAlloc
{
    private:
     
     enum EConst
     {
        DefMaxSize = 256
     };

    private:

    class _Header
    {
    };

    private:
     ushort     MaxSize;
    protected:

    public:
     // ctor/dtor
                MemAlloc(uint = DefMaxSize);
               ~MemAlloc();

     // access
     ushort     GetMaxSize()    const;

     // protocol
     void*      Allocate(uint, bool = false);
     void*      Realloc(uint)
     void       Deallocate(void*);

     void       CheckIntegrity();
}
////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(pop, before)
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MEMORY_H__

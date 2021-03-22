////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_MEMORY_INC__
#   include <PalmMemory.inc>
#endif

#ifdef __PALM_OS__

// no namespace
////////////////////////////////////////////////////////////////////////////////////////
#ifdef __PALM_OS_MEMORY_ALLOCATION__
//
static char* _prompt_out_of_memory_ = "Not enough memory for operator new";
static char* _prompt_invalid_arg_ = "Invalid arg in operation delete";
//
void* operator new (size_t _size)
{
    void* p = ::MemPtrNew(ail::Max(static_cast<size_t>(1), _size));
    
    if(p == null)
    {
        FATAL_ERROR(_prompt_out_of_memory_);
    }
    return p;
}

void* operator new[] (size_t _size)
{
    void* p = ::MemPtrNew(ail::Max(static_cast<size_t>(1), _size));

    if(p == null)
    {
        FATAL_ERROR(_prompt_out_of_memory_);
    }
    return p;
}

void operator delete(void* _p)
{
	using namespace ail;
    palmxassert(_p != null, Error::eInvalidArg, Error);
    Err err = ::MemPtrFree(_p);
}

void operator delete[] (void* _p)
{
	using namespace ail;
    palmxassert(_p != null, Error::eInvalidArg, Error);
    Err err = ::MemPtrFree(_p);
}
#endif // __PALM_OS_MEMORY_ALLOCATION__
////////////////////////////////////////////////////////////////////////////////////////

#endif // __PALM_OS__


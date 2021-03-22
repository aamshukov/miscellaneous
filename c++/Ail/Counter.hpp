////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COUNTER_H__
#define __COUNTER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Counter
// ----- -------
template <typename T> class Counter
{
    // use as: ": private Counter<X>"
    // it's possible make public GetCount(): "using Counter<X>::GetCount();"
    private:
     static uint    Count;
    private:
     void*          operator new(size_t);
     void           operator delete(void*);
    public:
                    Counter();
                    Counter(const Counter&);
                   ~Counter(); // NOT virtual ! ...
     
     static uint    GetCount();
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COUNTER_H__

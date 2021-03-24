////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PAIR_H__
#define __PAIR_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Pair
// ----- ----
template <typename F, typename S> class Pair
{
    public:
     F                  First;
     S                  Second;
    public:
                        Pair();
                        Pair(const Pair&);
                        Pair(F&, S&);

     const Pair<F, S>&  operator = (const Pair<F, S>&);
     bool               operator == (const Pair<F, S>&);

     F                  GetFirst()    const;
     void               SetFirst(F);

     S                  GetSecond()   const;
     void               SetSecond(S);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PAIR_H__

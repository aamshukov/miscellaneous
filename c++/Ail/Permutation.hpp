////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
// Synopsis:
//      Wendy Myrvold, Frank Ruskey, April, 2000
//      "Ranking and Unranking Permutations in Linear Time"
//      wendym@csr.uvic.ca  fruskey@csr.uvic.ca
//
//      ALGORITHM 317 (CACM) April-May-July 1967
//      Charles L. Robinson
//      Institute for Computer Research, U. of Chicago, Chicago, Ill.
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PERMUTATION_H__
#define __PERMUTATION_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Permutation
// ----- -----------
class __DECLSPEC__ Permutation : StateObject
{
    typedef ulong* _P;

    private:
    _P              P;  // permutation
    _P              PR; // reverse permutation
     ulong          N;  // size of permutation
    private:
     void           Shift(ulong*, ulong, ulong);
    protected:
     void           UnrankPermutation2(ulong, int_h);
     int_h          RankPermutation2(ulong);
    public:
     // ctor/dtor
                    Permutation(ulong = 256, ulong* = null, ulong* = null);
     virtual       ~Permutation();

     // access
     const ulong*   GetPermutation()            const;
     const ulong*   GetReversePermutation()     const;

     ulong          GetSize()                   const;
                   
     // protocol
     void           Permute(ulong);

     void           BuildIdentityPermutation();
     void           BuildReversePermutation();

     void           UnrankPermutation(int_h);
     int_h          RankPermutation();

     void           InversionFromPermutation(ulong*);
     void           PermutationFromInversion(const ulong*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PERMUTATION_H__

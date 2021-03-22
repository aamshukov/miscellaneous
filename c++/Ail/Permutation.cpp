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

#ifndef __PERMUTATION_INC__
#   include <Permutation.inc>
#endif

//#define __RECURSION_ALGO__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Permutation
// ----- -----------
Permutation::Permutation(ulong _n, ulong* _p, ulong* _pr) : N(_n)
{
    P  = _p  == null ? new ulong[N] : _p;
    PR = _pr == null ? new ulong[N] : _pr;
    //
    State = _p == null ? StateObject::eDelete : StateObject::eNoDelete;
}

Permutation::~Permutation()
{
    if(IsShouldDelete())
    {
        delete [] P,  P  = null;
        delete [] PR, PR = null;
    }
}

void Permutation::Permute(ulong _n)
{
    // magic ! ...
    // P starts from 1
   _xassertv(X, P != null, 0);
    //
    register ulong i, q, r, x, j, k;

    for(i = 0; i < N; i++)
    {
        P[i] = 0;
    }

    k = _n;

    for(i = N; i > 0; i--)
    {
        q = k/i;
        r = k-q*i;
        x = 0;
        j = N-1;
no:
        if(P[j] == 0)
        {
            if(x == r)
            {
                goto it;
            }
            else
            {
                x++;
            }
        }

        j--;
        goto no;
it:
        P[j] = i, k = q;
    }
}

void Permutation::BuildIdentityPermutation()
{
   _xassertv(X, P != null, 0);
    //
    for(register ulong i = 0; i < N; i++)
    {
        P[i] = i;
    }
}

void Permutation::BuildReversePermutation()
{
   _xassertv(X, P != null && PR != null, 0);
    //
    for(register ulong i = 0; i < N; i++)
    {
        PR[P[i]] = i;
    }
}

void Permutation::UnrankPermutation(int_h _rank)
{
    BuildIdentityPermutation();
    UnrankPermutation2(N, _rank);
}

void Permutation::UnrankPermutation2(ulong _n, int_h _rank)
{
   _xassertv(X, P != null, 0);
    //
#ifdef __RECURSION_ALGO__
    if(_n > 0)
    {
        Swap<ulong>(P[_n-1], P[static_cast<ulong>(_rank%_n)]);
        UnrankPermutation2(_n-1, _rank/_n);
    }
#else
    while(_n > 0)
    {
        Swap<ulong>(P[_n-1], P[static_cast<ulong>(_rank%_n)]);
       _rank /= _n, --_n;
    }
#endif
}

int_h Permutation::RankPermutation()
{
    BuildReversePermutation();
    return RankPermutation2(N);
}

int_h Permutation::RankPermutation2(ulong _n)
{
   _xassertv(X, P != null && PR != null && _n <= N, 0);
    //
    if(_n == 1)
    {
        return int_h();
    }

    ulong s = P[_n-1];

    Swap<ulong>(P[_n-1], P[PR[_n-1]]);
    Swap<ulong>(PR[s], PR[_n-1]);

    return s+_n*RankPermutation2(_n-1);
}

void Permutation::InversionFromPermutation(ulong* _inv)
{
   _xassertv(X, P != null && _inv != null, 0);
    //
    for(register ulong k = 0; k < N; k++)
    {
        register ulong val = 0;

        for(register ulong i = 0; P[i] != k; i++)
        {
            if(k < P[i])
            {
                val++;
            }
        }

       _inv[k] = val;
    }
}

void Permutation::PermutationFromInversion(const ulong* _inv)
{
   _xassertv(X, P != null && _inv != null, 0);
    //
    for(register ulong i = 0, k = N-1; /*k >= 0*/; k--, i++)
    {
        if(_inv[k] == 0)
        {
            if(k < N-1) // the last entry of the inversion is always 0
            {
                Shift(P, 0, k+1);
            }
            P[0] = k;
        }
        else
        {
            Shift(P, _inv[k], N-k-(_inv[k]+1));
            P[_inv[k]] = k;
        }

        // work around
        if(k == 0)
        {
            break;
        }
    }
}

void Permutation::Shift(ulong* _buffer, ulong _i, ulong _count)
{
    for(register ulong i = _i+_count; i > _i; i--)
    {
        _buffer[i] = _buffer[i-1];
    } 
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __IJ_H__
#define __IJ_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class IJ
// ----- --
template <typename C = uint, typename R = uint, typename S = uint> class IJ
{
    public:
     C                  Column;
     R                  Row;
     S                  Stuff;
    public:
                        IJ();
                        IJ(const IJ&);
                        IJ(C&, R&);

     const IJ<C, R, S>& operator = (const IJ<C, R, S>&);

     bool               operator == (const IJ<C, R, S>&);

     C                  GetColumn()    const;
     void               SetColumn(C);

     R                  GetRow()       const;
     void               SetRow(R);

     S                  GetStuff()     const;
     void               SetStuff(S);
};

typedef IJ<> Location;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __IJ_H__

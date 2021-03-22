////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
// This implementation of high precision integers is based on the following source:    .
// FREE MP - a public domain implementation of a subset of the GNU gmp library         .
// by Mark Henderson <markh@wimsey.bc.ca> VERSION 0.1                                  .
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HP_INTEGER_H__
#define __HP_INTEGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HPInteger
// ----- ---------
class __DECLSPEC__ HPInteger
{
    private:
     mp_int             MPInt;
    public:
     // ctor/dtor
                        HPInteger();
                        HPInteger(long);
                        HPInteger(ulong);
                        HPInteger(const HPInteger&);
                        HPInteger(char*, int = 10);
     virtual           ~HPInteger();

     // access
     const mp_int&      GetData()           const;
     ulong              GetSize(int = 10)   const;

     // operators
                        operator long();
                        operator ulong();

     const HPInteger&   operator = (const HPInteger&);
     const HPInteger&   operator = (long);
     const HPInteger&   operator = (ulong);

     bool               operator == (const HPInteger&);
     bool               operator == (long);
     bool               operator == (ulong);

     bool               operator != (const HPInteger&);
     bool               operator != (long);
     bool               operator != (ulong);

     bool               operator < (const HPInteger&);
     bool               operator < (long);
     bool               operator < (ulong);

     const HPInteger&   operator += (long);
     const HPInteger&   operator += (ulong);
     const HPInteger&   operator += (const HPInteger&);

     const HPInteger&   operator -= (long);
     const HPInteger&   operator -= (ulong);
     const HPInteger&   operator -= (const HPInteger&);

     const HPInteger&   operator *= (long);
     const HPInteger&   operator *= (ulong);
     const HPInteger&   operator *= (const HPInteger&);

     const HPInteger&   operator /= (long);
     const HPInteger&   operator /= (ulong);
     const HPInteger&   operator /= (const HPInteger&);

     const HPInteger&   operator %= (long);
     const HPInteger&   operator %= (ulong);
     const HPInteger&   operator %= (const HPInteger&);

     friend HPInteger   operator + (const HPInteger&, long);
     friend HPInteger   operator + (long, const HPInteger&);
     friend HPInteger   operator + (const HPInteger&, ulong);
     friend HPInteger   operator + (ulong, const HPInteger&);
     friend HPInteger   operator + (const HPInteger&, const HPInteger&);

     friend HPInteger   operator - (const HPInteger&, long);
     friend HPInteger   operator - (long, const HPInteger&);
     friend HPInteger   operator - (const HPInteger&, ulong);
     friend HPInteger   operator - (ulong, const HPInteger&);
     friend HPInteger   operator - (const HPInteger&, const HPInteger&);

     friend HPInteger   operator * (const HPInteger&, long);
     friend HPInteger   operator * (long, const HPInteger&);
     friend HPInteger   operator * (const HPInteger&, ulong);
     friend HPInteger   operator * (ulong, const HPInteger&);
     friend HPInteger   operator * (const HPInteger&, const HPInteger&);

     friend HPInteger   operator / (const HPInteger&, long);
     friend HPInteger   operator / (long, const HPInteger&);
     friend HPInteger   operator / (const HPInteger&, ulong);
     friend HPInteger   operator / (ulong, const HPInteger&);
     friend HPInteger   operator / (const HPInteger&, const HPInteger&);

     friend HPInteger   operator % (const HPInteger&, long);
     friend HPInteger   operator % (long, const HPInteger&);
     friend HPInteger   operator % (const HPInteger&, ulong);
     friend HPInteger   operator % (ulong, const HPInteger&);
     friend HPInteger   operator % (const HPInteger&, const HPInteger&);

     // protocol
     char*              HPI2A(char*, int = 10);
     void               BuildInstance(const byte*, ulong, int = 10);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HP_INTEGER_H__

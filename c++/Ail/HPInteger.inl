////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __HP_INTEGER_INL__
#define __HP_INTEGER_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HPInteger
// ----- ---------
__INLINE__ const mp_int& HPInteger::GetData() const
{
    return MPInt;
}

__INLINE__ ulong HPInteger::GetSize(int _base) const
{
    return mpz_sizeinbase(const_cast<mp_int*>(&MPInt), _base);
}

__INLINE__ char* HPInteger::HPI2A(char* _buffer, int _base)
{
    return mpz_get_str(_buffer, _base, &MPInt);
}

__INLINE__ HPInteger::operator long()
{
    return mpz_get_si(&MPInt);
}

__INLINE__ HPInteger::operator ulong()
{
    return mpz_get_ui(&MPInt);
}

__INLINE__ bool HPInteger::operator == (long _v)
{
    return mpz_cmp_si(&MPInt, _v) == 0;
}

__INLINE__ bool HPInteger::operator == (ulong _v)
{
    return mpz_cmp_ui(&MPInt, _v) == 0;
}

__INLINE__ bool HPInteger::operator == (const HPInteger& _other)
{
    return mpz_cmp(&MPInt, const_cast<mp_int*>(&_other.MPInt)) == 0;
}

__INLINE__ bool HPInteger::operator != (long _v)
{
    return mpz_cmp_si(&MPInt, _v) != 0;
}

__INLINE__ bool HPInteger::operator != (ulong _v)
{
    return mpz_cmp_ui(&MPInt, _v) != 0;
}

__INLINE__ bool HPInteger::operator != (const HPInteger& _other)
{
    return mpz_cmp(&MPInt, const_cast<mp_int*>(&_other.MPInt)) != 0;
}

__INLINE__ bool HPInteger::operator < (long _v)
{
    return mpz_cmp_si(&MPInt, _v) < 0;
}

__INLINE__ bool HPInteger::operator < (ulong _v)
{
    return mpz_cmp_ui(&MPInt, _v) < 0;
}

__INLINE__ bool HPInteger::operator < (const HPInteger& _other)
{
    return mpz_cmp(&MPInt, const_cast<mp_int*>(&_other.MPInt)) < 0;
}

__INLINE__ const HPInteger& HPInteger::operator += (long _v)
{
    mpz_add_ui(&MPInt, &MPInt, static_cast<ulong>(_v));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator += (ulong _v)
{
    mpz_add_ui(&MPInt, &MPInt, _v);
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator += (const HPInteger& _v)
{
    mpz_add(&MPInt, &MPInt, const_cast<mp_int*>(&_v.MPInt));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator -= (long _v)
{
    mpz_sub_ui(&MPInt, &MPInt, static_cast<ulong>(_v));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator -= (ulong _v)
{
    mpz_sub_ui(&MPInt, &MPInt, _v);
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator -= (const HPInteger& _v)
{
    mpz_sub(&MPInt, &MPInt, const_cast<mp_int*>(&_v.MPInt));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator *= (long _v)
{
    mpz_mul_ui(&MPInt, &MPInt, static_cast<ulong>(_v));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator *= (ulong _v)
{
    mpz_mul_ui(&MPInt, &MPInt, _v);
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator *= (const HPInteger& _v)
{
    mpz_mul(&MPInt, &MPInt, const_cast<mp_int*>(&_v.MPInt));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator /= (long _v)
{
    mpz_div_ui(&MPInt, &MPInt, static_cast<ulong>(_v));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator /= (ulong _v)
{
    mpz_div_ui(&MPInt, &MPInt, _v);
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator /= (const HPInteger& _v)
{
    mpz_div(&MPInt, &MPInt, const_cast<mp_int*>(&_v.MPInt));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator %= (long _v)
{
    mpz_mod_ui(&MPInt, &MPInt, static_cast<ulong>(_v));
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator %= (ulong _v)
{
    mpz_mod_ui(&MPInt, &MPInt, _v);
    return *this;
}

__INLINE__ const HPInteger& HPInteger::operator %= (const HPInteger& _v)
{
    mpz_mod(&MPInt, &MPInt, const_cast<mp_int*>(&_v.MPInt));
    return *this;
}

__INLINE__ HPInteger operator + (const HPInteger& _hpi, long _v)
{
    HPInteger hpi  = _hpi;
              hpi += _v;
    return hpi;
}

__INLINE__ HPInteger operator + (long _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi += _v;
    return hpi;
}

__INLINE__ HPInteger operator + (const HPInteger& _hpi, ulong _v)
{
    HPInteger hpi  = _hpi;
              hpi += _v;
    return hpi;
}

__INLINE__ HPInteger operator + (ulong _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi += _v;
    return hpi;
}

__INLINE__ HPInteger operator + (const HPInteger& _hpi1, const HPInteger& _hpi2)
{
    HPInteger hpi  = _hpi1;
              hpi += _hpi2;
    return hpi;
}

__INLINE__ HPInteger operator - (const HPInteger& _hpi, long _v)
{
    HPInteger hpi  = _hpi;
              hpi -= _v;
    return hpi;
}

__INLINE__ HPInteger operator - (long _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi -= _v;
    return hpi;
}

__INLINE__ HPInteger operator - (const HPInteger& _hpi, ulong _v)
{
    HPInteger hpi  = _hpi;
              hpi -= _v;
    return hpi;
}

__INLINE__ HPInteger operator - (ulong _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi -= _v;
    return hpi;
}

__INLINE__ HPInteger operator - (const HPInteger& _hpi1, const HPInteger& _hpi2)
{
    HPInteger hpi  = _hpi1;
              hpi -= _hpi2;
    return hpi;
}

__INLINE__ HPInteger operator * (const HPInteger& _hpi, long _v)
{
    HPInteger hpi  = _hpi;
              hpi *= _v;
    return hpi;
}

__INLINE__ HPInteger operator * (long _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi *= _v;
    return hpi;
}

__INLINE__ HPInteger operator * (const HPInteger& _hpi, ulong _v)
{
    HPInteger hpi  = _hpi;
              hpi *= _v;
    return hpi;
}

__INLINE__ HPInteger operator * (ulong _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi *= _v;
    return hpi;
}

__INLINE__ HPInteger operator * (const HPInteger& _hpi1, const HPInteger& _hpi2)
{
    HPInteger hpi  = _hpi1;
              hpi *= _hpi2;
    return hpi;
}

__INLINE__ HPInteger operator / (const HPInteger& _hpi, long _v)
{
    HPInteger hpi  = _hpi;
              hpi /= _v;
    return hpi;
}

__INLINE__ HPInteger operator / (long _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi /= _v;
    return hpi;
}

__INLINE__ HPInteger operator / (const HPInteger& _hpi, ulong _v)
{
    HPInteger hpi  = _hpi;
              hpi /= _v;
    return hpi;
}

__INLINE__ HPInteger operator / (ulong _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi /= _v;
    return hpi;
}

__INLINE__ HPInteger operator / (const HPInteger& _hpi1, const HPInteger& _hpi2)
{
    HPInteger hpi  = _hpi1;
              hpi /= _hpi2;
    return hpi;
}

__INLINE__ HPInteger operator % (const HPInteger& _hpi, long _v)
{
    HPInteger hpi  = _hpi;
              hpi %= _v;
    return hpi;
}

__INLINE__ HPInteger operator % (long _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi %= _v;
    return hpi;
}

__INLINE__ HPInteger operator % (const HPInteger& _hpi, ulong _v)
{
    HPInteger hpi  = _hpi;
              hpi %= _v;
    return hpi;
}

__INLINE__ HPInteger operator % (ulong _v, const HPInteger& _hpi)
{
    HPInteger hpi  = _hpi;
              hpi %= _v;
    return hpi;
}

__INLINE__ HPInteger operator % (const HPInteger& _hpi1, const HPInteger& _hpi2)
{
    HPInteger hpi  = _hpi1;
              hpi %= _hpi2;
    return hpi;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __HP_INTEGER_INL__

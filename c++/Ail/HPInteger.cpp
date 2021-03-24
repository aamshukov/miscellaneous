////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __HP_INTEGER_INC__
#   include <HPInteger.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class HPInteger
// ----- ---------
HPInteger::HPInteger()
{
    mpz_init_set_si(&MPInt, 0);
}

HPInteger::HPInteger(long _val)
{
    mpz_init_set_si(&MPInt, _val);
}

HPInteger::HPInteger(ulong _val)
{
    mpz_init_set_ui(&MPInt, _val);
}

HPInteger::HPInteger(const HPInteger& _other)
{
    if(this != &_other)
    {
        mpz_init_set(&MPInt, const_cast<mp_int*>(&_other.MPInt));
    }
}

HPInteger::HPInteger(char* _val, int _base)
{
    mpz_init_set_str(&MPInt, _val, _base);
}

HPInteger::~HPInteger()
{
    mpz_clear(&MPInt);
}

const HPInteger& HPInteger::operator = (const HPInteger& _other)
{
    if(this != &_other)
    {
        mpz_set(&MPInt, const_cast<mp_int*>(&_other.MPInt));
    }
    return *this;
}

const HPInteger& HPInteger::operator = (long _val)
{
    mpz_set_si(&MPInt, _val);
    return *this;
}

const HPInteger& HPInteger::operator = (ulong _val)
{
    mpz_set_ui(&MPInt, _val);
    return *this;
}

void HPInteger::BuildInstance(const byte* _buffer, ulong _size, int _base)
{
    if(_buffer == null || _size == 0)
    {
        return;
    }
    //
    static char* _lut_ = "0123456789ABCDEF";
    //
    AutoPtrArray<char> buffer(new char[_size*2+1]); // +1 terminator for fmp

    for(ulong i = 0, j = 0; i < _size; i++, j += 2)
    {
#if __ENDIAN__ == __LITTLE_ENDIAN__
        *(buffer+j+0) = _lut_[(_buffer[i] >> 4) & 0x0F];
        *(buffer+j+1) = _lut_[(_buffer[i] >> 0) & 0x0F];
#else
        *(buffer+j+0) = _lut_[(_buffer[i] >> 0) & 0x0F];
        *(buffer+j+1) = _lut_[(_buffer[i] >> 4) & 0x0F];
#endif
    }

    *(buffer+j) = 0; // terminator for fmp
    mpz_set_str(&MPInt, buffer, _base);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

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

#ifndef __ENDIAN_ORDER_INC__
#   include <EndianOrder.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class EndianOrder
// ----- -----------
EndianOrder::EndianOrder()
{
    int x = 1;
    LittleEndian = (*(char*)&x == 1);
#ifdef __LITTLE_ENDIAN__
    ReverseOrder = false;
#else
    ReverseOrder = true;
#endif
}

EndianOrder::~EndianOrder()
{
}

void EndianOrder::Arrange(byte* _buffer, uint _count)
{
    if(_buffer == null || _count == 0)
    {
        return;
    }

    if(ReverseOrder)
    {
        for(uint j = 0, i = _count-1; j < i;)
        {
            byte tmp = _buffer[j];
           _buffer[j++] = _buffer[i];
           _buffer[i--] = tmp;
        }
    }
}

void EndianOrder::Arrange(byte* _o_buffer, const byte* _i_buffer, uint _count)
{
    if(_i_buffer == null || _o_buffer == null || _count == 0)
    {
        return;
    }

    if(ReverseOrder)
    {
        for(uint j = 0, i = _count; j < _count;)
        {
            _o_buffer[--i] = _i_buffer[j++];
        }
    }
    else
    {
        memcpy(_o_buffer, _i_buffer, _count);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

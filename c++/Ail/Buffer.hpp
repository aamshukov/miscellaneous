////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __BUFFER_H__
#define __BUFFER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Buffer
// ----- ------
template <typename _T = byte> class Buffer
{
    typedef std::basic_string<_T>  _String;

    protected:
    _String         String_;
    public:
     // ctor/dtor
                    Buffer();
                    Buffer(const Buffer&, uint = 0, uint = -1);
                    Buffer(const _T*, uint = -1);
     explicit       Buffer(uint, _T = 0);
     virtual       ~Buffer();

     // access
     const _String& GetString()                     const;

     // operations
     Buffer&        operator = (const Buffer&);
     Buffer&        operator = (const _T*);
     Buffer&        operator = (_T);

     Buffer&        operator += (const Buffer&);
     Buffer&        operator += (const _T*);
     Buffer&        operator += (_T);

     Buffer&        operator -= (uint);

     bool           operator == (const Buffer&);
     bool           operator != (const Buffer&);

     const _T&      operator [] (uint)              const;

     // protocol
     bool           IsEmpty()                       const;
     void           SetEmpty();

     Buffer&        Assign(const Buffer&, uint = 0, uint = -1);
     Buffer&        Assign(const _T*, uint = -1);
     Buffer&        Assign(_T, uint = 1);

     Buffer&        Append(const Buffer&, uint = 0, uint = -1);
     Buffer&        Append(const _T*, uint = -1);
     Buffer&        Append(_T, uint = 1);

     Buffer&        Insert(uint, const Buffer&, uint = 0, uint = -1);
     Buffer&        Insert(uint, const _T*, uint = -1);
     Buffer&        Insert(uint, _T, uint = 1);

     uint           GetSize()                       const;
     uint           GetCapacity()                   const;
     
     void           Resize(uint);
     void           Reserve(uint);

     void           Reset();
     void           Remove(uint, uint = 1);

     void           Swap(Buffer&);
};
////////////////////////////////////////////////////////////////////////////////////////
// class XBuffer
// ----- -------
class XBuffer : public X
{
    public:
        XBuffer(uint = X::Failure);
};
////////////////////////////////////////////////////////////////////////////////////////
typedef Buffer<byte>  StreamBuffer;
typedef Buffer<char>  CharBuffer;
typedef Buffer<wchar> WcharBuffer;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __BUFFER_H__

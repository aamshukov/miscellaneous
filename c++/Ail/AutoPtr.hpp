////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AUTOPTR_H__
#define __AUTOPTR_H__

#pragma once

#ifdef __PALM_OS__
using namespace std;
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class AutoPtrBase
// ----- -----------
template <typename _T> class AutoPtrBase
{
    private:
     void*      operator new(size_t);
     void       operator delete(void*);
    protected:
    _T*         P;
    protected:
     // ctor/dtor
                AutoPtrBase();
                AutoPtrBase(_T*);
    public:
     // access
    _T*         GetP()              const;

     // operators
    _T&         operator  *  ()     const;
    _T**        operator  &  ();    // ! ...
                operator _T* ()     const;
     bool       operator  !  ()     const;

     // protocol
    _T*         Relinquish();
    _T*         Reset(_T*);
};
////////////////////////////////////////////////////////////////////////////////////////
// class AutoPtr
// ----- -------
template <typename _T> class AutoPtr : public AutoPtrBase<_T>
{
    public:
     // ctor/dtor
#ifdef __VISUAL_STUDIO__
                  AutoPtr()               throw();
                  AutoPtr(_T*)            throw();
                 ~AutoPtr()               throw();
#else
                  AutoPtr();
                  AutoPtr(_T*);
                 ~AutoPtr();
#endif

     // operators
#ifdef __VISUAL_STUDIO__
     AutoPtr<_T>& operator = (_T*)        throw();
    _T*           operator -> ()    const throw();
#else
     AutoPtr<_T>& operator = (_T*);
    _T*           operator -> ()    const;
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
// class AutoPtrArray
// ----- ------------
template <typename _T> class AutoPtrArray : public AutoPtrBase<_T>
{
    public:
     // ctor/dtor
#ifdef __VISUAL_STUDIO__
                        AutoPtrArray()            throw();
                        AutoPtrArray(ulong)       throw();
                        AutoPtrArray(_T _array[]) throw();
                       ~AutoPtrArray()            throw();
#else
                        AutoPtrArray();
                        AutoPtrArray(ulong);
                        AutoPtrArray(_T _array[]);
                       ~AutoPtrArray();
#endif

     // operators
#ifdef __VISUAL_STUDIO__
     AutoPtrArray<_T>&  operator = (_T _other[])  throw();
    _T&                 operator [] (int)         throw();
#else
     AutoPtrArray<_T>&  operator = (_T _other[]);
    _T&                 operator [] (int);
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
// AutoPtr helpers
// ------- -------
typedef AutoPtr<char*>   ap_char;
typedef AutoPtr<tchar*>  ap_tchar;
typedef AutoPtr<int8*>   ap_int8;
typedef AutoPtr<uint8*>  ap_uint8;
typedef AutoPtr<int16*>  ap_int16;
typedef AutoPtr<uint16*> ap_uint16;
typedef AutoPtr<int32*>  ap_int32;
typedef AutoPtr<uint32*> ap_uint32;
typedef AutoPtr<int64*>  ap_int64;
typedef AutoPtr<uint64*> ap_uint64;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __AUTOPTR_H__

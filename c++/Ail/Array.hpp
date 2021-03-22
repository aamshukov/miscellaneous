////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ARRAY_H__
#define __ARRAY_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Array
// ----- -----
template <typename _T, typename _Mutex = Synchronization::ThreadMutex<>, typename _Allocator = StandardAllocator> class Array : protected StateObject
{
    typedef StateObject::EState           _State;
    typedef Array<_T, _Mutex, _Allocator> _Array;

    private:

    enum EConst
    {
        ConstLowerBound = 0,
        ConstCount      = 32,
        ConstDelta      = 16
    };

    public:

    enum EFlags
    {
        None       = 0x0000,
        Sorted     = 0x0001,
        Init       = 0x0002,   // it is possible to zero out
        AutoResize = 0x0004,   // for operator []
        Native     = 0x0008    // for char, int, long
    };

    private:
     void               Initialize(uint, ushort, int, ushort);
     void               AssertRange(int)                        const;
     ushort             GetNextDelta(uint, uint = ConstDelta)   const;
     uint               ZeroBase(int)                           const;
     void               SetZero(uint, uint);
    protected:
     ushort             Flags;
     int                LowerBound;
     uint               Count;
     ushort             Delta;
    _T*                 Data;
    _Mutex              Mutex;
    public:
     // ctor/dtor
                        Array(uint = ConstCount, ushort = ConstDelta, int = ConstLowerBound, ushort = Array::Init, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
                        Array(const _Array&, const tchar* = null, uint = Synchronization::TimeoutNoLimit);
     virtual           ~Array();

     // operators
     const _Array&      operator = (const _Array&);

    _T&                 operator [] (int);
    _T&                 operator [] (int)                       const;

     // access
     bool               IsSorted()                              const;
     bool               IsInit()                                const;
     bool               IsAutoResize()                          const;

     bool               IsEmpty()                               const;

     bool               IsShouldDelete()                        const;
    _State              SetState(_State = StateObject::eDelete);

     ushort             GetFlags()                              const;
     void               SetFlags(ushort, ushort);

     int                GetLowerBound()                         const;

     uint               GetCount()                              const;

     ushort             GetDelta()                              const;
     void               SetDelta(ushort);
     
     const _T*          GetData()                               const;
           _T*          GetData();
     void               SetData(_T*, uint);

     // protocol
     bool               HasEntry(const _T&)                     const;
     int                FindEntry(const _T&)                    const;

     void               GetEntry(int, _T&)                      const;
     void               SetEntry(int, const _T&);

     void               AddEntry(const _T&);

     void               RemoveEntry(int);
     void               RemoveAllEntries();

     void               Insert(const _Array&, int);
     void               Insert(const _T&, int, int);

     void               Swap(_Array&)                           throw();
     void               Resize(uint);

     void               Destroy();
};

template <typename _T, typename _Mutex, typename _Allocator> bool operator == (const Array<_T, _Mutex, _Allocator>&, const Array<_T, _Mutex, _Allocator>&);
////////////////////////////////////////////////////////////////////////////////////////
// class XArray
// ----- ------
class __DECLSPEC__ XArray : public X
{
    public:

    enum EFlag
    {
        Failure    = 0x0001,
        OutOfRange = 0x0002,
        FixedSize  = 0x0004
    };

    public:
        XArray(uint = XArray::Failure);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __ARRAY_H__

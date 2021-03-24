////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MODULEPROC_INL__
#define __MODULEPROC_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV0
// ----- ------------
template <typename T> ModuleProcV0<T>::ModuleProcV0(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename T> void ModuleProcV0<T>::operator () ()
{
    typedef void (__AIL_STDCALL__* _Procedure) ();
    ((_Procedure)Procedure)();
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc0
// ----- -----------
template <typename R> ModuleProc0<R>::ModuleProc0(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R> R ModuleProc0<R>::operator () ()
{
    typedef R (__AIL_STDCALL__* _Procedure) ();
    return ((_Procedure)Procedure)();
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV1
// ----- ------------
template <typename P1> ModuleProcV1<P1>::ModuleProcV1(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1> void ModuleProcV1<P1>::operator () (P1 _p1)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1);
    ((_Procedure)Procedure)(_p1);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc1
// ----- -----------
template <typename R, typename P1> ModuleProc1<R, P1>::ModuleProc1(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1> R ModuleProc1<R, P1>::operator () (P1 _p1)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1);
    return ((_Procedure)Procedure)(_p1);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV2
// ----- ------------
template <typename P1, typename P2> ModuleProcV2<P1, P2>::ModuleProcV2(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2> void ModuleProcV2<P1, P2>::operator () (P1 _p1, P2 _a2)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _a2);
    ((_Procedure)Proc)(_p1, _a2);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc2
// ----- -----------
template <typename R, typename P1, typename P2> ModuleProc2<R, P1, P2>::ModuleProc2(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2> R ModuleProc2<R, P1, P2>::operator () (P1 _p1, P2 _p2)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2);
    return ((_Procedure)Procedure)(_p1, _p2);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV3
// ----- ------------
template <typename P1, typename P2, typename P3> ModuleProcV3<P1, P2, P3>::ModuleProcV3(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3> void ModuleProcV3<P1, P2, P3>::operator () (P1 _p1, P2 _p2, P3 _p3)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3);
    ((_Procedure)Procedure)(_p1, _p2, _p3);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc3
// ----- -----------
template <typename R, typename P1, typename P2, typename P3> ModuleProc3<R, P1, P2, P3>::ModuleProc3(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3> R ModuleProc3<R, P1, P2, P3>::operator () (P1 _p1, P2 _p2, P3 _p3)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3);
    return ((_Procedure)Procedure)(_p1, _p2, _p3);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV4
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4> ModuleProcV4<P1, P2, P3, P4>::ModuleProcV4(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4> void ModuleProcV4<P1, P2, P3, P4>::operator () (P1 , P2 _p2, P3 _p3, P4 _p4)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc4
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4> ModuleProc4<R, P1, P2, P3, P4>::ModuleProc4(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4> R ModuleProc4<R, P1, P2, P3, P4>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV5
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5> ModuleProcV5<P1, P2, P3, P4, P5>::ModuleProcV5(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5> void ModuleProcV5<P1, P2, P3, P4, P5>::operator () (P1 , P2 _p2, P3 _p3, P4 _p4, P5 _p5)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc5
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> ModuleProc5<R, P1, P2, P3, P4, P5>::ModuleProc5(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> R ModuleProc5<R, P1, P2, P3, P4, P5>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV6
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> ModuleProcV6<P1, P2, P3, P4, P5, P6>::ModuleProcV6(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> void ModuleProcV6<P1, P2, P3, P4, P5, P6>::operator () (P1 , P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc6
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> ModuleProc6<R, P1, P2, P3, P4, P5, P6>::ModuleProc6(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> R ModuleProc6<R, P1, P2, P3, P4, P5, P6>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV7
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> ModuleProcV7<P1, P2, P3, P4, P5, P6, P7>::ModuleProcV7(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> void ModuleProcV7<P1, P2, P3, P4, P5, P6, P7>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc7
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> ModuleProc7<R, P1, P2, P3, P4, P5, P6, P7>::ModuleProc7(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> R ModuleProc7<R, P1, P2, P3, P4, P5, P6, P7>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV8
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> ModuleProcV8<P1, P2, P3, P4, P5, P6, P7, P8>::ModuleProcV8(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> void ModuleProcV8<P1, P2, P3, P4, P5, P6, P7, P8>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc8
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> ModuleProc8<R, P1, P2, P3, P4, P5, P6, P7, P8>::ModuleProc8(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> R ModuleProc8<R, P1, P2, P3, P4, P5, P6, P7, P8>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV9
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> ModuleProcV9<P1, P2, P3, P4, P5, P6, P7, P8, P9>::ModuleProcV9(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> void ModuleProcV9<P1, P2, P3, P4, P5, P6, P7, P8, P9>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc9
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> ModuleProc9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>::ModuleProc9(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> R ModuleProc9<R, P1, P2, P3, P4, P5, P6, P7, P8, P9>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV10
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> ModuleProcV10<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>::ModuleProcV10(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> void ModuleProcV10<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc10
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> ModuleProc10<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>::ModuleProc10(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> R ModuleProc10<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV11
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11> ModuleProcV11<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11>::ModuleProcV11(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11> void ModuleProcV11<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc11
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11> ModuleProc11<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11>::ModuleProc11(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11> R ModuleProc11<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV12
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12> ModuleProcV12<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12>::ModuleProcV12(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12> void ModuleProcV12<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc12
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12> ModuleProc12<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12>::ModuleProc12(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12> R ModuleProc12<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV13
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13> ModuleProcV13<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13>::ModuleProcV13(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13> void ModuleProcV13<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc13
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13> ModuleProc13<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13>::ModuleProc13(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13> R ModuleProc13<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV14
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14> ModuleProcV14<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14>::ModuleProcV14(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14> void ModuleProcV14<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc14
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14> ModuleProc14<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14>::ModuleProc14(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14> R ModuleProc14<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV15
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15> ModuleProcV15<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15>::ModuleProcV15(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15> void ModuleProcV15<P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14, P15 _p15)
{
    typedef void (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14, P15 _p15);
    ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14, _p15);
}
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc15
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15> ModuleProc15<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15>::ModuleProc15(const Module& _module, const char* _proc) : ModuleProc(_module, _proc)
{
}

template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15> R ModuleProc15<R, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15>::operator () (P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14, P15 _p15)
{
    typedef R (__AIL_STDCALL__* _Procedure)(P1 _p1, P2 _p2, P3 _p3, P4 _p4, P5 _p5, P6 _p6, P7 _p7, P8 _p8, P9 _p9, P10 _p10, P11 _p11, P12 _p12, P13 _p13, P14 _p14, P15 _p15);
    return ((_Procedure)Procedure)(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10, _p11, _p12, _p13, _p14, _p15);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MODULEPROC_INL__

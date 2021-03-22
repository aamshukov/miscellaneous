////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __MODULEPROC_H__
#define __MODULEPROC_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc
// ----- ----------
class __DECLSPEC__ ModuleProc
{
    protected:
#ifdef __MS_WINDOWS__
     FARPROC    Procedure;
#else
     uint32     Procedure;
#endif
    public:
                ModuleProc(const Module&, const char*);
     virtual   ~ModuleProc();
    public:
#ifdef __MS_WINDOWS__
    class XModuleProc : public X
    {
        public:
           XModuleProc(uint = X::Failure);
    };

    friend class XModuleProc;
#endif
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV0
// ----- ------------
template <typename T = int> class ModuleProcV0 : public ModuleProc
{
    public:
            ModuleProcV0(const Module&, const char*);

     void   operator () ();
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc0
// ----- -----------
template <typename R> class ModuleProc0 : public ModuleProc
{
    public:
            ModuleProc0(const Module&, const char*);

     R      operator () ();
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV1
// ----- ------------
template <typename P1> class ModuleProcV1 : public ModuleProc
{
    public:
            ModuleProcV1(const Module& module, const char*);

     void   operator () (P1);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc1
// ----- -----------
template <typename R, typename P1> class ModuleProc1 : public ModuleProc
{
    public:
            ModuleProc1(const Module&, const char*);

     R      operator () (P1);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV2
// ----- ------------
template <typename P1, typename P2> class ModuleProcV2 : public ModuleProc
{
    public:
            ModuleProcV2(const Module&, const char*);

     void   operator () (P1, P2);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc2
// ----- -----------
template <typename R, typename P1, typename P2> class ModuleProc2 : public ModuleProc
{
    public:
            ModuleProc2(const Module&, const char*);

     R      operator () (P1, P2);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV3
// ----- ------------
template <typename P1, typename P2, typename P3> class ModuleProcV3 : public ModuleProc
{
    public:
            ModuleProcV3(const Module&, const char*);

     void   operator () (P1, P2, P3);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc3
// ----- -----------
template <typename R, typename P1, typename P2, typename P3> class ModuleProc3 : public ModuleProc
{
    public:
            ModuleProc3(const Module&, const char*);

     R      operator () (P1, P2, P3);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV4
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4> class ModuleProcV4 : public ModuleProc
{
    public:
            ModuleProcV4(const Module&, const char*);

     void   operator () (P1, P2, P3, P4);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc4
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4> class ModuleProc4 : public ModuleProc
{
    public:
            ModuleProc4(const Module&, const char*);

     R      operator () (P1, P2, P3, P4);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV5
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5> class ModuleProcV5 : public ModuleProc
{
    public:
            ModuleProcV5(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc5
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5> class ModuleProc5 : public ModuleProc
{
    public:
            ModuleProc5(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV6
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> class ModuleProcV6 : public ModuleProc
{
    public:
            ModuleProcV6(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc6
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6> class ModuleProc6 : public ModuleProc
{
    public:
            ModuleProc6(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV7
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> class ModuleProcV7 : public ModuleProc
{
    public:
            ModuleProcV7(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc7
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7> class ModuleProc7 : public ModuleProc
{
    public:
            ModuleProc7(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV8
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> class ModuleProcV8 : public ModuleProc
{
    public:
            ModuleProcV8(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc8
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8> class ModuleProc8 : public ModuleProc
{
    public:
            ModuleProc8(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV9
// ----- ------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> class ModuleProcV9 : public ModuleProc
{
    public:
            ModuleProcV9(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc9
// ----- -----------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9> class ModuleProc9 : public ModuleProc
{
    public:
            ModuleProc9(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV10
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> class ModuleProcV10 : public ModuleProc
{
    public:
            ModuleProcV10(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc10
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10> class ModuleProc10 : public ModuleProc
{
    public:
            ModuleProc10(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV11
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11> class ModuleProcV11 : public ModuleProc
{
    public:
            ModuleProcV11(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc11
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11> class ModuleProc11 : public ModuleProc
{
    public:
            ModuleProc11(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV12
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12> class ModuleProcV12 : public ModuleProc
{
    public:
            ModuleProcV12(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc12
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12> class ModuleProc12 : public ModuleProc
{
    public:
            ModuleProc12(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV13
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13> class ModuleProcV13 : public ModuleProc
{
    public:
            ModuleProcV13(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc13
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13> class ModuleProc13 : public ModuleProc
{
    public:
            ModuleProc13(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV14
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14> class ModuleProcV14 : public ModuleProc
{
    public:
            ModuleProcV14(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc14
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14> class ModuleProc14 : public ModuleProc
{
    public:
            ModuleProc14(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProcV15
// ----- -------------
template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15> class ModuleProcV15 : public ModuleProc
{
    public:
            ModuleProcV15(const Module&, const char*);

     void   operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15);
};
////////////////////////////////////////////////////////////////////////////////////////
// class ModuleProc15
// ----- ------------
template <typename R, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15> class ModuleProc15 : public ModuleProc
{
    public:
            ModuleProc15(const Module&, const char*);

     R      operator () (P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13, P14, P15);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __MODULEPROC_H__

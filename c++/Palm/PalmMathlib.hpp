////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_MATHLIB_H__
#define __PALM_MATHLIB_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmMathlib
// ----- -----------
class __DECLSPEC__ PalmMathlib : public PalmModule
{
    protected:
     virtual Err    Open();
     virtual Err    Close();
    public:
     // ctor/dtor
                    PalmMathlib(bool = true);
     virtual       ~PalmMathlib();

     // access
     static PalmModule&
                    GetMathlibModule();

     // api
     static Err     ACos(double, double&);
     static Err     ASin(double, double&);
     static Err     ATan(double, double&);
     static Err     ATan2(double, double, double&);
     static Err     Cos(double, double&);
     static Err     Sin(double, double&);
     static Err     Tan(double, double&);
     static Err     SinCos(double, double&, double&);
     static Err     CosH(double, double&);
     static Err     SinH(double, double&);
     static Err     TanH(double, double&);
     static Err     ACosH(double, double&);
     static Err     ASinH(double, double&);
     static Err     ATanH(double, double&);
     static Err     Exp(double, double&);
     static Err     FrExp(double, double&, int16&);
     static Err     LdExp(double, int16, double&);
     static Err     Log(double, double&);
     static Err     Log10(double, double&);
     static Err     ModF(double, double&, double&);
     static Err     ExpM1(double, double&);
     static Err     Log1P(double, double&);
     static Err     LogB(double, double&);
     static Err     Log2(double, double&);
     static Err     Pow(double, double, double&);
     static Err     Sqrt(double, double&);
     static Err     Hypot(double, double, double&);
     static Err     Cbrt(double, double&);
     static Err     Ceil(double, double&);
     static Err     FAbs(double, double&);
     static Err     Floor(double, double&);
     static Err     FMod(double, double, double&);
     static Err     IsInf(double, int16&);
     static Err     Finite(double, int16&);
     static Err     ScalBN(double, int16, double&);
     static Err     DRem(double, double, double&);
     static Err     Significand(double, double&);
     static Err     CopySign(double, double, double&);
     static Err     IsNaN(double, int16&);
     static Err     ILogB(double, int16&);
     static Err     RInt(double, double&);
     static Err     NextAfter(double, double, double&);
     static Err     Remainder(double, double, double&);
     static Err     ScalB(double, double, double&);
     static Err     Round(double, double&);
     static Err     Trunc(double, double&);
     static Err     SignBit(double, uint32&);

    public:

    class __DECLSPEC__ XPalmMathlib : public XPalmModule
    {
        public:

        enum EErrors
        {
            // appErrorClass+'math'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmMathlib;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_MATHLIB_H__

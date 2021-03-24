////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_MATHLIB_INL__
#define __PALM_MATHLIB_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmMathlib
// ----- -----------
__INLINE__ Err PalmMathlib::ACos(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibACos(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ASin(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibASin(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ATan(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibATan(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ATan2(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibATan2(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::Cos(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibCos(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Sin(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibSin(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Tan(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibTan(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::SinCos(double _x, double& _sinx, double& _siny)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibSinCos(HMODULE(GetMathlibModule()), _x, &_sinx, &_siny);
}

__INLINE__ Err PalmMathlib::CosH(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibCosH(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::SinH(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibSinH(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::TanH(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibTanH(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ACosH(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibACosH(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ASinH(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibASinH(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ATanH(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibATanH(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Exp(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibExp(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::FrExp(double _x, double& _fraction, int16& _exp)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibFrExp(HMODULE(GetMathlibModule()), _x, &_fraction, &_exp);
}

__INLINE__ Err PalmMathlib::LdExp(double _x, int16 _exp, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibLdExp(HMODULE(GetMathlibModule()), _x, _exp, &_result);
}

__INLINE__ Err PalmMathlib::Log(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibLog(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Log10(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibLog10(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ModF(double _x, double& _int_part, double& _frac_part)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibModF(HMODULE(GetMathlibModule()), _x, &_int_part, &_frac_part);
}

__INLINE__ Err PalmMathlib::ExpM1(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibExpM1(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Log1P(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibLog1P(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::LogB(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibLogB(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Log2(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibLog2(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Pow(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibPow(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::Sqrt(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibSqrt(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Hypot(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibHypot(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::Cbrt(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibCbrt(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Ceil(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibCeil(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::FAbs(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibFAbs(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Floor(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibFloor(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::FMod(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibFMod(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::IsInf(double _x, int16& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibIsInf(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Finite(double _x, int16& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibFinite(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ScalBN(double _x, int16 _exp, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibScalBN(HMODULE(GetMathlibModule()), _x, _exp, &_result);
}

__INLINE__ Err PalmMathlib::DRem(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibDRem(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::Significand(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibSignificand(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::CopySign(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibCopySign(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::IsNaN(double _x, int16& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibIsNaN(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::ILogB(double _x, int16& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibILogB(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::RInt(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibRInt(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::NextAfter(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibNextAfter(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::Remainder(double _x, double _y, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibRemainder(HMODULE(GetMathlibModule()), _x, _y, &_result);
}

__INLINE__ Err PalmMathlib::ScalB(double _x, double _exp, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibScalB(HMODULE(GetMathlibModule()), _x, _exp, &_result);
}

__INLINE__ Err PalmMathlib::Round(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibRound(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::Trunc(double _x, double& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibTrunc(HMODULE(GetMathlibModule()), _x, &_result);
}

__INLINE__ Err PalmMathlib::SignBit(double _x, uint32& _result)
{
    palmxassert(PalmMathlib::GetMathlibModule().IsValid(), PalmModule::XPalmModule::eLibNotFound, PalmMathlib::XPalmMathlib);
    return ::MathLibSignBit(HMODULE(GetMathlibModule()), _x, &_result);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_MATHLIB_INL__

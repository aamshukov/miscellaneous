////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_DIALOG_INL__
#define __PALM_DIALOG_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmDialog
// ----- ----------
__INLINE__ PalmDialog::operator FormType* ()
{
    return static_cast<FormType*>(Form);
}

__INLINE__ PalmDialog::operator const FormType* () const
{
    return const_cast<const FormType*>(Form);
}

__INLINE__ bool PalmDialog::IsValid() const
{
    return Form != null;
}

__INLINE__ void PalmDialog::Attach()
{
    Form = ::FrmGetActiveForm();
}

__INLINE__ void PalmDialog::Detach()
{
    Form = null;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_DIALOG_INL__

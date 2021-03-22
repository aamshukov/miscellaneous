////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FORM_INL__
#define __PALM_FORM_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmForm
// ----- --------
__INLINE__ PalmForm::operator FormType* ()
{
    return static_cast<FormType*>(Form);
}

__INLINE__ PalmForm::operator const FormType* () const
{
    return const_cast<const FormType*>(Form);
}

__INLINE__ bool PalmForm::IsValid() const
{
    return Form != null;
}

__INLINE__ void PalmForm::Attach()
{
    Form = ::FrmGetActiveForm();
}

__INLINE__ void PalmForm::Detach()
{
    Form = null;
}

__INLINE__ void PalmForm::InitForm(uint16 _id)
{
    Form = ::FrmInitForm(_id);
}

__INLINE__ void PalmForm::DestroyForm()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmDeleteForm(Form), Form = null;
}

__INLINE__ void PalmForm::DrawForm()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmDrawForm(Form);
}

__INLINE__ void PalmForm::EraseForm()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmEraseForm(Form);
}

__INLINE__ FormType* PalmForm::GetActiveForm()
{
    return ::FrmGetActiveForm();
}

__INLINE__ void PalmForm::SetActiveForm(FormType* _form)
{
    palmxassert(_form != null, Error::eInvalidArg, PalmForm::XPalmForm);
  ::FrmSetActiveForm(_form);
}

__INLINE__ void PalmForm::SetActiveForm()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetActiveForm(Form);
}

__INLINE__ uint16 PalmForm::GetFormId()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetFormId(Form);
}

__INLINE__ uint16 PalmForm::GetActiveFormID()
{
    return ::FrmGetActiveFormID();
}

__INLINE__ FormType* PalmForm::GetFormPtr(uint16 _id)
{
    return ::FrmGetFormPtr(_id);
}

__INLINE__ FormType* PalmForm::GetFirstForm()
{
    return ::FrmGetFirstForm();
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ FieldType* PalmForm::GetActiveField()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetActiveField(Form);
}
#endif

__INLINE__ bool PalmForm::GetUserModifiedState()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetUserModifiedState(Form);
}

__INLINE__ void PalmForm::SetNotUserModified()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmSetNotUserModified(Form);
}

__INLINE__ uint16 PalmForm::GetFocus()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetFocus(Form);
}

__INLINE__ void PalmForm::SetFocus(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetFocus(Form, _id);
}

__INLINE__ void PalmForm::GetFormBounds(Rect& _r)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmGetFormBounds(Form, &_r);
}

__INLINE__ WinHandle PalmForm::GetWindowHandle()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetWindowHandle(Form);
}

__INLINE__ uint16 PalmForm::GetNumberOfObjects()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetNumberOfObjects(Form);
}

__INLINE__ uint16 PalmForm::GetObjectIndex(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetObjectIndex(Form, _id);
}

__INLINE__ uint16 PalmForm::GetObjectId(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetObjectId(Form, _id);
}

#if (__PALM_OS__ >= 0x0400)
__INLINE__ uint16 PalmForm::GetObjectIndexFromPtr(void* _p)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    palmxassert(_p != null, Error::eInvalidArg, PalmForm::XPalmForm);
    return ::FrmGetObjectIndexFromPtr(Form, _p);
}
#endif

__INLINE__ FormObjectKind PalmForm::GetObjectType(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetObjectType(Form, _id);
}

__INLINE__ void* PalmForm::GetObjectPtr(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetObjectPtr(Form, _id);
}

__INLINE__ void PalmForm::GetObjectBounds(uint16 _id, Rect& _r)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmGetObjectBounds(Form, _id, &_r);
}

__INLINE__ void PalmForm::SetObjectBounds(uint16 _id, const Rect& _r)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetObjectBounds(Form, _id, _r);
}

__INLINE__ void PalmForm::HideObject(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmHideObject(Form, _id);
}

__INLINE__ void PalmForm::ShowObject(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmShowObject(Form, _id);
}

__INLINE__ void PalmForm::GetObjectPosition(uint16 _id, Coord& _x, Coord& _y)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmGetObjectPosition(Form, _id, &_x, &_y);
}

__INLINE__ void PalmForm::GetObjectPosition(uint16 _id, Point& _pt)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmGetObjectPosition(Form, _id, &_pt.x, &_pt.y);
}

__INLINE__ void PalmForm::SetObjectPosition(uint16 _id, Coord _x, Coord _y)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetObjectPosition(Form, _id, _x, _y);
}

__INLINE__ void PalmForm::SetObjectPosition(uint16 _id, const Point& _pt)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetObjectPosition(Form, _id, _pt.x, _pt.y);
}

__INLINE__ int16 PalmForm::GetControlValue(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetControlValue(Form, _id);
}

__INLINE__ void PalmForm::SetControlValue(uint16 _id, int16 _value)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetControlValue(Form, _id, _value);
}

__INLINE__ uint16 PalmForm::GetControlGroupSelection(uint8 _group_number)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetControlGroupSelection(Form, _group_number);
}

__INLINE__ void PalmForm::SetControlGroupSelection(uint8 _group_number, uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetControlGroupSelection(Form, _group_number, _id);
}

__INLINE__ void PalmForm::CopyLabel(uint16 _id, const char* _label)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    palmxassert(_label != null, Error::eInvalidArg, PalmForm::XPalmForm);
  ::FrmCopyLabel(Form, _id, _label);
}

__INLINE__ const char* PalmForm::GetLabel(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetLabel(Form, _id);
}

__INLINE__ void PalmForm::SetCategoryLabel(uint16 _id, char* _label)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetCategoryLabel(Form, _id, _label);
}

__INLINE__ const char* PalmForm::GetTitle()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetTitle(Form);
}

__INLINE__ void PalmForm::SetTitle(char* _title)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    palmxassert(_title != null, Error::eInvalidArg, PalmForm::XPalmForm);
  ::FrmSetTitle(Form, _title);
}

__INLINE__ void PalmForm::CopyTitle(const char* _title)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmCopyTitle(Form, _title);
}

__INLINE__ void* PalmForm::GetGadgetData(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmGetGadgetData(Form, _id);
}

__INLINE__ void PalmForm::SetGadgetData(uint16 _id, const void* _data)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    palmxassert(_data != null, Error::eInvalidArg, PalmForm::XPalmForm);
  ::FrmSetGadgetData(Form, _id, _data);
}

__INLINE__ void PalmForm::SetGadgetHandler(uint16 _id, FormGadgetHandlerType* _handler)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    palmxassert(_handler != null, Error::eInvalidArg, PalmForm::XPalmForm);
  ::FrmSetGadgetHandler(Form, _id, _handler);
}

__INLINE__ uint16 PalmForm::DoDialog()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmDoDialog(Form);
}

__INLINE__ uint16 PalmForm::Alert(uint16 _id)
{
    return ::FrmAlert(_id);
}

__INLINE__ uint16 PalmForm::CustomAlert(uint16 _id, const char* _s1, const char* _s2, const char* _s3)
{
    return ::FrmCustomAlert(_id, _s1 != null ? _s1 : PalmOS::StringStub,
                                 _s2 != null ? _s2 : PalmOS::StringStub,
                                 _s3 != null ? _s3 : PalmOS::StringStub);
}

__INLINE__ uint16 PalmForm::CustomResponseAlert(uint16 _id, const char* _s1, const char* _s2, const char* _s3, char* _buffer, int16 _count, FormCheckResponseFuncType* _handler)
{
    palmxassert(_buffer != null, Error::eInvalidArg, PalmForm::XPalmForm);
    palmxassert(_handler != null, Error::eInvalidArg, PalmForm::XPalmForm);
    return ::FrmCustomResponseAlert(_id, _s1 != null ? _s1 : PalmOS::StringStub,
                                         _s2 != null ? _s2 : PalmOS::StringStub,
                                         _s3 != null ? _s3 : PalmOS::StringStub,
                                         _buffer, _count, _handler);
}

__INLINE__ void PalmForm::PopupForm(uint16 _id)
{
  ::FrmPopupForm(_id);
}

__INLINE__ void PalmForm::GotoForm(uint16 _id)
{
  ::FrmGotoForm(_id);
}

__INLINE__ void PalmForm::Help(uint16 _id)
{
  ::FrmHelp(_id);
}

__INLINE__ void PalmForm::UpdateScrollers(uint16 _up, uint16 _down, bool _is_up, bool _is_down)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmUpdateScrollers(Form, _up, _down, _is_up, _is_down);
}

__INLINE__ bool PalmForm::IsVisible()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmVisible(Form);
}

__INLINE__ void PalmForm::UpdateForm(uint16 _id, uint16 _code)
{
  ::FrmUpdateForm(_id, _code);
}

__INLINE__ void PalmForm::ReturnToForm(uint16 _id)
{
  ::FrmReturnToForm(_id);
}

__INLINE__ void PalmForm::CloseAllForms()
{
  ::FrmCloseAllForms();
}

__INLINE__ void PalmForm::SaveAllForms()
{
  ::FrmSaveAllForms();
}

__INLINE__ bool PalmForm::PointInTitle(Coord _x, Coord _y)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmPointInTitle(Form, _x, _y);
}

__INLINE__ bool PalmForm::PointInTitle(const Point& _pt)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmPointInTitle(Form, _pt.x, _pt.y);
}

__INLINE__ void PalmForm::SetMenu(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
  ::FrmSetMenu(Form, _id);
}

__INLINE__ bool PalmForm::ValidatePtr()
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmValidatePtr(Form);
}

__INLINE__ Err PalmForm::AddSpaceForObject(MemPtr* _object, FormObjectKind _type, uint16 _size)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    palmxassert(_object != null, Error::eInvalidArg, PalmForm::XPalmForm);
    return ::FrmAddSpaceForObject(&Form, _object, _type, _size);
}

__INLINE__ Err PalmForm::RemoveObject(uint16 _id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmRemoveObject(&Form, _id);
}

__INLINE__ FormType* PalmForm::NewForm(uint16 _id, const char* _title,
                                       Coord _x, Coord _y,
                                       Coord _w, Coord _h,
                                       bool _modal, uint16 _def_button,
                                       uint16 _res_id, uint16 _menu_id)
{
    return ::FrmNewForm(_id, _title, _x, _y, _w, _h, _modal, _def_button, _res_id, _menu_id);
}

__INLINE__ FormType* PalmForm::NewForm(uint16 _id, const char* _title,
                                       const Point& _pt, const Size& _sz,
                                       bool _modal, uint16 _def_button,
                                       uint16 _res_id, uint16 _menu_id)
{
    return ::FrmNewForm(_id, _title, _pt.x, _pt.y, _sz.cx, _sz.cy, _modal, _def_button, _res_id, _menu_id);
}

__INLINE__ FormLabelType* PalmForm::NewLabel(uint16 _id, const char* _label, Coord _x, Coord _y, FontID _font_id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewLabel(&Form, _id, _label, _x, _y, _font_id);
}

__INLINE__ FormLabelType* PalmForm::NewLabel(uint16 _id, const char* _label, const Point& _pt, FontID _font_id)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewLabel(&Form, _id, _label, _pt.x, _pt.y, _font_id);
}

__INLINE__ FormBitmapType* PalmForm::NewBitmap(uint16 _id, uint16 _res_id, Coord _x, Coord _y)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewBitmap(&Form, _id, _res_id, _x, _y);
}

__INLINE__ FormBitmapType* PalmForm::NewBitmap(uint16 _id, uint16 _res_id, const Point& _pt)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewBitmap(&Form, _id, _res_id, _pt.x, _pt.y);
}

__INLINE__ FormGadgetType* PalmForm::NewGadget(uint16 _id, Coord _x, Coord _y, Coord _w, Coord _h)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewGadget(&Form, _id, _x, _y, _w, _h);
}

__INLINE__ FormGadgetType* PalmForm::NewGadget(uint16 _id, const Point& _pt, const Size& _sz)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewGadget(&Form, _id, _pt.x, _pt.y, _sz.cx, _sz.cy);
}

__INLINE__ Err PalmForm::ActiveState(FormActiveStateType* _state, bool _save)
{
    return ::FrmActiveState(_state, _save);
}

__INLINE__ FrmGraffitiStateType* PalmForm::NewGsi(Coord _x, Coord _y)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewGsi(&Form, _x, _y);
}

__INLINE__ FrmGraffitiStateType* PalmForm::NewGsi(const Point& _pt)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    return ::FrmNewGsi(&Form, _pt.x, _pt.y);
}

__INLINE__ void PalmForm::SetEventHandler(FormEventHandlerType* _handler)
{
    palmxassert(Form != null, Error::eUninitialized, PalmForm::XPalmForm);
    palmxassert(_handler != null, Error::eInvalidArg, PalmForm::XPalmForm);
  ::FrmSetEventHandler(Form, _handler);
}

__INLINE__ bool PalmForm::DispatchEvent(EventType& _event)
{
    return ::FrmDispatchEvent(&_event);
}

__INLINE__ bool PalmForm::HandleEvent(EventType& _event)
{
    return ::FrmDispatchEvent(&_event);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FORM_INL__

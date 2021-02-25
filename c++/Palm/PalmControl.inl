////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_CONTROL_INL__
#define __PALM_CONTROL_INL__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmControl
// ----- -----------
__INLINE__ bool PalmControl::IsValid() const
{
    return Control != null;
}

__INLINE__ void* PalmControl::GetControl() const
{
    return Control;
}

__INLINE__ void PalmControl::Attach(void* _p)
{
    Control = _p;
}

__INLINE__ void* PalmControl::Detach()
{
    void* p = Control;
    Control = null;
    return p;
}

__INLINE__ void PalmControl::DrawControl()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlDrawControl(static_cast<ControlType*>(Control));
}

__INLINE__ void PalmControl::EraseControl()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlEraseControl(static_cast<ControlType*>(Control));
}

__INLINE__ void PalmControl::HideControl()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlHideControl(static_cast<ControlType*>(Control));
}

__INLINE__ void PalmControl::ShowControl()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlShowControl(static_cast<ControlType*>(Control));
}

__INLINE__ bool PalmControl::Enabled()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
    return ::CtlEnabled(static_cast<ControlType*>(Control));
}

__INLINE__ void PalmControl::SetEnabled(bool _enable_flag)
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlSetEnabled(static_cast<ControlType*>(Control), _enable_flag);
}

__INLINE__ void PalmControl::SetUsable(bool _usable_flag)
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlSetUsable(static_cast<ControlType*>(Control), _usable_flag);
}

__INLINE__ int16 PalmControl::GetValue()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
    return ::CtlGetValue(static_cast<ControlType*>(Control));
}

__INLINE__ void PalmControl::SetValue(int16 _set_value)
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlSetValue(static_cast<ControlType*>(Control), _set_value);
}

__INLINE__ char const * PalmControl::GetLabel()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
    return ::CtlGetLabel(static_cast<ControlType*>(Control));
}

__INLINE__ void PalmControl::SetLabel(char const * _new_label)
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlSetLabel(static_cast<ControlType*>(Control), _new_label);
}

__INLINE__ void PalmControl::SetGraphics(DmResID _new_bitmap_id, DmResID _new_selected_bitmap_id)
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlSetGraphics(static_cast<ControlType*>(Control), _new_bitmap_id, _new_selected_bitmap_id);
}

__INLINE__ void PalmControl::GetSliderValues(uint16& _min_value, uint16& _max_value, uint16& _page_size, uint16& _value)
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlGetSliderValues(static_cast<ControlType*>(Control), &_min_value, &_max_value, &_page_size, &_value);
}

__INLINE__ void PalmControl::SetSliderValues(const uint16& _min_value, const uint16& _max_value, const uint16& _page_size, const uint16& _value)
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlSetSliderValues (static_cast<ControlType*>(Control), &_min_value, &_max_value, &_page_size, &_value);
}

__INLINE__ void PalmControl::HitControl()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
  ::CtlHitControl(static_cast<ControlType*>(Control));
}

__INLINE__ bool PalmControl::ValidatePointer()
{
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
    return ::CtlValidatePointer(static_cast<ControlType*>(Control));
}

__INLINE__ ControlType* PalmControl::NewControl(void** _form, uint16 _id, ControlStyleType _style, const char* _text, Coord _x, Coord _y, Coord _width, Coord _height, FontID _font, uint8 _group, bool _left_anchor)
{
    return ::CtlNewControl(_form, _id, _style, _text, _x, _y, _width, _height, _font, _group, _left_anchor);
}

#if __PALM_OS__ >= 0x0500
__INLINE__ GraphicControlType* PalmControl::NewGraphicControl(void** _form, uint16 _id, ControlStyleType _style, DmResID _bitmap_id, DmResID _selected_bitmap_id, Coord _x, Coord _y, Coord _width, Coord _height, uint8 _group, bool _left_anchor)
{
    return ::CtlNewGraphicControl(_form, _id, _style, _bitmap_id, _selected_bitmap_id, _x, _y, _width, _height, _group, _left_anchor);
}
#else
__INLINE__ GraphicControlType* PalmControl::NewGraphicControl(void** _form, uint16 _id, ControlStyleType _style, DmResID _bitmap_id, DmResID _selected_bitmap_id, Coord _x, Coord _y, Coord _width, Coord _height, FontID _font_id, uint8 _group, bool _left_anchor)
{
    return ::CtlNewGraphicControl(_form, _id, _style, _bitmap_id, _selected_bitmap_id, _x, _y, _width, _height, _font_id, _group, _left_anchor);
}
#endif

__INLINE__ SliderControlType* PalmControl::NewSliderControl(void** _form, uint16 _id, ControlStyleType _style, DmResID _thumb_id, DmResID _background_id, Coord _x, Coord _y, Coord _width, Coord _height, uint16 _max_value, uint16 _min_value, uint16 _page_size, uint16 _value)
{
    return ::CtlNewSliderControl(_form, _id, _style, _thumb_id, _background_id, _x, _y, _width, _height, _min_value, _max_value, _page_size, _value);
}

__INLINE__ bool PalmControl::HandleEvent(EventType& _event)
{
#if __palm_debug_level__ >= 1
    const std::type_info& info = typeid(this);
    palmxassert(PalmText::StrCompare(info.name(), "PalmControl") == 0, Error::eTypeMismatch, PalmControl::XPalmControl);
#endif
    palmxassert(Control != null, Error::eUninitialized, PalmControl::XPalmControl);
    return ::CtlHandleEvent(static_cast<ControlType*>(Control), &_event);
}
////////////////////////////////////////////////////////////////////////////////////////
// class Wrapper
// ----- -------
template <typename _T> PalmControl::Wrapper<_T>::Wrapper(PalmControl& _o, uint16 _id)
                                  : O(_o)
{
    FormType* form = ::FrmGetActiveForm();

    if(form == null)
    {
        return;
    }

    uint16 index = ::FrmGetObjectIndex(form, _id);

    if(index == frmInvalidObjectId)
    {
        return;
    }

   _T* o = static_cast<_T*>(::FrmGetObjectPtr(form, index));

    if(o == null)
    {
        return;
    }
   _o.Attach(o);
}

template <typename _T> PalmControl::Wrapper<_T>::~Wrapper()
{
    O.Detach();
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_CONTROL_INL__

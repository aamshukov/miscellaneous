////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_CONTROL_H__
#define __PALM_CONTROL_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
/**
 * @class PalmControl
 * @brief A class to wrap the Palm OS control interface and base class for the other Palm GUI objects
 *
 * The PalmControl class is a wrapper class over the Palm OS control interface.
 * It provides the control functions after attaching a PalmControl object to
 * a GUI object using the <code>ATTACH_CONTROL()</code> macro.
 *
 * The PalmControl class is a base class for the following classes:
 * <ul><li>PalmField
 * <li>PalmList
 * <li>PalmScroller
 * <li>PalmTable
 * </ul>
 *
 * Attaching to a GUI control is done in order to operate on the specific
 * control. This is done in the context of the method, where the attachment
 * is done. Once out of the specific context, the object is not attached to
 * the GUI control, and ou can not perform any operation on it. In order to
 * attach use the macro: <code>ATTACH_CONTROL()</code>. For example, if the
 * form class (which is derived from the PalmForm class) is:
 *
 * <code><pre>
 * #include <PalmControl.inc>
 * #include <PalmForm.inc>
 *
 * class MainForm : public PalmForm
 * {
 * private:
 *    // A PalmControl object to handle the list
 *    PalmControl PopupTriggerControl;
 *
 * Public:
 *    // Initialization routine
 *    bool Setup();
 * };
 *
 * bool MainForm::Setup()
 * {
 *    // Attach to the popup trigger control
 *    ATTACH_CONTROL( ControlType, PopupTriggerControl, Popup_rsrc_ID )
 *
 *    // Set the popup trigger label to init value
 *    PopupTriggerCOntrol.SetLabel("Select option");
 *
 *    return true;
 * }
 * </pre></code>
 *
 */
////////////////////////////////////////////////////////////////////////////////
// class PalmControl
// ----- -----------
class __DECLSPEC__ PalmControl
{
    public:

    template <typename _T> class Wrapper
    {
        private:
         PalmControl&   O;
        public:
         // ctor/dtor
                        Wrapper(PalmControl&, uint16);
                       ~Wrapper();
    };

    protected:
     mutable void*          Control;
    public:
     // ctor/dtor
                            PalmControl(void* = null);
     virtual               ~PalmControl();

     // access
     bool                   IsValid()       const;
     void*                  GetControl()    const;

     void                   Attach(void*);
     void*                  Detach();

     // api
     void                   DrawControl();
     void                   EraseControl();

     void                   HideControl();
     void                   ShowControl();

     bool                   Enabled();
     void                   SetEnabled(bool);

     void                   SetUsable(bool);

     int16                  GetValue();
     void                   SetValue(int16);

     const char*            GetLabel();
     void                   SetLabel(const char*);

     void                   SetGraphics(DmResID, DmResID);

     void                   GetSliderValues(uint16&, uint16&, uint16&, uint16&);
     void                   SetSliderValues(const uint16&, const uint16&, const uint16&, const uint16&);

     void                   HitControl();

     bool                   ValidatePointer();

     static ControlType*
                            NewControl(void**, uint16, ControlStyleType, const char*, Coord, Coord, Coord, Coord, FontID, uint8, bool);

     static GraphicControlType*
#if __PALM_OS__ >= 0x0500
                            NewGraphicControl(void**, uint16, ControlStyleType, DmResID, DmResID, Coord, Coord, Coord, Coord, uint8, bool);
#else
                            NewGraphicControl(void**, uint16, ControlStyleType, DmResID, DmResID, Coord, Coord, Coord, Coord, FontID, uint8, bool);
#endif

     static SliderControlType*
                            NewSliderControl(void**, uint16, ControlStyleType, DmResID, DmResID, Coord, Coord, Coord, Coord, uint16, uint16, uint16, uint16);

     bool                   HandleEvent(EventType&);

    public:

    class __DECLSPEC__ XPalmControl : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'ctrl'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmControl;
};
////////////////////////////////////////////////////////////////////////////////////////
// syntax:
//  ATTACH_CONTROL(TableType, MyTable, MyTableID)
//
// agil added '_object##'
#define ATTACH_CONTROL(_type, _object, _id) \
    PalmControl::Wrapper<_type> _object##wrapper(_object, _id);
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_CONTROL_H__


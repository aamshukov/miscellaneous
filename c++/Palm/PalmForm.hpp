////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FORM_H__
#define __PALM_FORM_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
/**
 * @class PalmForm
 * @brief A base class for a Palm OS form object
 *
 * The PalmForm is a base class for a form object. A form is a contaniner of GUI
 * objects. It handles events sent by the GUI objects, set their properties.
 * Every Palm OS application contains one or more PalmForm based objects that
 * construct the interface with the user.
 *
 * Example for a PalmForm derived object:
 *
 * <code><pre>
 * //
 * // class UserPrefForm
 * // ----- ------------
 * class MemoPrintForm : public PalmForm
 * {
 *    private:
 *       // A wrapper on a popup trigger control
 *       PalmControl PopupTrigger;
 *       // Contains the display type
 *       PalmList TypeList;
 *
 *    protected:
 *       // The intialization and exit routines
 *       bool Setup();
 *       bool Finalize();
 *
 *       // A decleration of the event handler container
 *       DECLARE_EVENT_MAP()
 *
 *       // Event handler for the ctlSelectEvent events
 *       bool CtlSelectEventHandler(EventType* _event);
 *
 *    public:
 *       // ctor/dtor
 *                MemoPrintForm(uint16 _id) : PalmForm(_id) {}
 *       virtual ~MemoPrintForm() {}
 * };
 * </pre></code>
 *
 * In order to see how to attach event handlers in the form to events, see
 * the PalmEvent class.
 *
 * The PalmControl class describes how to attach objects to the form objects
 * and use them.
 *
 */

////////////////////////////////////////////////////////////////////////////////////////
// class PalmForm
// ----- --------
class __DECLSPEC__ PalmForm : public PalmEventManager
{
    private:
     mutable FormType*  Form;
    protected:
#ifndef DOXYGEN_PARSING
     DECLARE_EVENT_MAP()
#endif

    protected:
     virtual bool       Pretranslate(EventType&);

     /**
      * Inherent that method to place intialization code that makes Palm OS
      * calls.
      * Return ture if the method succeeds.
      */
     virtual bool       Setup();
     /**
      * Inherent that method to place exit code that makes Palm OS calls.
      * Return ture if the method succeeds.
      */
     virtual bool       Finalize();

     /**
      * The default event handler for the open event handler.
      * Calls the Form setup routine. Returns true on a sucessful open.
      */
     bool               EvOpen(EventType&);
     /**
      * The default event handler for the close event handler.
      * Calls the Form Finalize routine. Returns true on a sucessful close.
      */
     bool               EvClose(EventType&);

    public:
     /** Constructor - Don't make any Palm OS calls here. */
                        PalmForm(uint16);
     /** Destructor - Don't make any Palm OS calls here. */
     virtual           ~PalmForm();

     // operators
                        operator FormType* ();
                        operator const FormType* () const;

     /** Reloads the form by sending a close and open event to the form object
      */
     bool               LoadForm();
     /** Reopens the form. */
     bool               PopupForm();

     /** Returns true if the curremt form object is valid */
     bool               IsValid()                   const;
     /** Link the object with the current displayed form */
     void               Attach();
     /** detach the object from the form it is attached to. */
     void               Detach();

     /** attach a gadget with resource ID to the form. Return true on success */
     bool               AttachGadget(uint16);

     /** Load and initialize the form with the specified resource ID */
     void               InitForm(uint16 rscID);
     /** Release all the memory allocated for the form and its attached
      * objects
      */
     void               DestroyForm();

     /**
      * Draw the form and it's frame. Any custom drawing should be done
      * after this method. If the saveBehind is set, than the form saves
      * the display behind it, it is restored when the SraseForm is called.
      */
     void               DrawForm();
     /**
      * Erase the form from the display. If the display was saved by the
      * DrawForm, it is restored.
      */
     void               EraseForm();

     /**
      * Return a pointer to the current open form. Dn't call the method when
      * a popup window is on, since there is no active form.
      */
     static FormType*   GetActiveForm();
     /** Set the active form to the given form. */
     static void        SetActiveForm(FormType*);
     /** Set the active form to the form contained in this object. */
     void               SetActiveForm();

     /** Return the resource ID of that form. */
     uint16             GetFormId();
     /** Return the resource ID for the current active form. */
     static uint16      GetActiveFormID();

     /** Return a pointer to the form with the resource ID, or 0
         if the form is not in memory */
     static FormType*   GetFormPtr(uint16);
     /**
      * Retuen a pointer to the first form in the form list. The list is
      * managed as LIFO stack, so the last window created is the first
      * on the stack.
      */
     static FormType*   GetFirstForm();


     FieldType*         GetActiveField();

     bool               GetUserModifiedState();
     void               SetNotUserModified();

     /**
      * Return a resource ID of the object that has the focus on the form.
      * If no object has the focus return noFocus.
      *
      * You can get the resource ID from the index ID using:
      * GetObjectId().
      *
      * To operate on the resource, you can use the macro:<br>
      * <Code>ATTACH_CONTROL(object_type, object_variable, resource_id)<Code><br>
      * Defined in PalmControl.
      */
     uint16             GetFocus();
     /**
      * Set the focus in the form to the specified object ID in the form.
      * You can get the object ID from the resource ID using:
      * GetObjectIndex().
      */
     void               SetFocus(uint16);

     /** Return the visible bounds of the form, including the frame. */
     void               GetFormBounds(Rect&);

     /**
      * Return the window handle if the form. This is also the form data
      * structure, since the window handle is the first element in the
      * form data structure.
      */
     WinHandle          GetWindowHandle();

     /** Returns the number of objects in the form. */
     uint16             GetNumberOfObjects();

     /**
      * Return the object index in the form, for the given resource ID. Note
      * that bitmaps use a different mechanism, and you need to provide the
      * bitmap resource ID and not the ID of the form bitmap object.
      *
      * The index of the first object is 0.
      */
     uint16             GetObjectIndex(uint16);
     /**
      * Return the object resource ID for a given object index in the form.
      * In case of error returns frmInvalidObjectId.
      */
     uint16             GetObjectId(uint16);

#if (__PALM_OS__ >= 0x0400)
     uint16             GetObjectIndexFromPtr(void*);
#endif

     /** Return the object type for the specified object index. */
     FormObjectKind     GetObjectType(uint16);
     /**
      * Return a pointer to the object data structure, for the specified
      * object index
      */
     void*              GetObjectPtr(uint16);

     /** Return the object bounds for a given object index. */
     void               GetObjectBounds(uint16, Rect&);
     /**
      * Set the position and bounds of an object index. Doesn't update the
      * display.
      */
     void               SetObjectBounds(uint16, const Rect&);

     /**
      * Erase the specified object index and set the usable bit. After this
      * method the object won't respond to user events.
      */
     void               HideObject(uint16);
     /**
      * Reset the usable bit for the specified object index. In case that
      * the form is visible, redraw the object.
      */
     void               ShowObject(uint16);

     /**
      * Return the coordinates of a specified object index in the form.
      *
      * You can also use: <b>GetObjectPosition(uint16, Point&)</b>
      */
     void               GetObjectPosition(uint16, Coord&, Coord&);
     void               GetObjectPosition(uint16, Point&);

     /**
      * Sets the position of the specified object index, relative to the
      * form.
      *
      * You can also use: <b>SetObjectPosition(uint16, const Point&)</b>
      */
     void               SetObjectPosition(uint16, Coord, Coord);
     void               SetObjectPosition(uint16, const Point&);

     /**
      * Return the current value of the specified object index. This
      * function is valid only for sliders, push button and check box
      * control objects.
      *
      * Push button and check box return a value of 0 for off, or 1 for on.
      * Sliders return the current value of the value of the value field.
      */
     int16              GetControlValue(uint16);
     /**
      * Set the current value of the specified object index. Redraw
      * the control. This function is valid only for sliders, push button
      * and check box control objects.
      *
      * Push button and check box accept a value of 0 for off, or 1 for on.
      * For liders give a value between the minimum and maximum.
      */
     void               SetControlValue(uint16, int16);

     uint16             GetControlGroupSelection(uint8);
     void               SetControlGroupSelection(uint8, uint16);

     /**
      * Copies the spcified string to the specified label resource ID,
      * and redraw the display if the item is visible.
      *
      * The size of the string must not exceed the size of the resource
      * label.
      *
      * If the new string is shorter than the current string, the method won't
      * erase the current one, so the tail of the current string is left on
      * the display. To avoid this, first hide the object using:
      * HideObject(), set it's value and then show the object using:
      * ShowObject().
      */
     void               CopyLabel(uint16, const char*);
     /**
      * Return a pointer to the internal string field of the specified
      * label resource ID.
      */
     const char*        GetLabel(uint16);

     void               SetCategoryLabel(uint16, char*);

     /**
      * Return a pointer to the internal string field of the specified
      * label resource ID.
      *
      * In case that the form doesn't have a title or the form ID is wrong
      * return 0.
      */
     const char*        GetTitle();
     /**
      * Set the title of the form to the specified string. Redraw the form, if
      * the form is visible.
      *
      * Note that since the form internal structure points to this string, it
      * should not be a temporary string.
      */
     void               SetTitle(char*);
     /**
      * Copies the specified string to the form title, and redraw the display if
      * the form is visible.
      *
      * The size of the string must not exceed the size of the current title.
      */
     void               CopyTitle(const char*);

     /**
      * Return the value of the data field of the specified gadget object
      * index in the form.
      */
     void*              GetGadgetData(uint16);
     /**
      * Set the value of the the data field of the specified gadget object
      * index in the form.
      */
     void               SetGadgetData(uint16, const void*);
     /** Set the event handler for the specified gadget object index. */
     void               SetGadgetHandler(uint16, FormGadgetHandlerType*);

     /**
      * Display a modal dialog until the user taps a button in the dialog.
      * Returns the resource ID of the button the user tapped.
      */
     uint16             DoDialog();

     /**
      * Display a predefined alert, based on the alert control id.
      * Returns the item number of the button the user selected. A button’s
      * item number is determined by its order in the alert dialog; the first
      * button has the item number 0 (zero).
      */
     static uint16      Alert(uint16);
     /**
      * Display a predefined custom alert, and replaces the predefine
      * strings ^1 ^2 ^3 with the strings provided in the method
      * arguments.
      * Returns the number of the button the user tapped (the first button is
      * zero).
      */
     static uint16      CustomAlert(uint16, const char*, const char*, const char*);
     /**
      * Create a modal dialog with a text field from an alert resource and
      * display it until the user taps a button in the alert dialog.
      * Returns the number of the button the user tapped (the first button is
      * zero).
      */
     static uint16      CustomResponseAlert(uint16, const char*, const char*, const char*, char*, int16, FormCheckResponseFuncType*);

     /**
      * Opens the specified form, without closing the current form.
      * You can call ReturnToForm to close a form opened by PopupForm.
      */
     static void        PopupForm(uint16);
     /** Closes the current form and open the form with the given resource ID */
     static void        GotoForm(uint16);
     /**
      * Display the specified help message until the user taps the Done
      * button in the help dialog..
      */
     static void        Help(uint16);

     /** Visually update (show or hide) the field scroll arrow buttons. */
     void               UpdateScrollers(uint16, uint16, bool, bool);

     /** Returns true if the form is visible; false if it is not visible. */
     bool               IsVisible();

     /**
      * Redraw the form if the default event handler is used. If the
      * the event is handled in a custom event handler, only parts of
      * display can be redrawn.
      */
     static void        UpdateForm(uint16, uint16);
     /**
      * Erase and delete the currently active form and make the specified
      * form the active form.
      */
     static void        ReturnToForm(uint16);

     /** Use this method to cleanly close all open form before exiting the
      * application */
     static void        CloseAllForms();
     /** Send a frmSaveEvent to all open forms. */
     static void        SaveAllForms();

     /**
      * Returns true if the specified coordinate is in the bounds the
      * form’s title.
      */
     bool               PointInTitle(Coord, Coord);
     /**
      * Returns true if the specified coordinate is in the bounds the
      * form’s title.
      */
     bool               PointInTitle(const Point&);
     /** Change a form’s menu bar and make the new menu active. */
     void               SetMenu(uint16);
     /** Returns true if the form pointer is non-NULL pointer. */
     bool               ValidatePtr();

     Err                AddSpaceForObject(MemPtr*, FormObjectKind, uint16);

     /**
      * Remove the object with the specified object index from the form. Returns
      * 0 if no error.
      */
     Err                RemoveObject(uint16);

     /**
      * Use this method to create form dynamically. Return a pointer to the
      * newly created form, or 0 in case of error. The most common cause
      * of error is lack of memory.
      *
      * Other method to create a form:<br>
      * <b>static FormType*   NewForm(uint16, const char*, const Point&,
      * const Size&, bool, uint16, uint16, uint16);</b>
      */
     static FormType*   NewForm(uint16, const char*, Coord, Coord, Coord, Coord, bool, uint16, uint16, uint16);
     static FormType*   NewForm(uint16, const char*, const Point&, const Size&, bool, uint16, uint16, uint16);

     /**
      * Create a new label, and place it on the form. Returns a pointer to
      * the new label, or 0 if the call fails.
      *
      * Other method to create a label:<br>
      * <b>FormLabelType*     NewLabel(uint16, const char*, const Point&,
      *  FontID); </b>
      */
     FormLabelType*     NewLabel(uint16, const char*, Coord, Coord, FontID);
     FormLabelType*     NewLabel(uint16, const char*, const Point&, FontID);

     /**
      * Create a new bitmap on the form. Return a pointer to the newly
      * created object, or 0 in case of error.
      *
      * Other method to create a bitmap:<br>
      * <b>FormBitmapType*    NewBitmap(uint16, uint16, const Point&);</b>
      */
     FormBitmapType*    NewBitmap(uint16, uint16, Coord, Coord);
     FormBitmapType*    NewBitmap(uint16, uint16, const Point&);

     /**
      * Create a new gadget on the form. Return a pointer to the newly
      * created object, or 0 in case of error.
      *
      * Other method to create a gadget:<br>
      * <b>FormGadgetType*    NewGadget(uint16, const Point&, const Size&);</b>
      */
     FormGadgetType*    NewGadget(uint16, Coord, Coord, Coord, Coord);
     FormGadgetType*    NewGadget(uint16, const Point&, const Size&);

     static Err         ActiveState(FormActiveStateType*, bool);

     /**
      * Create a new graffiti state indicator on the form. Return a
      * pointer to the newly created object, or 0 in case of error.
      *
      * Other method to create a GSI:<br>
      * <b>FrmGraffitiStateType* NewGsi(const Point&);</b>
      */
     FrmGraffitiStateType*
                        NewGsi(Coord, Coord);

     FrmGraffitiStateType*
                        NewGsi(const Point&);

     void               SetEventHandler(FormEventHandlerType*);

     static bool        DispatchEvent(EventType&);
     static bool        HandleEvent(EventType&);

    public:

    /**
     * @class XPalmForm
     * @brief Used internally for handling error cases
     */
    class __DECLSPEC__ XPalmForm : public PalmError
    {
        public:

        enum EErrors
        {
            eSetupError = appErrorClass+'form',
            eFinalizeError
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmForm;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FORM_H__

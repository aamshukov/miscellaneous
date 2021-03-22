////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_APP_H__
#define __PALM_APP_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__

/**
 * @class PalmApp
 * @brief A base class for a Palm OS application.
 *
 * PalmApp class is a base class for the application. The application object
 * should inhert from the PalmApp class. In a minimum implementation the
 * application can be just a PalmApp object, though in most cases the setup
 * and the exist routines are implemented.
 *
 * Typical code in the PalmApp derived object constructor is intialization
 * of other forms objects, global objects or resources that are not Palm OS related.
 *
 * A PalmApp derievd object serves as a container for the application forms.
 *
 * In order to link the application to the Palm OS and define the entry point
 * use a set of macros. These macros define the entry point, an event handler
 * and the exit code. A PalmApp object is instantiated in the macros and is
 * used to start the application:
 * - BEGIN_ENTRY_POINT(_app)<br>
 * Macro to use as the entry point to the Palm application.
 * - DEFAULT_C_STUB() or C_STUB(YourHandler)<br>
 * Macro to handle errors when the application is launced.
 * - END_ENTRY_POINT(_app)<br>
 * Macro to end the definition of the program.
 *
 * For example:
 *
 * <code><i><pre>
 * BEGIN_ENTRY_POINT(PalmOsApp)
 *    DEFAULT_C_STUB()
 * END_ENTRY_POINT(PalmOsApp)
 * </pre></i></code>
 *
 * The PalmOsApp class:
 *
 * <code><i><pre>
 * //
 * // class PalmOsApp
 * // ----- ---------
 * class PalmOsApp : public ail::PalmApp
 * {
 *    private:
 *     // Declare the application forms and
 *     // initilize them in the ctor
 *     MSExplorer Explorer;
 *     MSForm     MainForm;
 *    protected:
 *     // Init function to put the initalization code, for
 *     // example - verify the Palm OS HW or the Palm OS version
 *     void       InitInstance();
 *     void       ExitInstance();
 *    public:
 *     // ctor/dtor
 *                PalmOsApp();
 *               ~PalmOsApp();
 * };
 * </pre></i></code>
 *
 * Accessing the launch command can be done using the
 */

////////////////////////////////////////////////////////////////////////////////////////
// class PalmApp
// ----- -------
class __DECLSPEC__ PalmApp
{
    public:

    enum EConst
    {
        eTimeout = 100  // msecs
    };

    enum EErrorCode
    {
        eOk = 0,
        eUnknownCode = appErrorClass|0x0001,
        eInitInstanceCode,
        eExitInstanceCode,
        eResetCode,
        eLaunchCodeCode,
        eNoGlobalVarsCode
    };

    private:
     uint16             LaunchCode;
     uint16             Flags;
     uint32             ExitCode;
     const void*        CommandPBP;
     EventType          CurrEvent;
     volatile int32     Timeout;
    private:
     bool               IsIdleEvent();
     void               Run();
     bool               RetriveEvent();
    protected:
    /**
     * Intialization routine
     *
     * Called when the application is first loaded. This is the place
     * to put the initialization code for the app. This is a good place
     * to verify the version of the Palm OS, or the type of the HW in
     * order to tune the application.<br>
     * This is the place to put Palm OS calls, do not make any Palm OS
     * calls in the constructor.
     *
     * Example for initialization code:
     * <code><i><pre>
     * void PalmOsApp::InitInstance()
     * {
     *    // verify the HW and OS compatibility
     *    if(!Explorer.IsCompatible())
     *    {
     *        NON_FATAL_ERROR("The device is not compatible")
     *        SetExitCode(PalmApp::eInitInstanceCode);
     *        return;
     *    }
     *
     *    // Load the main form
     *    if(!MainForm.LoadForm())
     *    {
     *        SetExitCode(PalmApp::eInitInstanceCode);
     *        return;
     *    }
     * }
     * </pre></i></code>
     */

    virtual void       InitInstance();
    /**
     * Cleanup routine
     *
     * This method is executed before existing the application. Cleanup
     * code that uses Palm OS services should be placed here and not in
     * the destructor.
     */
     virtual void       ExitInstance();

    /**
     * Idle routine
     *
     * This method is executed while no event are processed.
     */
     virtual bool       Idle(int32);

    /**
     * Called before a sys handler, the first opportunity
     * to process an event
     */
     virtual bool       PretranslateI();

    /**
     * Called before a menu handler, the second opportunity
     * to process an event
     */
     virtual bool       PretranslateII();

     /** Called before a form handler, the last opportunity :) */
     virtual bool       AppHandleEvent();
    public:
     /** Constructor - don't make PlamOS calls here */
                        PalmApp();

     /** Destructor - don't make PlamOS calls here */
     virtual           ~PalmApp();

    /**
     * @brief Accessors/Mutators function
     */

     /** Get the application launch code object variable */
     uint16             GetLaunchCode()             const;
     /** Set the application launch code object variable */
     void               SetLaunchCode(uint16);

     /** Get The application launch flags object variable */
     uint16             GetFlags()                  const;
     /** Set The application launch flags object variable */
     void               SetFlags(uint16);

     /** Get the application exit code object variable */
     uint32             GetExitCode()               const;
     /** set the application exit code object variable */
     void               SetExitCode(uint32);

     /** Get a pointer to the lanch command PBP object variable */
     const void*        GetCommandPBP()             const;
     /** Set a pointer to the lanch command PBP object variable */
     void               SetCommandPBP(const void*);

     /**
      * return the current event. In case that the AppHandleEvent is
      * defined, use this method to get the event.
      */
     const EventType&   GetCurrEvent()              const;

    /**
     * Get/Set timeout in msecs
     */
     int32              GetTimeout()                const;
     void               SetTimeout(int32);

     /**Quit the application - Put appStopEvent in the event queue */
     static void        Quit();

     /**
      * @brief The application entry point
      *
      * Derive that method in case that a special processing is need
      * when the application is launched.
      *
      * This method sets the launch flags, calls the Initialize method
      * and start the application. At the end, the ExitInstance method
      * is invoked and the ExitXode is returned.
      */
     uint32             PilotMain(uint16, void*, uint16);

    public:

    /**
     * @class XPalmApp
     * @brief Used internally for handling error cases
     */
    class __DECLSPEC__ XPalmApp : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'appl'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmApp;
};
////////////////////////////////////////////////////////////////////////////////////////
// entry point
// ----- -----

#undef BEGIN_ENTRY_POINT
#undef C_STUB
#undef DEFAULT_C_STUB
#undef END_ENTRY_POINT

extern "C" uint32 PilotMainCStub(uint16, void*, uint16);

#define BEGIN_ENTRY_POINT(_app)                                                             \
extern "C"                                                                                  \
uint32 PilotMain(uint16 _command, void* _command_pbp, uint16 _flags)                        \
{                                                                                           \
    try                                                                                     \
    {                                                                                       \
        if(!(_flags & sysAppLaunchFlagNewGlobals) && !(_flags & sysAppLaunchFlagSubCall))   \
        {                                                                                   \

#define C_STUB(_handler)                                                                    \
            return _handler(_command, _command_pbp, _flags);                                \
        }                                                                                   \

#define DEFAULT_C_STUB()                                                                    \
            return PilotMainCStub(_command, _command_pbp, _flags);                          \
        }                                                                                   \

#define END_ENTRY_POINT(_app)                                                               \
        std::auto_ptr<_app> app(new _app());                                                \
        return app->PilotMain(_command, _command_pbp, _flags);                              \
    }                                                                                       \
    catch(...)                                                                              \
    {                                                                                       \
        NON_FATAL_ERROR("The Application unexpectedly terminated");                         \
        return uint32(-1);                                                                  \
    }                                                                                       \
}                                                                                           \
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_APP_H__

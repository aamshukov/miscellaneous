////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_MODULE_H__
#define __PALM_MODULE_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__

/** 
 * @class PalmModule
 * @brief Implements lazy loading process of a Palm OS module
 */

////////////////////////////////////////////////////////////////////////////////////////
// class PalmModule
// ----- ----------
class __DECLSPEC__ PalmModule
{
    protected:
     bool               Free;
     HMODULE            Handle;
    _string             Name;
     uint32             Type;
     uint32             Creator;
     uint16             Count; // how many instances are loaded
    public:
     virtual Err        Open()  = 0;
     virtual Err        Close() = 0;
    public:

    /** 
     *  Constructor
     */
                        PalmModule(const char*, uint32, uint32 = 'libr', bool = true);

    /** 
     *  Destructor
     */
     virtual           ~PalmModule();

    /** 
     *  Check if a module is loaded
     */
     bool               IsValid()                               const;

    /** 
     *  True if a module must be unloaded
     */
     bool               ShouldFree()                            const;

    /** 
     *  Returns a handle of a module
     */
     HMODULE            GetModule()                             const;

    /** 
     *  Returns name of a module
     */
    _string             GetName()                               const;

    /** 
     *  Returns a vendor dependent library type
     */
     uint32             GetType()                               const;

    /** 
     *  Returns a creator id of a library
     */
     uint32             GetCreator()                            const;

    /** 
     *  @brief Operators
     *  Cast operator
     */
                        operator HMODULE ()                     const;

    /** 
     *  Equality operator
     */
     bool               operator == (const PalmModule&)         const;

    /** 
     *  The pair Load/Unload module must be consistent
     *  Loads a module, which was described in a constructor
     */
     Err                LoadModule();

    /** 
     *  Unloads a module
     */
     Err                UnloadModule();

    public:

    /**
     * @class XPalmApp
     * @brief Used internally for handling error cases
     */
    class __DECLSPEC__ XPalmModule : public PalmError
    {
        public:

        enum EErrors
        {
            eLibNotFound = appErrorClass+'modl'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmModule;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_MODULE_H__

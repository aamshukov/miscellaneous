////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_ERROR_H__
#define __PALM_ERROR_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__

/** 
 * @class PalmError
 * @brief This class is derived from a base class Error
 */
////////////////////////////////////////////////////////////////////////////////////////
// class PalmError
// ----- ---------
class PalmError : public Error
{
    public:

    enum EErrors
    {
        eUnknownCtrl = appErrorClass+'errr',
        eUnknownRes
    };

    protected:
    /** 
     *  Loads error descriptions, should be overwritten
     */
     virtual void   LoadErrorDescriptions();
    public:

    /** 
     *  Default constructor
     */
                    PalmError();

    /** 
     *  Destructor
     */
     virtual       ~PalmError();

    /** 
     *  Displays an error message,
     *  if neither an error nor a message is specified
     */
     void           PromptError(uint32, const char* = null);
};
////////////////////////////////////////////////////////////////////////////////////////
// assert
// ------
#if (__palm_debug_level__ >= 1)
#define ERRDISPLAYFILELINEMSG(_file, _line, _message)                               \
        ErrDisplayFileLineMsg(_file, _line, _message);
#else
#define ERRDISPLAYFILELINEMSG(_file, _line, _message)
#endif

#if (__palm_debug_level__ >= 1)
#define palmxassert(_expr, _error, _class)                                          \
        if(_expr == 0)                                                              \
        {                                                                           \
           _class err;                                                              \
            try                                                                     \
            {                                                                       \
                err.AddError(static_cast<uint32>(_error));                          \
            }                                                                       \
            catch(...)                                                              \
            {                                                                       \
            }                                                                       \
            const char* message = Error::GetDescription(_error);                    \
            if(message == null)                                                     \
            {                                                                       \
                message = PalmOS::StringStub;                                       \
            }                                                                       \
            ERRDISPLAYFILELINEMSG(__FILE__, __LINE__, message);                     \
            throw err;                                                              \
        }
#else
// agil - add a missing variable
#define palmxassert(_expr, _error, _class)
#define palmxassert_s(_expr, _error, _class)
#endif

#define FATAL_ERROR(_message)                                                       \
    ::SysFatalAlert(_message);                                                      \
    ::SysReset();                                                                   \

#define NON_FATAL_ERROR(_message)                                                   \
    ::SysFatalAlert(_message);                                                      \
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_ERROR_H__

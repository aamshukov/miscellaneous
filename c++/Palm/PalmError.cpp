////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PALM_ERROR_INC__
#   include <PalmError.inc>
#endif

#ifdef __PALM_OS__

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmError
// ----- ---------
PalmError::PalmError()
{
}

PalmError::~PalmError()
{
}

void PalmError::LoadErrorDescriptions()
{
    // base class
    Error::LoadErrorDescriptions();

    GetDescriptions()[eUnknownCtrl] = "An attempt to use an unknown control";
    GetDescriptions()[eUnknownRes]  = "Invalid resource";
}

void PalmError::PromptError(uint32 _err, const char* _message)
{
    if(_err == errNone && _message != null)
    {
        ErrDisplay(_message);
    }
    else
    {
        DECLARE_BUFFER

        // system
      ::SysErrString(static_cast<Err>(_err), buffer, BUFFER_SIZE);

        if(buffer[0] == 0)
        {
            // try to find descriptions
            const char* p = GetDescription(_err);

            if(p != null)
            {
                ErrDisplay(p);
            }
            else
            {
                // unknown
              ::StrCopy(buffer, "Unknown Fatal Error!");
                ErrDisplay(buffer);
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__

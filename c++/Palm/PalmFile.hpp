////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FILE_H__
#define __PALM_FILE_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PalmFile
// ----- --------
class __DECLSPEC__ PalmFile
{
    private:
     FileHand   Handle;
     Err        Error; // holds last error, internal use only
    public:
     // ctor/dtor
                PalmFile();
     virtual   ~PalmFile();

     // access
     FileHand   GetHandle() const;

     // operators
                operator FileHand ();

     // api
     Err        Open(uint16, const char*, uint32, uint32 = sysFileTFileStream, uint32 = fileModeReadOnly);
     Err        Close();
     static Err Delete(uint16, const char*);

     int32      Read(char*, int32, int32);
     int32      DmRead(char*, int32, int32, int32);
     int32      Write(const void*, int32, int32);
     
     Err        Flush();

     Err        Truncate(int32);

     Err        Rewind();
     Err        Seek(int32, FileOriginEnum = fileOriginBeginning);
     int32      Tell(int32&);

     Err        Control(FileOpEnum, void*, int32&);

     Err        IsEOF();

     Err        GetError();
     Err        GetLastError();
     Err        Clearerr();

    public:

    class __DECLSPEC__ XPalmFile : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'file'
        };

        public: 
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmFile;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FILE_H__


////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FT_MANAGER_H__
#define __FT_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTManager
// ----- ---------
class __DECLSPEC__ FTManager
{
    public:

    enum EType
    {
        // file
        TrGetFileInfo = 'gfin',
        TrCreateFile  = 'crtf',
        TrGetFile     = 'getf',
        TrPutFile     = 'putf',
        TrDeleteFile    'dltf',

        // folder
        TrGetFolderInfo = 'gfnf',
        TrChangeFolder  = 'chgf',
        TrCreateFolder  = 'crfl',
        TrGetFolder     = 'gtfl',
        TrPutFolder     = 'ptfl'
    };

    public:
     // ctor/dtor
                    FTManager();
     virtual       ~FTManager();

     // protocol
     virtual bool   CanHandle(const RRTransaction*);
     virtual void   Process(const RRTransaction*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FT_MANAGER_H__

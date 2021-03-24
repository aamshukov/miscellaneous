////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NEWS_MANAGER_H__
#define __NEWS_MANAGER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class NewsManager
// ----- -----------
class __DECLSPEC__ NewsManager
{
    public:

    enum EType
    {
        TrGetNews  = 'gnws',
        TrPostNews = 'pnws'
    };

    public:
     // ctor/dtor
                    NewsManager();
     virtual       ~NewsManager();

     // protocol
     virtual bool   CanHandle(const RRTransaction*);
     virtual void   Process(const RRTransaction*);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __NEWS_MANAGER_H__

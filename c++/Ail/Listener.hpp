////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __LISTENER_H__
#define __LISTENER_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Listener
// ----- --------
class __DECLSPEC__ Listener : public Singleton<Listener>
{
    private:
     HWND       HListener;
    public:
     // ctor/dtor
                Listener();
               ~Listener();

     // access
     HWND       GetListener()       const;
     void       SetListener(HWND);

     // protocol
     int        SendMessage(uint, uint, uint);
     int        PostMessage(uint, uint, uint);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __LISTENER_H__

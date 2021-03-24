////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __SOCKET_H__
#define __SOCKET_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Socket
// ----- ------
class __DECLSPEC__ Socket
{
    public:

    static const IPv4Address DummyIP;

    enum EState
    {
        Unknown      = 0, // unknown state, socket is not connected
        Connected    = 1, // socket is connected
        Disconnected = 2, // socket is disconnected
        Invalid      = 3  // socket is in invalid state (throw)
    };

    private:
                        Socket(const Socket&);
     Socket&            operator = (const Socket&);
    protected:
     IPv4Address        LocalAddress;
     IPv4Address        RemoteAddress;

     EState             State;
     SOCKET             Socket_;
    protected:
     static void        xxassert(Socket&, int, uint = X::InvalidArg);
     //
     virtual void       Connect(bool = true, int = 0, ushort = IPPROTO_IP)  = 0;
     virtual void       Disconnect()                                        = 0;
     virtual int        Send(const byte*, int, int = 0, int = 0)            = 0;
     virtual int        Receive(byte*, int = 0, int = 0, int = 0)           = 0;
     int                SetTimeout(int, short);
    public:
     // ctor/dtor
                        Socket();
     explicit           Socket(const IPv4Address&, const IPv4Address& = Socket::DummyIP);
     virtual           ~Socket();

     // access
     bool               IsConnected()                       const;
     EState             GetState()                          const;
     void               SetState(EState);

     IPv4Address&       GetLocalAddress()                   const;
     void               SetLocalAddress(const IPv4Address&);

     IPv4Address&       GetRemoteAddress()                  const;
     void               SetRemoteAddress(const IPv4Address&);

     SOCKET             GetSocket()                         const;
     void               SetSocket(SOCKET);

     operator           SOCKET ();

     // protocol
     void               GetOptions(int, int, byte*, int*)   const;
     void               SetOptions(int, int, byte*, int);

     int                SetBufferSize(int = 65536, int = SO_RCVBUF);
    public:
    
    ////////////////
    // class XSocket
    // ----- -------
    class __DECLSPEC__ XSocket : public X
    {
        public:

        enum EError
        {
            Timeout = 0x00000100
        };

        public:
            XSocket(uint = X::Failure);

            virtual tchar* Why()
            {
                static tchar buffer[64];
                sprintf(buffer, "error: [%ld], syserror: [%ld]", Error, SysError);
                return buffer;
            }
    };

    friend class XSocket;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __SOCKET_H__

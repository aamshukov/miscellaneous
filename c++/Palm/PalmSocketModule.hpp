////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_SOCKET_MODULE_H__
#define __PALM_SOCKET_MODULE_H__

#ifdef __PALM_OS__ 

#pragma once
////////////////////////////////////////////////////////////////////////////////////////
#define HtoNS(x) (x)
#define HtoNL(x) (x)
#define NtoHS(x) (x)
#define NtoHL(x) (x)
////////////////////////////////////////////////////////////////////////////////////////
__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
typedef NetSocketRef        socket_t;
typedef NetSocketAddrINType sockaddr_in_t;
typedef NetSocketAddrType   sockaddr_t;
typedef NetIPAddr           in_addr_t;
typedef NetHostInfoType     hostent_t;
typedef NetHostInfoBufType  hostent_buf_t;
typedef NetServInfoType     servent_t;
typedef NetServInfoBufType  servent_buf_t;
typedef NetFDSetType        fd_set_t;

#undef netFDSet
#define netFDSet(n, p) ((*p) |= static_cast<fd_set_t>(1 << n))

#undef  INVALID_SOCKET
#define INVALID_SOCKET (static_cast<socket_t>(-1))
////////////////////////////////////////////////////////////////////////////////////////
// class PalmSocketModule
// ----- ----------------
class __DECLSPEC__ PalmSocketModule : public PalmModule
{
    public:

    enum EConst
    {
        eTimeout = 20*1000
    };

    private:
     static Err         Error;
    protected:
     virtual Err        Open();
     virtual Err        Close();
     virtual void       LoadErrorDescriptions();
    public:
     // ctor/dtor
                        PalmSocketModule(bool = true);
                       ~PalmSocketModule();

     // access
     static Err         GetError();
     static PalmModule& GetSocketModule();

     // sockets api
     static socket_t    CreateSocket(NetSocketAddrEnum = netSocketAddrINET, NetSocketTypeEnum = netSocketTypeStream, int16 = netSocketProtoIPTCP, uint16 = PalmSocketModule::eTimeout);
     static int16       CloseSocket(socket_t, uint16 = PalmSocketModule::eTimeout);

     static int16       Shutdown(socket_t, int16, uint16 = PalmSocketModule::eTimeout);

     static int16       Connect(socket_t, sockaddr_t*, int16, uint16 = PalmSocketModule::eTimeout);
     static socket_t    Accept(socket_t, sockaddr_t*, int16&, uint16 = PalmSocketModule::eTimeout);
     static int16       Bind(socket_t, sockaddr_t*, int16, uint16 = PalmSocketModule::eTimeout);
     static int16       Listen(socket_t, uint16 = 8, uint16 = PalmSocketModule::eTimeout);

     static hostent_t*  GetHostByAddress(hostent_buf_t&, sockaddr_t*, uint16, uint16, uint16 = PalmSocketModule::eTimeout);
     static hostent_t*  GetHostByName(hostent_buf_t&, char*, uint16 = PalmSocketModule::eTimeout);
     static Err         GetHostName(char*, uint16&);

     static int16       GetPeerName(socket_t, sockaddr_t*, int16&, uint16 = PalmSocketModule::eTimeout);
     static int16       GetSocketName(socket_t, sockaddr_t*, int16&, uint16 = PalmSocketModule::eTimeout);

     static servent_t*  GetServiceByName(servent_buf_t&, const char*, const char*, uint16 = PalmSocketModule::eTimeout);

     static int16       GetSocketOption(socket_t, uint16, uint16, void*, uint16&, uint16 = PalmSocketModule::eTimeout);
     static int16       SetSocketOption(socket_t, uint16, uint16, void*, uint16, uint16 = PalmSocketModule::eTimeout);

     static in_addr_t   InetAddress(char*);
     static char*       InetNtoA(in_addr_t, char*);

     static int16       Receive(socket_t, byte*, uint16, uint16, sockaddr_t*, uint16&, uint16 = PalmSocketModule::eTimeout);
     static int16       ReceiveFrom(socket_t, NetIOParamType&, uint16, uint16 = PalmSocketModule::eTimeout);

     static int16       Send(socket_t, byte*, uint16, uint16, sockaddr_t*, uint16, uint16 = PalmSocketModule::eTimeout);
     static int16       SendTo(socket_t, NetIOParamType&, uint16, uint16 = PalmSocketModule::eTimeout);

     static int16       Select(uint16, fd_set_t*, fd_set_t*, fd_set_t*, uint16 = PalmSocketModule::eTimeout);

    public:

    class __DECLSPEC__ XPalmSocketModule : public XPalmModule
    {
        public:

        enum EErrors
        {
            // appErrorClass+'scmd'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XPalmModule;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__ 
#endif // __PALM_SOCKET_MODULE_H__

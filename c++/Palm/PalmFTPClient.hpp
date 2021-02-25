////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  Copyright © 1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FTP_CLIENT_H__
#define __PALM_FTP_CLIENT_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPClient
// ----- ---------
class __DECLSPEC__ FTPClient
{
    typedef PalmStreamSocket _Socket;

    private:
     FTPURL                 ProxyServer;
     FTPURL                 SOCKSServer;

     FTPURL                 Resource;

    _string                 Username;
    _string                 Password;
    _string                 Account;

     uint16                 SocksVersion;   // SOCKS4/SOCKS5

    _Socket                 Connection;
     volatile bool          Terminated;
    protected:
     ftpcode                GetGreetings();
     ftpcode                ProcessRequest(const char*, uint16 = PalmSocket::eTimeout, bool = false);
    public:
     // ctor/dtor
                            FTPClient(const FTPURL&);
                           ~FTPClient();

     // access
     const FTPURL&          GetProxyServer()                const;
     void                   SetProxyServer(const char*);

     const FTPURL&          GetSOCKSServer()                const;
     void                   SetSOCKSServer(const char*);

     const FTPURL&          GetResource()                   const;
     void                   SetResource(const char*);

    _string                 GetUsername()                   const;
     void                   SetUsername(const _string&);

    _string                 GetPassword()                   const;
     void                   SetPassword(const _string&);

    _string                 GetAccount()                    const;
     void                   SetAccount(const _string&);

     uint16                 GetSocksVersion()               const;
     void                   SetSocksVersion(uint16);

     const _Socket&         GetConnection()                 const;

     // api
     ftpcode                Connect();
     ftpcode                Disconnect();

     void                   Terminate();

     ftpcode                Login(const char* = null, const char* = null, const char* = null, uint16 = PalmSocket::eTimeout);

     ftpcode                CheckLink(bool = false, uint16 = PalmSocket::eTimeout);
     static ftpcode         CheckLink(const char*, const char* = null, bool = false, uint16 = PalmSocket::eTimeout);

     ftpcode                GetSize(fsize_t_&, bool = false, uint16 = PalmSocket::eTimeout);
     static ftpcode         GetSize(fsize_t_&, const char*, const char* = null, bool = false, uint16 = PalmSocket::eTimeout);

     ftpcode                GetResource(PalmFile&, const char* = null, fpos_t_ = 0, fsize_t_& = fsize_stub, bool = false, uint16 = PalmSocket::eTimeout);
     ftpcode                GetResourceThroughFirewall(PalmFile&, const char* = null, fpos_t_ = 0, fsize_t_& = fsize_stub, uint16 = PalmSocket::eTimeout);
     ftpcode                GetResourceFirewallFree(PalmFile&, const char* = null, fpos_t_ = 0, fsize_t_& = fsize_stub, uint16 = PalmSocket::eTimeout);
     static ftpcode         GetResource(const char*, const char*, fpos_t_ = 0, const char* = null, bool = false, uint16 = PalmSocket::eTimeout);

     ftpcode                GetList(PalmFile&, const char* = null, bool = false, uint16 = PalmSocket::eTimeout);
     ftpcode                GetListThroughFirewall(PalmFile&, const char* = null, uint16 = PalmSocket::eTimeout);
     ftpcode                GetListFirewallFree(PalmFile&, const char* = null, uint16 = PalmSocket::eTimeout);
     static ftpcode         GetList(const char*, const char*, const char* = null, bool = false, uint16 = PalmSocket::eTimeout);

     // commands
     ftpcode                SendCommandUSER(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandPASS(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandACCT(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandCWD(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandCDUP(uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSMNT(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandQUIT(uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandREIN(uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandPORT(uint32, uint16, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandPASV(PalmIPv4&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandTYPE(FTProtocol::EFileType, FTProtocol::EFileFormat, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSTRU(FTProtocol::EDataStructure, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandMODE(FTProtocol::ETransmissionMode, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandRETR(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSTOR(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSTOU(uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandAPPE(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandALLO(uint32, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandREST(uint32, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandRNFR(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandRNTO(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandABOR(uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandDELE(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandRMD(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandMKD(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandPWD(uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandLIST(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandNLST(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSITE(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSYST(uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSTAT(const _string&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandSIZE(const _string&, fsize_t_&, uint16 = PalmSocket::eTimeout);
     ftpcode                SendCommandHELP(const _string&, uint32);
     ftpcode                SendCommandNOOP(uint16 = PalmSocket::eTimeout);

    public:
    
    class __DECLSPEC__ XFTPClient : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'ftpc'
        };

        protected:
         virtual void LoadErrorDescriptions();
    };

    friend class XFTPClient;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FTP_CLIENT_H__

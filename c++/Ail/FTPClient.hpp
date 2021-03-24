////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FTP_CLIENT_H__
#define __FTP_CLIENT_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTPClient
// ----- ---------
class __DECLSPEC__ FTPClient
{
    enum ETimeout
    {
        Timeout = 20
    };

    private:
     FTPURL                 ProxyServer;
     FTPURL                 SOCKSServer;
     FTPURL                 Resource;

     String<>               Username;
     String<>               Password;
     String<>               Account;

     short                  SocksVersion;   // SOCKS4/SOCKS5

     StreamSocket           Connection;
     volatile bool          Terminated;
    protected:
     ftpcode                GetGreetings();
     ftpcode                ProcessRequest(const char*, uint = FTPClient::Timeout, bool = false);
    public:
     // ctor/dtor
                            FTPClient(const FTPURL&);
                           ~FTPClient();

     // access
     const FTPURL&          GetProxyServer()                const;
     void                   SetProxyServer(const tchar*);

     const FTPURL&          GetSOCKSServer()                const;
     void                   SetSOCKSServer(const tchar*);

     const FTPURL&          GetResource()                   const;
     void                   SetResource(const tchar*);

     String<>               GetUsername()                   const;
     void                   SetUsername(const String<>&);

     String<>               GetPassword()                   const;
     void                   SetPassword(const String<>&);

     String<>               GetAccount()                    const;
     void                   SetAccount(const String<>&);

     short                  GetSocksVersion()               const;
     void                   SetSocksVersion(short);

     const StreamSocket&    GetConnection()                 const;

     // protocol
     ftpcode                Connect();
     ftpcode                Disconnect();

     void                   Terminate();

     ftpcode                Login(const char* = null, const char* = null, const char* = null, uint = FTPClient::Timeout);

     ftpcode                CheckLink(bool = false, uint = FTPClient::Timeout);
     static ftpcode         CheckLink(const tchar*, const tchar* = null, bool = false, uint = FTPClient::Timeout);

     ftpcode                GetSize(fsize_t_&, bool = false, uint = FTPClient::Timeout);
     static ftpcode         GetSize(fsize_t_&, const tchar*, const tchar* = null, bool = false, uint = FTPClient::Timeout);

     ftpcode                GetResource(File<>&, const tchar* = null, fpos_t_ = 0, fsize_t_& = fsize_stub, bool = false, uint = FTPClient::Timeout);
     ftpcode                GetResourceThroughFirewall(File<>&, const tchar* = null, fpos_t_ = 0, fsize_t_& = fsize_stub, uint = FTPClient::Timeout);
     ftpcode                GetResourceFirewallFree(File<>&, const tchar* = null, fpos_t_ = 0, fsize_t_& = fsize_stub, uint = FTPClient::Timeout);
     static ftpcode         GetResource(const tchar*, const tchar*, fpos_t_ = 0, const tchar* = null, bool = false, uint = FTPClient::Timeout);

     ftpcode                GetList(File<>&, const tchar* = null, bool = false, uint = FTPClient::Timeout);
     ftpcode                GetListThroughFirewall(File<>&, const tchar* = null, uint = FTPClient::Timeout);
     ftpcode                GetListFirewallFree(File<>&, const tchar* = null, uint = FTPClient::Timeout);
     static ftpcode         GetList(const tchar*, const tchar*, const tchar* = null, bool = false, uint = FTPClient::Timeout);

     // commands
     ftpcode                SendCommandUSER(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandPASS(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandACCT(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandCWD(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandCDUP(uint = FTPClient::Timeout);
     ftpcode                SendCommandSMNT(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandQUIT(uint = FTPClient::Timeout);
     ftpcode                SendCommandREIN(uint = FTPClient::Timeout);
     ftpcode                SendCommandPORT(uint, ushort, uint = FTPClient::Timeout);
     ftpcode                SendCommandPASV(IPv4Address&, uint = FTPClient::Timeout);
     ftpcode                SendCommandTYPE(FTProtocol::EFileType, FTProtocol::EFileFormat, uint = FTPClient::Timeout);
     ftpcode                SendCommandSTRU(FTProtocol::EDataStructure, uint = FTPClient::Timeout);
     ftpcode                SendCommandMODE(FTProtocol::ETransmissionMode, uint = FTPClient::Timeout);
     ftpcode                SendCommandRETR(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandSTOR(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandSTOU(uint = FTPClient::Timeout);
     ftpcode                SendCommandAPPE(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandALLO(uint, uint = FTPClient::Timeout);
     ftpcode                SendCommandREST(uint, uint = FTPClient::Timeout);
     ftpcode                SendCommandRNFR(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandRNTO(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandABOR(uint = FTPClient::Timeout);
     ftpcode                SendCommandDELE(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandRMD(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandMKD(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandPWD(uint = FTPClient::Timeout);
     ftpcode                SendCommandLIST(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandNLST(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandSITE(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandSYST(uint = FTPClient::Timeout);
     ftpcode                SendCommandSTAT(const String<>&, uint = FTPClient::Timeout);
     ftpcode                SendCommandSIZE(const String<>&, fsize_t_&, uint = FTPClient::Timeout);
     ftpcode                SendCommandHELP(const String<>&, uint);
     ftpcode                SendCommandNOOP(uint = FTPClient::Timeout);
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FTP_CLIENT_H__

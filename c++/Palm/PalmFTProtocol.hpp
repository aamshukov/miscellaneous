////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PALM_FT_PROTOCOL_H__
#define __PALM_FT_PROTOCOL_H__

#ifdef __PALM_OS__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class FTProtocol
// ----- ----------
class FTProtocol
{
    public:

    enum EFileType
    {
        eASCII  = 'A', // default
        eEBCDIC = 'E',
        eBinary = 'I', // image
        eLocal  = 'L'
    };

    enum EFileFormat
    {
        eNonprint = 'N', // default
        eTelnet   = 'T',
        eFORTRAN  = 'C'
    };

    enum ETransmissionMode
    {
        eStream     = 'S', // default
        eBlock      = 'B',
        eCompressed = 'C'
    };

    enum EDataStructure
    {
        eFile   = 'F',  // default
        eRecord = 'R',
        ePage   = 'P'
    };

    enum ECode
    { 
        eCode0   = -1,  // Unknown
        eCode000 = 0,   // Announcing FTP.  
        eCode010 = 10,  // Message from system operator.
        eCode020 = 20,  // Exected delay.
        eCode030 = 30,  // Server availability information.
        eCode050 = 50,  // FTP commentary or user information.
        eCode100 = 100, // System status reply.
        eCode110 = 110, // Restart marker reply.
        eCode120 = 120, // Service ready in nnn minutes.
        eCode125 = 125, // Data connection already open; transfer starting.
        eCode150 = 150, // File status okay; about to open data connection.
        eCode151 = 151, // Directory listing reply. 
        eCode200 = 200, // Command okay.
        eCode201 = 201, // An ABORT has terminated activity, as requested.
        eCode202 = 202, // Command not implemented, superfluous at this site.
        eCode211 = 211, // System status, or system help reply.
        eCode212 = 212, // Directory status.
        eCode213 = 213, // File status.
        eCode214 = 214, // Help message.
        eCode215 = 215, // NAME system type.
        eCode220 = 220, // Service ready for new user.
        eCode221 = 221, // Service closing control connection.
        eCode225 = 225, // Data connection open; no transfer in progress.
        eCode226 = 226, // Closing data connection.
        eCode227 = 227, // Entering Passive Mode (h1,h2,h3,h4,p1,p2).
        eCode230 = 230, // User logged in, proceed.
        eCode231 = 231, // User is "logged out".  Service terminated.
        eCode232 = 232, // Logout command noted, will complete when transfer done.
        eCode233 = 233, // User is "logged out".  Parameters reinitialized.
        eCode250 = 250, // Requested file action okay, completed.
        eCode251 = 251, // FTP Restart-marker reply.
                        //      Text is:  MARK yyyy = mmmm
                        //      where 'yyyy' is user's data stream marker (yours)
                        //      and mmmm is server's equivalent marker (mine)
                        //      (Note the spaces between the markers and '=').
        eCode252 = 252, // FTP transfer completed correctly.  
        eCode253 = 253, // Rename completed.
        eCode254 = 254, // Delete completed.
        eCode257 = 257, // "PATHNAME" created.
        eCode300 = 300, // Connection greeting message, awaiting input.
        eCode301 = 301, // Current command incomplete (no <CRLF> for long time).
        eCode331 = 331, // User name okay, need password.
        eCode332 = 332, // Need account for login.
        eCode350 = 350, // Requested file action pending further information.
        eCode400 = 400, // This service not implemented.
        eCode401 = 401, // This service not accepting users now, goodbye.
        eCode402 = 402, // Command not implemented for requested value or action.
        eCode421 = 421, // Service not available, closing control connection.
        eCode425 = 425, // Can't open data connection.
        eCode426 = 426, // Connection closed; transfer aborted.
        eCode430 = 430, // Log-on time or tries exceeded, goodbye.
        eCode431 = 431, // Log-on unsuccessful.  User and/or password invalid.
        eCode432 = 432, // User not valid for this service.
        eCode433 = 433, // Cannot transfer files without valid account. Enter account and resend command.
        eCode434 = 434, // Log-out forced by operator action.  Phone site.
        eCode435 = 435, // Log-out forced by system problem.  
        eCode436 = 436, // Service shutting down, goodbye.
        eCode450 = 450, // Requested file action not taken.
        eCode451 = 451, // Requested action aborted: local error in processing.
        eCode452 = 452, // Requested action not taken.
        eCode453 = 453, // File transfer incomplete, insufficient storage space.
        eCode454 = 454, // Cannot connect to your data socket.
        eCode455 = 455, // File system error not covered by other reply codes.
        eCode456 = 456, // Name duplication; rename failed.
        eCode457 = 457, // Transfer parameters in error.
        eCode500 = 500, // Syntax error, command unrecognized.
        eCode501 = 501, // Syntax error in parameters or arguments.
        eCode502 = 502, // Command not implemented.
        eCode503 = 503, // Bad sequence of commands.
        eCode504 = 504, // Command not implemented for that parameter.
        eCode505 = 505, // Last command conflicts illegally with previous command(s).
        eCode506 = 506, // Last command not implemented by the server.  
        eCode507 = 507, // Catchall error reply.
        eCode530 = 530, // Not logged in.
        eCode532 = 532, // Need account for storing files.
        eCode550 = 550, // Requested action not taken.
        eCode551 = 551, // Requested action aborted: page type unknown.
        eCode552 = 552, // Requested file action aborted.
        eCode553 = 553  // Requested action not taken.
    };

    typedef FTProtocol::ECode ftpcode;

    public:
     // ctor/dtor
                        FTProtocol();
                       ~FTProtocol();

     // protocol
     static ftpcode     GetResponseCode(const char*);
     static bool        IsMultiLineResponse(const char*);
     static _string     GetMultiLineResponse(const char*);
     static void        BuildPortRequest(uint32, uint16, char*);
     static void        ParseListLine(const char*);
     static ftpcode     GetResourceSize(const char*, fsize_t_&);

    public:

    class __DECLSPEC__ XFTProtocol : public PalmError
    {
        public:

        enum EErrors
        {
            // appErrorClass+'ftpr'
        };

        public:
         virtual void LoadErrorDescriptions();
    };

    friend class XFTProtocol;
};
//
typedef FTProtocol::ECode ftpcode;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PALM_OS__
#endif // __PALM_FT_PROTOCOL_H__

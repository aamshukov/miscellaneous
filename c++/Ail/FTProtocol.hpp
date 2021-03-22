////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __FT_PROTOCOL_H__
#define __FT_PROTOCOL_H__

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
        ASCII  = 'A',   // default
        EBCDIC = 'E',
        Binary = 'I',   // image
        Local  = 'L'
    };

    enum EFileFormat
    {
        Nonprint = 'N', // default
        Telnet   = 'T',
        FORTRAN  = 'C'
    };

    enum ETransmissionMode
    {
        Stream     = 'S',   // default
        Block      = 'B',
        Compressed = 'C'
    };

    enum EDataStructure
    {
        File   = 'F',  // default
        Record = 'R',
        Page   = 'P'
    };

    enum ECode
    { 
        Code0   = -1,   // Unknown
        Code000 = 0,    // Announcing FTP.  
        Code010 = 10,   // Message from system operator.
        Code020 = 20,   // Exected delay.
        Code030 = 30,   // Server availability information.
        Code050 = 50,   // FTP commentary or user information.
        Code100 = 100,  // System status reply.
        Code110 = 110,  // Restart marker reply.
        Code120 = 120,  // Service ready in nnn minutes.
        Code125 = 125,  // Data connection already open; transfer starting.
        Code150 = 150,  // File status okay; about to open data connection.
        Code151 = 151,  // Directory listing reply. 
        Code200 = 200,  // Command okay.
        Code201 = 201,  // An ABORT has terminated activity, as requested.
        Code202 = 202,  // Command not implemented, superfluous at this site.
        Code211 = 211,  // System status, or system help reply.
        Code212 = 212,  // Directory status.
        Code213 = 213,  // File status.
        Code214 = 214,  // Help message.
        Code215 = 215,  // NAME system type.
        Code220 = 220,  // Service ready for new user.
        Code221 = 221,  // Service closing control connection.
        Code225 = 225,  // Data connection open; no transfer in progress.
        Code226 = 226,  // Closing data connection.
        Code227 = 227,  // Entering Passive Mode (h1,h2,h3,h4,p1,p2).
        Code230 = 230,  // User logged in, proceed.
        Code231 = 231,  // User is "logged out".  Service terminated.
        Code232 = 232,  // Logout command noted, will complete when transfer done.
        Code233 = 233,  // User is "logged out".  Parameters reinitialized.
        Code250 = 250,  // Requested file action okay, completed.
        Code251 = 251,  // FTP Restart-marker reply.
                        //      Text is:  MARK yyyy = mmmm
                        //      where 'yyyy' is user's data stream marker (yours)
                        //      and mmmm is server's equivalent marker (mine)
                        //      (Note the spaces between the markers and '=').
        Code252 = 252,  // FTP transfer completed correctly.  
        Code253 = 253,  // Rename completed.
        Code254 = 254,  // Delete completed.
        Code257 = 257,  // "PATHNAME" created.
        Code300 = 300,  // Connection greeting message, awaiting input.
        Code301 = 301,  // Current command incomplete (no <CRLF> for long time).
        Code331 = 331,  // User name okay, need password.
        Code332 = 332,  // Need account for login.
        Code350 = 350,  // Requested file action pending further information.
        Code400 = 400,  // This service not implemented.
        Code401 = 401,  // This service not accepting users now, goodbye.
        Code402 = 402,  // Command not implemented for requested value or action.
        Code421 = 421,  // Service not available, closing control connection.
        Code425 = 425,  // Can't open data connection.
        Code426 = 426,  // Connection closed; transfer aborted.
        Code430 = 430,  // Log-on time or tries exceeded, goodbye.
        Code431 = 431,  // Log-on unsuccessful.  User and/or password invalid.
        Code432 = 432,  // User not valid for this service.
        Code433 = 433,  // Cannot transfer files without valid account. Enter account and resend command.
        Code434 = 434,  // Log-out forced by operator action.  Phone site.
        Code435 = 435,  // Log-out forced by system problem.  
        Code436 = 436,  // Service shutting down, goodbye.
        Code450 = 450,  // Requested file action not taken.
        Code451 = 451,  // Requested action aborted: local error in processing.
        Code452 = 452,  // Requested action not taken.
        Code453 = 453,  // File transfer incomplete, insufficient storage space.
        Code454 = 454,  // Cannot connect to your data socket.
        Code455 = 455,  // File system error not covered by other reply codes.
        Code456 = 456,  // Name duplication; rename failed.
        Code457 = 457,  // Transfer parameters in error.
        Code500 = 500,  // Syntax error, command unrecognized.
        Code501 = 501,  // Syntax error in parameters or arguments.
        Code502 = 502,  // Command not implemented.
        Code503 = 503,  // Bad sequence of commands.
        Code504 = 504,  // Command not implemented for that parameter.
        Code505 = 505,  // Last command conflicts illegally with previous command(s).
        Code506 = 506,  // Last command not implemented by the server.  
        Code507 = 507,  // Catchall error reply.
        Code530 = 530,  // Not logged in.
        Code532 = 532,  // Need account for storing files.
        Code550 = 550,  // Requested action not taken.
        Code551 = 551,  // Requested action aborted: page type unknown.
        Code552 = 552,  // Requested file action aborted.
        Code553 = 553   // Requested action not taken.
    };
    typedef FTProtocol::ECode ftpcode;

    public:
     // ctor/dtor
                        FTProtocol();
                       ~FTProtocol();

     // protocol
     static ftpcode     GetResponseCode(const char*);
     static bool        IsMultiLineResponse(const char*);
     static String<>    GetMultiLineResponse(const char*);
     static void        BuildPortRequest(uint, ushort, char*);
     static void        ParseListLine(const char*);
     static ftpcode     GetResourceSize(const char*, fsize_t_&);
};
//
typedef FTProtocol::ECode ftpcode;
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __FT_PROTOCOL_H__

//
//  ftpCommand.h
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_ftpCommand_h
#define libuvftp_ftpCommand_h

#include <string>
#include "uv.h"
#include <iostream>

struct passiveDataChannelConnection
{
    uv_tcp_t* dataConnSocket;
    std::string serverIp;
    int portNr;
    uv_connect_t* connection;
};

class ftpCommand {
    
private:

	//libv read cb
	static void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);

	static void on_DataRead(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);

protected:
    const std::string command;

    //function pointer which decides whether there is something to read
    static bool(*finishReading)(std::string lineRead);

	//function pointer which decides whether there is something to read (used in on_DataRead)
	static bool(*finishReading2)(std::string lineRead);

    //Called by the libuv read cb (on_read) every time, it is used e.g. to store partial results 
    static void (*processResonse)(std::string response);

	static void writeCb(uv_write_t* req, int status);
    

       
public:
	//callback called when the operation is done and it has a result from the on_read
	static void(*ReadFinishedCB) (bool success, std::string &response);

	//callback called when the operation is done and it has a result from the on_DataRead
	static void(*ReadFinishedCB2) (bool success);

	//Sends a message and initializes the read of the response (mainly used by the control channel)
	static void InitWriteRead(uv_stream_t* socket, std::string command);
    
    //connects to the socket and reads the data (mainly used for reading from the data channel)
    static void ConnectAndReadFromStream(passiveDataChannelConnection& dataChannel);
};

#endif

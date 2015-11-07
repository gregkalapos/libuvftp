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


class ftpCommand {
    
protected:
    const std::string command;
    static void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
    //function pointer which decides whether there is something to read
    static bool(*finishReading)(std::string lineRead);
    //Called when the read cb is called, it is used e.g. to store partial results
    static void (*processResonse)(std::string response);

	static void writeCb(uv_write_t* req, int status);
    
public:
    //callback called when the operation is done and it has a result
    static void(*ReadFinishedCB) (bool success, std::string &response);

	static void InitWriteRead(uv_stream_t* socket, std::string command);
    
    //connects to the socket and reads the data (mainly used for reading from the data channel)
    static void ConnectAndReadFromStream(uv_stream_t* socket);
};

#endif

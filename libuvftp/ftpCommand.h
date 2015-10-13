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
    static void (*processResonse)(std::string response);
public:
    //callback called when the operation is done and it has a result
    static void(*stringReadCB) (bool success, std::string &response);
};

#endif

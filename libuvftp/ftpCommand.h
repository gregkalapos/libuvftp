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



//void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
//    buf->base = (char*)malloc(suggested_size);
//    buf->len = suggested_size;
//}

class ftpCommand {
    
protected:
    const std::string command;
    static void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
    static bool(*finishReading)(std::string lineRead); //function pointer which decides whether there is something to read
    
public:
     static void(*stringReadCB) (bool success, std::string &response);
};

#endif

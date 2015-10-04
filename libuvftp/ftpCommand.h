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
    
public:
   // static virtual void run() = 0;
    
};

#endif

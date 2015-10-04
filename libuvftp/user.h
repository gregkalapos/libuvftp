//
//  user.h
//  libuvftp
//
//  Created by Gergely Kalapos on 04/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_user_h
#define libuvftp_user_h

#include "ftpCommand.h"

class user: public ftpCommand {
    static char* chr;
    static void writeCb(uv_write_t* req, int status);
    
    static void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
    
    static void(*callback) (bool success, std::string &response);
public:
    
    static void run(uv_stream_t* socket, void(*fp)(bool, std::string&));
    
};

#endif

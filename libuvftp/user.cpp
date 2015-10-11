//
//  user.hpp
//  libuvftp
//
//  Created by Gergely Kalapos on 04/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_user_hpp
#define libuvftp_user_hpp


#endif

#include "user.h"


char* user::chr = new char[256];

bool user::isEndOfSuccessMsg(std::string text)
{
   // std::replace(text.begin(), text.end(), ' ', '');
   // std::replace(text.begin(), text.end(), '-', '');
    return text.find("230 Login successful") != std::string::npos;
}

void alloc_buffer_u(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void user::writeCb(uv_write_t* req, int status)
{
    uv_read_start(req->handle, alloc_buffer_u, on_read);
}

void user::run(uv_stream_t* socket, void(*fp)(bool, std::string&))
{
    ftpCommand::stringReadCB = fp;
    ftpCommand::finishReading = isEndOfSuccessMsg;
    
    uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
    char c[] = "USER anonymous\n";
    uv_buf_t wrbuf = uv_buf_init(c, 15);
    
    uv_write(req, socket, &wrbuf, 1, writeCb);
}
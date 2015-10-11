//
//  pasv.cpp
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_pasv_cpp
#define libuvftp_pasv_cpp

#include "pasv.h"

void alloc_buffer_u2(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void pasv::writeCbPasv(uv_write_t* req, int status)
{
    uv_read_start(req->handle, alloc_buffer_u2, on_read);
}

void pasv::run(uv_stream_t* socket, void(*fp)(bool, std::string&))
{
    ftpCommand::stringReadCB = fp;
    //ftpCommand::finishReading = isEndOfSuccessMsg;
    
    uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
    char c[] = "PASV \n";
    uv_buf_t wrbuf = uv_buf_init(c, 15);
    
    uv_write(req, socket, &wrbuf, 1, writeCbPasv);
}

#endif

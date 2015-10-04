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

void(*user::callback) (bool success, std::string &response) = NULL;

void alloc_buffer_u(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void user::on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread < 0) {
        if (nread != UV_EOF){
            std::string str("Read error %s\n");
            callback(false, str);
        }
        //fprintf(stderr, , uv_err_name(nread));
        uv_close((uv_handle_t*) client, NULL);
        free(client);
        return;
    }
    
    char *data = (char*) malloc(sizeof(char) * (nread+1));
    data[nread] = '\0';
    strncpy(data, buf->base, nread);
    std::string str(data);
    
    if(callback!= nullptr)
    {
        callback(true, str);
      //  callback = nullptr;
    }
    
    //uv_read_stop(client);
    free(data);
    free(buf->base);
}


void user::writeCb(uv_write_t* req, int status)
{
    uv_read_start(req->handle, alloc_buffer_u, on_read);
}

void user::run(uv_stream_t* socket, void(*fp)(bool, std::string&))
{
    callback = fp;
    
    uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
    char c[] = "USER anonymous\n";
    uv_buf_t wrbuf = uv_buf_init(c, 15);
    
 // uv_write_cb
    //uv_write(<#uv_write_t *req#>, uv_stream_t *handle, <#const uv_buf_t *bufs#>, <#unsigned int nbufs#>, <#uv_write_cb cb#>)
    
   // uv_read_start(req->handle, alloc_buffer_u, on_read);
    uv_write(req, socket, &wrbuf, 1, writeCb);
}
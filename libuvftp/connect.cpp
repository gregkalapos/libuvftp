//
//  connect.cpp
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_connect_cpp
#define libuvftp_connect_cpp

#include "connect.h"

void(*connect::callback) (bool success, std::string &response) = NULL;

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void connect::on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
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
    
    callback(true, str);
    
    free(data);
    free(buf->base);
}

void connect::on_connect(uv_connect_t* req, int status)
{
    if(status < 0)
    {
        std::string str = "error on connect";
        callback(false, str);
    }
    else
    {
        uv_read_start((uv_stream_t*) req->handle, alloc_buffer, on_read);
    }
}

void connect::startConnect(std::string _ip, int _port, void(*fp) (bool, std::string&))
{
    callback = fp;
    
    uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), socket);
    
    uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));
    
    struct sockaddr_in dest;
    
    uv_ip4_addr(_ip.c_str(), _port, &dest);
    
    //uv_tcp_connect(<#uv_connect_t *req#>, <#uv_tcp_t *handle#>, <#const struct sockaddr *addr#>, <#uv_connect_cb cb#>)
    
    uv_tcp_connect(connect, socket, (const struct sockaddr*)&dest, on_connect );
}


#endif

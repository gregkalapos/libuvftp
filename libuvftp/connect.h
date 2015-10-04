//
//  connect.h
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_connect_h
#define libuvftp_connect_h

#include <string>
#include "uv.h"
#include <iostream>

class connect {
    
private:
    static std::string ip;
    static int port;
    static void(*callback) (bool success, std::string &response);
    
    static void on_connect(uv_connect_t* req, int status);
    static void on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
    
public:
    //connect(): ip(_ip), port(_port){};
    static void startConnect(uv_tcp_t* socket, std::string _ip, int _port, void(*fp) (bool, std::string&));
//    void startConnect();
   
};

#endif

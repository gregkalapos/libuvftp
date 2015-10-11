//
//  clientPi.cpp
//  libuvftp
//
//  Created by Gergely Kalapos on 04/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_clientPi_cpp
#define libuvftp_clientPi_cpp

#include "clientPi.h"
#include "user.h"
#include "pasv.h"

uv_tcp_t* clientPi::socket = NULL;

void clientPi::connect(std::string _ip, int _port, void(*fp) (bool, std::string&))
{
    socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    connect::startConnect(socket, _ip, _port, fp);
}

void clientPi::execute(ftpCommand ftpCommand)
{
    
}

void clientPi::executeUser(void(*fp) (bool, std::string&))
{
    user::run((uv_stream_s*)socket, fp);
}

void clientPi::executePasv(void(*fp) (bool, std::string&))
{
    pasv::run((uv_stream_s*)socket, fp);
}

#endif

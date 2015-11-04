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
#include "list.h"

uv_tcp_t* clientPi::controlConnSocket = nullptr;
uv_tcp_t* clientPi::dataConnSocket = nullptr;

void clientPi::connect(std::string _ip, int _port, void(*fp) (bool, std::string&))
{
    controlConnSocket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    connect::startConnect(controlConnSocket, _ip, _port, fp);
}

//void clientPi::execute(ftpCommand ftpCommand)
//{
//    
//}

void clientPi::executeUser(std::string userName, void(*fp) (bool, std::string&))
{
    user::run((uv_stream_s*)controlConnSocket, fp, userName);
}

void clientPi::executePasv(void(*fp) (bool, std::string&))
{
    dataConnSocket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    pasv::run((uv_stream_s*)controlConnSocket, fp, dataConnSocket);
}

void clientPi::executeList(void(*controlChannelCb) (bool, std::string&), void(*dataChannelCb) (bool, std::string&))
{
    list::run((uv_stream_s*)controlConnSocket, controlChannelCb, dataConnSocket, dataChannelCb);
}

#endif

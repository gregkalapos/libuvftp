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
#include "pwdCom.h"
#include "type.h"
#include "Pass.h"

uv_tcp_t* clientPi::controlConnSocket = nullptr;
//uv_tcp_t* clientPi::dataConnSocket = nullptr;

passiveDataChannelConnection clientPi::dataConnSocket;

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
    clientPi::dataConnSocket.dataConnSocket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    pasv::run((uv_stream_s*)controlConnSocket, fp, dataConnSocket);
}

void clientPi::executeList(void(*controlChannelCb) (bool, std::string&), void(*dataChannelCb) (bool, std::string&))
{
    list::run((uv_stream_s*)controlConnSocket, controlChannelCb, dataConnSocket, dataChannelCb);
}

void clientPi::executePwd(void(*fp) (bool, std::string&))
{
	pwd::run((uv_stream_s*)controlConnSocket, fp);
}


void clientPi::executeType(std::string type, void(*fp) (bool, std::string&))
{
	type::run(type, (uv_stream_s*)controlConnSocket, fp);
}

void clientPi::executePass(std::string password, void(*fp) (bool, std::string&))
{
	Pass::run(password, (uv_stream_s*)controlConnSocket, fp);
}

#endif

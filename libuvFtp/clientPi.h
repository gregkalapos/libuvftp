//
//  clientPi.h
//  libuvftp
//
//  Created by Gergely Kalapos on 04/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_clientPi_h
#define libuvftp_clientPi_h

#include <string>
#include "uv.h"
#include <iostream>
#include "connect.h"
#include "ftpCommand.h"


class clientPi {
    static uv_tcp_t* controlConnSocket;
    static uv_tcp_t* dataConnSocket;
    static void on_dataChannelConnect(uv_connect_t* req, int status);
    
public:
    static void connect(std::string _ip, int _port, void(*fp) (bool, std::string&));
    //static void execute(ftpCommand ftpCommand); //TODO: does this make sense?
    static void executeUser(std::string userName, void(*fp) (bool, std::string&));
    static void executePasv(void(*fp) (bool, std::string&));
	static void executeList(void(*controlChannelCb) (bool, std::string&), void(*dataChannelCb) (bool, std::string&));
};


#endif

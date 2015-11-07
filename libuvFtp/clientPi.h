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
#include <iostream>
#include "connect.h"
#include "ftpCommand.h"


class clientPi {
    static uv_tcp_t* controlConnSocket;
    static uv_tcp_t* dataConnSocket;
    
public:
    static void connect(std::string _ip, int _port, void(*fp) (bool, std::string&));
    //static void execute(ftpCommand ftpCommand); //TODO: does this make sense?
    static void executeUser(std::string userName, void(*fp) (bool, std::string&));
    static void executePasv(void(*fp) (bool, std::string&));
	static void executeList(void(*controlChannelCb) (bool, std::string&), void(*dataChannelCb) (bool, std::string&));
	static void executePwd(void(*fp) (bool, std::string&));
	static void executeType(std::string type, void(*fp) (bool, std::string&));
	static void executePass(std::string password, void(*fp) (bool, std::string&));
};


#endif

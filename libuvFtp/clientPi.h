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
    static uv_tcp_t* socket;// = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    
public:
    static void connect(std::string _ip, int _port, void(*fp) (bool, std::string&));
    static void execute(ftpCommand ftpCommand); //TODO: does this make sense?
    static void executeUser(void(*fp) (bool, std::string&));
    static void executePasv(void(*fp) (bool, std::string&));
};


#endif

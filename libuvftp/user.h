//
//  user.h
//  libuvftp
//
//  Created by Gergely Kalapos on 04/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_user_h
#define libuvftp_user_h

#include "ftpCommand.h"

class user: public ftpCommand {
    static char* chr;
    static void writeCb(uv_write_t* req, int status);
    static bool isEndOfSuccessMsg(std::string text);
    static std::string result;
    
    static void processPartialResult(std::string);
    
public:
    static void run(uv_stream_t* socket, void(*fp)(bool, std::string&), std::string userName);
};

#endif

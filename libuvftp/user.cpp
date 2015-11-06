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

std::string user::result = "";

void user::processPartialResult(std::string partialResult)
{
    result += partialResult;
}

bool user::isEndOfSuccessMsg(std::string text)
{
    return text.find("230 Login successful") != std::string::npos || text.find("331 Password required for anonymous") != std::string::npos;
}

void user::run(uv_stream_t* socket, void(*fp)(bool, std::string&), std::string userName)
{
    ftpCommand::ReadFinishedCB = fp;
    ftpCommand::finishReading = isEndOfSuccessMsg;
    
    std::string tmpStr = "USER " + userName + "\n";

	InitWriteRead(socket, tmpStr);
}
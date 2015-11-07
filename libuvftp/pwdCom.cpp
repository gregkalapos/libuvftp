#ifndef libuvftp_pwdCom_cpp
#define libuvftp_pwdCom_cpp

#include "pwdCom.h"


void pwd::run(uv_stream_t* socket, void(*fp)(bool, std::string&))
{
	ftpCommand::ReadFinishedCB = fp;
	std::string cmd = "PWD \n";

	InitWriteRead(socket, cmd);
}

pwd::pwd()
{
}


pwd::~pwd()
{
}

#endif
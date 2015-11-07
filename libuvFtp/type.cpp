#ifndef libuvftp_type_cpp
#define libuvftp_type_cpp

#include "type.h"

type::type()
{
}


type::~type()
{
}

void type::run(std::string type, uv_stream_t* socket, void(*fp)(bool, std::string&))
{
	ftpCommand::ReadFinishedCB = fp;
	std::string cmd = "TYPE " + type + " \n";	
	InitWriteRead(socket, cmd);
}

#endif
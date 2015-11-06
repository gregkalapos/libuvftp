#include "Pass.h"



Pass::Pass()
{
}


Pass::~Pass()
{
}


void Pass::run(std::string password, uv_stream_t* socket, void(*fp)(bool, std::string&))
{
	std::string cmd = "PASS " + password + "\n";

	ftpCommand::ReadFinishedCB = fp;
	ftpCommand::InitWriteRead(socket, cmd);
}

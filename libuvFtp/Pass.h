#pragma once
#include "ftpCommand.h"
class Pass :
	public ftpCommand
{
public:

	static void run(std::string password, uv_stream_t* socket, void(*fp)(bool, std::string&));
	Pass();
	~Pass();
};


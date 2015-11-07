#ifndef libuvftp_pass_h
#define libuvftp_pass_h


#include "ftpCommand.h"
class Pass :
	public ftpCommand
{
public:

	static void run(std::string password, uv_stream_t* socket, void(*fp)(bool, std::string&));
	Pass();
	~Pass();
};

#endif

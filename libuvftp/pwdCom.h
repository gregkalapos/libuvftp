#ifndef libuvftp_pwdCom_h
#define libuvftp_pwdCom_h

#include "ftpCommand.h"

class pwd: public ftpCommand
{
public:
	static void run(uv_stream_t* socket, void(*fp)(bool, std::string&));

	pwd();
	~pwd();
};

#endif
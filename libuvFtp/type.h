#ifndef libuvftp_type_h
#define libuvftp_type_h

#include "ftpCommand.h"


class type :
	public ftpCommand
{
public:

 	static void run(std::string type, uv_stream_t* socket, void(*fp)(bool, std::string&));
	type();
	~type();
};

#endif
#ifndef libuvftp_list_h
#define libuvftp_list_h

#include "ftpCommand.h"

class list: public ftpCommand
{
private:
	static uv_stream_t* controlChannel;
	static uv_tcp_t* dataChannel;

public:
	list();
	~list();

	static void run(uv_stream_t* controlChannelSocket, void(*controlChannelReturn)(bool, std::string&), uv_tcp_t* _dataChannelSocket, void(*dataChannelReturn)(bool, std::string&));
};

#endif

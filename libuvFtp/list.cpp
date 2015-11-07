#ifndef libuvftp_list_cpp
#define libuvftp_list_cpp

#include "list.h"


uv_stream_t* list::controlChannel = nullptr;
uv_tcp_t* list::dataChannel = nullptr;


list::list()
{
}


list::~list()
{
}

void list::run(uv_stream_t* controlChannelSocket, void(*controlChannelReturn)(bool, std::string&), uv_tcp_t* _dataChannelSocket, void(*dataChannelReturn)(bool, std::string&))
{
	ftpCommand::ReadFinishedCB = controlChannelReturn;	
	    
	controlChannel = controlChannelSocket;
	dataChannel = _dataChannelSocket;

	std::string commandStr = "LIST \n";
	
	InitWriteRead(controlChannel, commandStr);    
}

#endif
#ifndef libuvftp_list_cpp
#define libuvftp_list_cpp

#include "list.h"

void alloc_buffer_list(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

uv_stream_t* list::controlChannel = nullptr;
passiveDataChannelConnection* list::dataChannel = nullptr;

void(*list::controlChannelUserCallback)(bool, std::string&) = nullptr;

std::string list::partialResponse = "";

void list::processPartialresponse(std::string _partialResponse)
{
    partialResponse += _partialResponse;
    
    if(_partialResponse.find("150") != std::string::npos)
    {
        ftpCommand::ConnectAndReadFromStream(*dataChannel);
    }
}

bool list::isCommandFinished(std::string response)
{
    return response.find("226") != std::string::npos;
}

void list::readingFinished(bool success, std::string& response)
{
     controlChannelUserCallback(success, partialResponse);
}

list::list()
{
}

list::~list()
{
}

void list::run(uv_stream_t* controlChannelSocket, void(*controlChannelReturn)(bool, std::string&), passiveDataChannelConnection& _dataChannel, void(*dataChannelReturn)(bool, std::string&))
{
	ftpCommand::ReadFinishedCB = readingFinished;
    ftpCommand::finishReading = isCommandFinished;
    ftpCommand::processResonse = processPartialresponse;
    
    controlChannelUserCallback = controlChannelReturn;
    
	controlChannel = controlChannelSocket;
	dataChannel = &_dataChannel;

	std::string commandStr = "LIST \n";
	
	InitWriteRead(controlChannel, commandStr);    
}

#endif
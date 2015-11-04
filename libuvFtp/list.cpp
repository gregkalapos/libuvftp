#include "list.h"



list::list()
{
}


list::~list()
{
}

void list::writeListPasvCb(uv_write_t* req, int status)
{

}

void list::run(uv_stream_t* controlChannelSocket, void(*controlChannelReturn)(bool, std::string&), uv_tcp_t* _dataChannelSocket, void(*dataChannelReturn)(bool, std::string&))
{
	ftpCommand::stringReadCB = controlChannelReturn;
	
	//ftpCommand::processResonse = connectToDataChannel;
	
	//ftpCommand::finishReading = isEndOfSuccessMsg;
	controlChannel = controlChannelSocket;
	dataChannel = _dataChannelSocket;

	uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
	char c[] = "LIST \n";
	uv_buf_t wrbuf = uv_buf_init(c, 15);

	uv_write(req, controlChannel, &wrbuf, 1, writeListPasvCb);
}
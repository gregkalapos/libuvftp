#ifndef libuvftp_list_h
#define libuvftp_list_h

#include "ftpCommand.h"

class list: public ftpCommand
{
private:
	static uv_stream_t* controlChannel;
	static uv_tcp_t* dataChannel;
    static bool isCommandFinished(std::string response);
    //called when all the resonses are already processed. It passes the responses to the callback provided by the caller
    static void readingFinished(bool success, std::string& response);
    
    //points to the callback which is triggered when the operation is done
    static void(*controlChannelUserCallback)(bool, std::string&);
    
    static void processPartialresponse(std::string _partialResponse);
    
    static std::string partialResponse;
public:
	list();
	~list();

	static void run(uv_stream_t* controlChannelSocket, void(*controlChannelReturn)(bool, std::string&), uv_tcp_t* _dataChannelSocket, void(*dataChannelReturn)(bool, std::string&));
};

#endif

#ifndef libuvftp_list_h
#define libuvftp_list_h

#include "ftpCommand.h"

class list: public ftpCommand
{
private:
	static uv_stream_t* controlChannel;
	static passiveDataChannelConnection* dataChannel;
    static bool isCommandFinished(std::string response);
    //called when all the resonses are already processed. It passes the responses to the callback provided by the caller
    static void readingFinished(bool success, std::string& response);
    
    //points to the callback which is triggered when the operation is done
    static void(*controlChannelUserCallback)(bool, std::string&);
    
    static void processPartialresponse(std::string _partialResponse);
    
    static std::string partialResponse;

	static bool isFinished;
	static bool isDataChannelFinished(std::string line);
public:
	list();
	~list();

	static void run(uv_stream_t* controlChannelSocket, void(*controlChannelReturn)(bool, std::string&), passiveDataChannelConnection& _dataChannel, void(*dataChannelReturn)(bool, std::string&));
};

#endif

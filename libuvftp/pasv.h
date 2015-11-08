//
//  pasv.h
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_pasv_h
#define libuvftp_pasv_h

#include "ftpCommand.h"

class pasv: public ftpCommand {
    
    static void connectToDataChannel(std::string response);
    static passiveDataChannelConnection* dataChannelSocket;
    static void onConnectToDataChannel(uv_connect_t* req, int status);

	static bool isEndOfSuccessMsg(std::string text);
public:
    static void run(uv_stream_t* controlChannelSocket, void(*fp)(bool, std::string&), passiveDataChannelConnection& _dataChannelSocket);
};

#endif

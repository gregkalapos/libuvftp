//
//  fto.h
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#include "ftpCommand.h"

void(*ftpCommand::stringReadCB) (bool success, std::string &response) = nullptr;
bool(*ftpCommand::finishReading)(std::string lineRead) = nullptr;
void (*ftpCommand::processResonse)(std::string response) = nullptr;

void ftpCommand::on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread < 0) {
        if (nread != UV_EOF){
            std::string str("Read error %s\n");
            stringReadCB(false, str);
        }
        //fprintf(stderr, , uv_err_name(nread));
        uv_close((uv_handle_t*) client, NULL);
        free(client);
        return;
    }
    
    char *data = (char*) malloc(sizeof(char) * (nread+1));
    data[nread] = '\0';
    strncpy(data, buf->base, nread);
    std::string str(data);
    
    auto tmp = stringReadCB;
    
    if(stringReadCB!= nullptr)
    {
        
        if(finishReading!=nullptr && finishReading(str))
        {
            stringReadCB = nullptr;
            finishReading = nullptr;
            uv_read_stop(client);
        }
        
    }
   
    free(data);
    free(buf->base);
    
    if(processResonse!=nullptr)
    {
        processResonse(str);
    }
    
    if(tmp != nullptr)
        tmp(true, str);
}
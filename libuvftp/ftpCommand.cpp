//
//  fto.h
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#include "ftpCommand.h"

void(*ftpCommand::ReadFinishedCB) (bool success, std::string &response) = nullptr;
bool(*ftpCommand::finishReading)(std::string lineRead) = nullptr;
void (*ftpCommand::processResonse)(std::string response) = nullptr;


void alloc_buffer_l(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
	buf->base = (char*)malloc(suggested_size);
	buf->len = suggested_size;
}


void ftpCommand::on_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf)
{
    if (nread < 0) {
        if (nread != UV_EOF){
            std::string str("Read error %s\n");
            ReadFinishedCB(false, str);
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
        
    auto tmp = ReadFinishedCB;
    auto isReadingDone = true;
    
    
    //TODO this can be much cleaner!
    if(ReadFinishedCB!= nullptr)
    {
        if(finishReading!=nullptr)
        {
            if(finishReading(str))
            {
                ReadFinishedCB = nullptr;
                finishReading = nullptr;
                uv_read_stop(client);
            }
            else
                isReadingDone = false;
        }
    }
   
    free(data);
    free(buf->base);
    
    if(processResonse!=nullptr)
    {
        processResonse(str);
    }
    
    if(tmp != nullptr && isReadingDone)
    {
		processResonse = nullptr;
        tmp(true, str);        
    }
}


void ftpCommand::writeCb(uv_write_t* req, int status)
{
	uv_read_start(req->handle, alloc_buffer_l, on_read);
}

void ftpCommand::InitWriteRead(uv_stream_t* socket, std::string command)
{	
	uv_write_t *req = (uv_write_t *)malloc(sizeof(uv_write_t));
	char* cstr = new char[command.length() + 1];
	strcpy(cstr, command.c_str());

	uv_buf_t wrbuf = uv_buf_init(cstr, command.length() );

	uv_write(req, socket, &wrbuf, 1, writeCb);
	delete[] cstr;
}
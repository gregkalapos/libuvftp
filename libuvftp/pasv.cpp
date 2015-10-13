//
//  pasv.cpp
//  libuvftp
//
//  Created by Gergely Kalapos on 03/10/15.
//  Copyright (c) 2015 Gergely Kalapos. All rights reserved.
//

#ifndef libuvftp_pasv_cpp
#define libuvftp_pasv_cpp

#include "pasv.h"
#include <vector>
#include <sstream>
#include <iostream>

uv_tcp_t* pasv::dataChannelSocket = nullptr;

void alloc_buffer_u2(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*)malloc(suggested_size);
    buf->len = suggested_size;
}

void pasv::onConnectToDataChannel(uv_connect_t* req, int status)
{
    if(status < 0)
    {
        std::string str = "error on connect";
        //callback(false, str);
        //TODO: report error
    }
}

void pasv::writeCbPasv(uv_write_t* req, int status)
{
    uv_read_start(req->handle, alloc_buffer_u2, on_read);
}

void pasv::run(uv_stream_t* socket, void(*fp)(bool, std::string&), uv_tcp_t* _dataChannelSocket)
{
    ftpCommand::stringReadCB = fp;
    ftpCommand::processResonse = connectToDataChannel;
    dataChannelSocket = _dataChannelSocket;
    
    uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
    char c[] = "PASV \n";
    uv_buf_t wrbuf = uv_buf_init(c, 15);
    
    uv_write(req, socket, &wrbuf, 1, writeCbPasv);
}

//parses the response of a successful pasv response and connects to the data channel 
void pasv::connectToDataChannel(std::string response)
{
    auto openParPos = response.find('(');
    auto closeParPos = response.find(')');
    
    if(openParPos!= std::string::npos && closeParPos != std::string::npos)
    {
        std::string addrWitPort = response.substr(openParPos+1, openParPos+closeParPos-1);
        std::istringstream f(addrWitPort);
        std::vector<std::string> strings;
        std::string s;
        while (getline(f, s, ',')) {
            strings.push_back(s);
        }
        
        if(strings.size() == 6)
        {
            auto ip = strings[0] + "." + strings[1] + "." + strings[2] + "." + strings[3];
            int port =  256 * std::stoi(strings[4]) + std::stoi(strings[5]);
            
            uv_tcp_init(uv_default_loop(), dataChannelSocket);
            uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));
            struct sockaddr_in dest;
            uv_ip4_addr(ip.c_str(), port, &dest);            
            uv_tcp_connect(connect, dataChannelSocket, (const struct sockaddr*)&dest, onConnectToDataChannel);
        }
    }
    
}

#endif

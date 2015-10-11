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
    
     static void writeCbPasv(uv_write_t* req, int status);
    
public:
    static void run(uv_stream_t* socket, void(*fp)(bool, std::string&));
};

#endif

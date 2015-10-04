#pragma comment (lib, "libuv.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Iphlpapi.lib")


#include "connect.h"

int couter;

void cb(bool b)
{    
    std::cout << b;
}

int main() {
    
    std::string ret;
   
    connect::startConnect("208.118.235.20", 21, [](bool b, std::string& c){
        std::cout << c;
    });
    
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    
    return 0;
}
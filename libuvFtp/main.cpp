#pragma comment (lib, "libuv.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Iphlpapi.lib")


#include "clientPi.h"
#include "user.h"

int couter;

void cb(bool b)
{    
    std::cout << b;
}

int main() {
    
    std::string ret;

    clientPi::connect("208.118.235.20", 21, [](bool succ, std::string& c){
        if(succ)
        {
            std::cout << c;
            clientPi::executeUser("anonymous", [](bool succ, std::string& c){
                if(succ)
                    std::cout << c;
                
                    if(c.find("Login successful") != std::string::npos)
                    {
                        clientPi::executePasv([](bool succ, std::string& c){
                            std::cout << c;
                            
                            clientPi::executeList([](bool succ, std::string &c){
                                
                                std::cout << c;
                                //control channel cb
                            
                            }, [](bool succ, std::string& c){
                                
                            });
                        });
                    };
            });
        }
    });
    

    
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    
    return 0;
}
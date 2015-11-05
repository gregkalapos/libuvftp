#pragma comment (lib, "libuv.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "Iphlpapi.lib")


#include "clientPi.h"
#include "user.h"

int main() {
    
    std::string ret;

    clientPi::connect("208.118.235.20", 21, [](bool succ, std::string& c){
        if(succ)
        {
            std::cout << c;
            clientPi::executeUser("anonymous", [](bool succ, std::string& c){
                if(succ)
                    std::cout << c; //after this expect: 230 Login successful.
                        clientPi::executePasv([](bool succ, std::string& c){
                            std::cout << c;
                            
                            clientPi::executeList([](bool succ, std::string &c){
                                
                                std::cout << c;
                                //control channel cb
                            
                            }, [](bool succ, std::string& c){
                                //data channel cb
                            });
                        });
            });
        }
    });   
    
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
    uv_loop_close(uv_default_loop());
    
    return 0;
}
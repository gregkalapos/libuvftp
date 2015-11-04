#include "list.h"



list::list()
{
}


list::~list()
{
}


void list::run(uv_stream_t* controlChannelSocket, void(*controlChannelReturn)(bool, std::string&), uv_tcp_t* _dataChannelSocket, void(*dataChannelReturn)(bool, std::string&))
{

}
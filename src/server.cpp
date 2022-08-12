#include "server.hpp"

namespace serverAsync
{
    server::server(string&& address, const int port) : address(address), port(port) 
    {
    }

    server::~server()
    {
    }
}
#include "server.hpp"

namespace serverAsync
{
    server::server(string&& address, const int port) 
    : address(address), port(port) 
    {
        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;


        std::cout << this->address << " hi " << '\n';
    }

    server::~server()
    {
    }
}
#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <string>
using std::string;

#include <iostream>
#include <vector>
using std::vector;

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8887"

namespace client
{
    struct addr
    {
       string address;
       int port;
    };

    class client
    {
        private:
           std::unique_ptr<SOCKET> sk;
           vector<client> clients;
        public:
            client(SOCKET * sk);
            ~client();
            addr getDataSocket();
            void* get_in_addr(struct sockaddr *);
        };
}
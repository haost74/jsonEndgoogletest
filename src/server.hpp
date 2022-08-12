#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

#include <string>
#include <iostream>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

namespace serverAsync
{
    using std::string;
    class server
    {
        private:
            const string address;
            const string port;

            WSADATA wsaData;
            int iResult;

            SOCKET ListenSocket = INVALID_SOCKET;
            SOCKET ClientSocket = INVALID_SOCKET;

            int iSendResult;
            char recvbuf[DEFAULT_BUFLEN];
            int recvbuflen = DEFAULT_BUFLEN;
            struct addrinfo *result = NULL;
            struct addrinfo hints;

        public:
            server(string&& address, string&& port);
            ~server();
    };
}

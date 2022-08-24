#include "server.hpp"

namespace serverAsync
{

   string server::getAddr()
   {
     // Init WinSock
        WSADATA wsa_Data;
        int wsa_ReturnCode = WSAStartup(0x101,&wsa_Data);

        // Get the local hostname
        char szHostName[255];
        gethostname(szHostName, 255);
        struct hostent *host_entry;
        host_entry=gethostbyname(szHostName);
        char * szLocalIP;
        szLocalIP = inet_ntoa (*(struct in_addr *)*host_entry->h_addr_list);
        string res(szLocalIP);
        WSACleanup();
        return res;
   }

    server::server(string&& address, string&& port) 
    : address(address), port(port) 
    {
      auto str = getAddr();

       std::cout << "start server address = " << str << " port = " << port << '\n';

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

         // Resolve the server address and port
        iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
        if ( iResult != 0 ) {
            printf("getaddrinfo failed with error: %d\n", iResult);
            WSACleanup();
        }

         // Create a SOCKET for the server to listen for client connections.
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (ListenSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
        }

        // Setup the TCP listening socket
        iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
        }

        freeaddrinfo(result);

         iResult = listen(ListenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
        }

        while (true)
        {                   
        
            // Accept a client socket
            ClientSocket = accept(ListenSocket, NULL, NULL);
            if (ClientSocket == INVALID_SOCKET) {
                printf("accept failed with error: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
            }

             taskloop::task_system ts;
             ts.async_([this]{client();});
        }

         WSACleanup();
        
    }

    void server::client()
    {
        auto sk = new SOCKET(ClientSocket);
        ClientSocket = INVALID_SOCKET;
        struct sockaddr_in  sockaddr;
        int namelen = sizeof(sockaddr);
        auto ind = getpeername( *sk, (struct sockaddr *)&sockaddr, &namelen);
        if(!ind)
        {
           printf("Peer Name: %s\n", inet_ntoa((in_addr)(* (in_addr*)&sockaddr.sin_addr.S_un.S_addr)));
           printf("Port Numer: %d\n", sockaddr.sin_port);
        }

        // --- No longer need server socket
        //closesocket(ListenSocket);

         // Receive until the peer shuts down the connection
        do {
            memset(recvbuf, 0, recvbuflen);
            iResult = recv(*sk, recvbuf, recvbuflen, 0);
            if (iResult > 0) {
                printf("Bytes received: %d\n", iResult);

            std::string stre(recvbuf);

            std::cout << stre << '\n';

            // Echo the buffer back to the sender
                iSendResult = send( *sk, recvbuf, iResult, 0 );
                //iSendResult = sendall(sk, recvbuf, &iResult);
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(*sk);
                    WSACleanup();
                }
                    printf("Bytes sent: %d\n", iSendResult);
                }
                else if (iResult == 0)
                    printf("Connection closing...\n");
                else  {
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(*sk);
                    WSACleanup();
                }

             } while (iResult > 0);

              // shutdown the connection since we're done
            iResult = shutdown(*sk, SD_SEND);
            if (iResult == SOCKET_ERROR) {
                printf("shutdown failed with error: %d\n", WSAGetLastError());
                closesocket(*sk);
                WSACleanup();
            }

            // cleanup
            closesocket(*sk);
            delete sk;
    }
    
       int server::sendall(SOCKET* s, char *buf, int *len)
        {
            int total = 0;        // how many bytes we've sent
            int bytesleft = *len; // how many we have left to send
            int n;

            while(total < *len) {
                n = send(*s, buf+total, bytesleft, 0);
                if (n == -1) { break; }
                total += n;
                bytesleft -= n;
            }

            *len = total; // return number actually sent here

            return n==-1?-1:0; // return -1 onm failure, 0 on success
        } 

    server::~server()
    {
    }
}
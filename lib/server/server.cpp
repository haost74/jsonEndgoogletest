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


        // Accept a client socket
        ClientSocket = accept(ListenSocket, NULL, NULL);
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
        }


        struct sockaddr_in  sockaddr;
        int namelen = sizeof(sockaddr);
        auto ind = getpeername( ClientSocket, (struct sockaddr *)&sockaddr, &namelen);
        if(!ind)
        {
           printf("Peer Name: %s\n", inet_ntoa((in_addr)(* (in_addr*)&sockaddr.sin_addr.S_un.S_addr)));
           printf("Peer Name: %d\n", sockaddr.sin_port);
        }

        /*
        

sockaddr_in sa = {0}; 
socklen_t sl = sizeof(sa);
if (getpeername(sd, (sockaddr *) &sa,  &sl))
  perror("getpeername() failed");
else
  printf("peer is: %s:%hu\n", inetntoa(sa.sinaddr), ntohs(sa.sin_port));
        
        */
        

        // No longer need server socket
        closesocket(ListenSocket);

         // Receive until the peer shuts down the connection
        do {

            iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
            if (iResult > 0) {
                printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
                iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
                if (iSendResult == SOCKET_ERROR) {
                    printf("send failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }
                    printf("Bytes sent: %d\n", iSendResult);
                }
                else if (iResult == 0)
                    printf("Connection closing...\n");
                else  {
                    printf("recv failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                }

             } while (iResult > 0);

              // shutdown the connection since we're done
            iResult = shutdown(ClientSocket, SD_SEND);
            if (iResult == SOCKET_ERROR) {
                printf("shutdown failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
            }

            // cleanup
            closesocket(ClientSocket);
            WSACleanup();

        
    }

    server::~server()
    {
    }
}
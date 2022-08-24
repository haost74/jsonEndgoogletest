#include "client.hpp"

namespace client
{

   addr client::getDataSocket()
    {
         struct sockaddr_in  sockaddr;
        int namelen = sizeof(sockaddr);
        auto ind = getpeername( *sk, (struct sockaddr *)&sockaddr, &namelen);
        // if(!ind)
        // {
        //    printf("Peer Name: %s\n", inet_ntoa((in_addr)(* (in_addr*)&sockaddr.sin_addr.S_un.S_addr)));
        //    printf("Port Numer: %d\n", sockaddr.sin_port);
        // }

        addr adr;
        adr.address = inet_ntoa((in_addr)(* (in_addr*)&sockaddr.sin_addr.S_un.S_addr));
       
        adr.port = sockaddr.sin_port;

        return adr;
    }

    // get sockaddr, IPv4 or IPv6:
    void* client::get_in_addr(struct sockaddr *sa)
    {
        if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }

    client::client(SOCKET* sk): sk(std::make_unique<SOCKET>(*sk))
    {
    }
    
    client::~client()
    {
    }
}
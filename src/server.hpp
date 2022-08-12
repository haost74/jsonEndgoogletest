#pragma once

#include <string>

namespace serverAsync
{
    using std::string;
    class server
    {
        private:
            const string address;
            const unsigned port;
        public:
            server(string&& address, const int port);
            ~server();
    };
}

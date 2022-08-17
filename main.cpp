#include <iostream>
#include <string>
#include <thread>
#include <json/json.h>
#include <gtest/gtest.h>
#include "lib/server/server.hpp"

using std::string;
using std::cout;

//  test-netconnection 192.168.224.211 -port 8887  

int main(int argc, char** argv)
{

    Json::Value root;   // starts as "null"; will contain the root value after parsing

    root["encoding"] = "UTF-8";
    root["indent"]["length"] = "Some text";     
    root["indent"]["use_space"] = "Some user_space text";
    root["indent"]["id"] = 1;
    // std::cout << root << "\n";

    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(root);

    // std::cout << output << '\n';


    std::thread th([](){
          string address = "127.0.0.1";
          serverAsync::server sr(std::move(address), "8887");
    });

    th.join();

    return 0;
}
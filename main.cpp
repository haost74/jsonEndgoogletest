#include <iostream>
#include <string>
#include <json/json.h>
#include <gtest/gtest.h>
#include "src/server.hpp"

using std::string;
using std::cout;

int main(int argc, char** argv)
{

    // Json::Value root;   // starts as "null"; will contain the root value after parsing

    // root["encoding"] = "UTF-8";
    // root["indent"]["length"] = "Some text";     
    // root["indent"]["use_space"] = "Some user_space text";
    // root["indent"]["id"] = 1;
    // std::cout << root << "\n";

    string address = "172.0.0.1";
    serverAsync::server sr(std::move(address), 10);
    

    return 0;
}
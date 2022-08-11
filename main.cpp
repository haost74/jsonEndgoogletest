#include <iostream>
#include <json/json.h>
#include <gtest/gtest.h>


int main(int argc, char** argv)
{

    Json::Value root;   // starts as "null"; will contain the root value after parsing

    root["encoding"] = "UTF-8";
    root["indent"]["length"] = "Some text";     
    root["indent"]["use_space"] = "Some user_space text";
    root["indent"]["id"] = 1;
    std::cout << root << "\n";

    return 0;
}
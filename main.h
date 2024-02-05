#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
using std::cout;
using std::endl;
using std::string;
const string loginUser();
const string registerUser();
const string showAllUser();
const string showUser();
const string loginToken();
const string updateUser();
const string deleteUser();
#endif
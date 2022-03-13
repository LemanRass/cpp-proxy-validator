// cpp-proxy-validator2.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <curl/curl.h>
#include "ProxyList.h"
#include "Logger.h"
using namespace std;

struct Request
{
    CURL* curl;
    long code;
};

// TODO: Reference additional headers your program requires here.

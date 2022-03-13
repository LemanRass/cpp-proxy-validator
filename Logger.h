//
// Created by Ruslan on 11.03.2022.
//

#ifndef PROXYCHECKER_LOGGER_H
#define PROXYCHECKER_LOGGER_H

#include <iostream>
#include <mutex>

using namespace std;

class Logger {

public:
    static void Log(string msg);

};


#endif //PROXYCHECKER_LOGGER_H

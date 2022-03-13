//
// Created by Ruslan on 06.03.2022.
//

#include "Logger.h"

mutex m;

void Logger::Log(string msg) {

    lock_guard<mutex>lock(m);
    cout << msg << endl;
}
//
// Created by Ruslan on 11.03.2022.
//

#ifndef DDOS_PROXYLIST_H
#define DDOS_PROXYLIST_H

#include <iostream>
#include <vector>
using namespace std;

class ProxyList {

public:
    static void Init();
    static vector<string> GetProxies();
};


#endif //DDOS_PROXYLIST_H

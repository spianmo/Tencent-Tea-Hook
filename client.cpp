//
// Created by Administrator on 2022/4/13.
//

#include "httplib.h"
#include <iostream>

#define HOST "localhost:8787"
using namespace std;
using namespace httplib;

int main() {
//    Client cli(HOST);
//    cli.Post("/obtain", "66666", "text/plain");
    system("chcp 65001");
    stringstream ss;
    ss << "==================客户端发包==================" << endl;
    cout << ss.str() << endl;
    return 0;
}
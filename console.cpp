//
//  sample.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <chrono>
#include <cstdio>
#include "httplib.h"

using namespace httplib;
using namespace std;

std::string dump_headers(const Headers &headers) {
    std::string s;
    char buf[BUFSIZ];

    for (auto it = headers.begin(); it != headers.end(); ++it) {
        const auto &x = *it;
        snprintf(buf, sizeof(buf), "%s: %s\n", x.first.c_str(), x.second.c_str());
        s += buf;
    }

    return s;
}

std::string log(const Request &req, const Response &res) {
    std::string s;
    char buf[BUFSIZ];

    s += "================================\n";

    snprintf(buf, sizeof(buf), "%s %s %s", req.method.c_str(),
             req.version.c_str(), req.path.c_str());
    s += buf;

    std::string query;
    for (auto it = req.params.begin(); it != req.params.end(); ++it) {
        const auto &x = *it;
        snprintf(buf, sizeof(buf), "%c%s=%s",
                 (it == req.params.begin()) ? '?' : '&', x.first.c_str(),
                 x.second.c_str());
        query += buf;
    }
    snprintf(buf, sizeof(buf), "%s\n", query.c_str());
    s += buf;

    s += dump_headers(req.headers);

    s += "--------------------------------\n";

    snprintf(buf, sizeof(buf), "%d %s\n", res.status, res.version.c_str());
    s += buf;
    s += dump_headers(res.headers);
    s += "\n";

    if (!res.body.empty()) { s += res.body; }

    s += "\n";

    return s;
}


enum PacketProto {
    oi_symmetry_encrypt2, oi_symmetry_decrypt2
};

std::map<std::string, PacketProto> packetProtoMap;

class BasePacket {
public:
    PacketProto type;
    string key;
    string encrypt;
    string decrypt;

    explicit BasePacket(const string &data);

    [[nodiscard]] string format() const;

private:
    static std::vector<std::string> stringSplit(const std::string &str, char delim);
};

BasePacket::BasePacket(const string &data) {
    vector<string> lines = stringSplit(data, 10);
    this->type = packetProtoMap[lines[0]];
    this->key = lines[1];
    this->decrypt = lines[2];
    this->encrypt = lines[3];
}

std::vector<std::string> BasePacket::stringSplit(const std::string &str, char delim) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
}

string BasePacket::format() const {
    stringstream ss;
    ss << ((this->type == oi_symmetry_encrypt2) ? "oi_symmetry_encrypt2" : "oi_symmetry_decrypt2") << endl;
    ss << this->key << endl;
    ss << this->encrypt << endl;
    ss << this->decrypt << endl;
    return ss.str();
}

int main(int argc, char *argv[]) {
    system("chcp 65001");
    Server svr;

    if (!svr.is_valid()) {
        printf("server has an error...\n");
        return -1;
    }

    svr.Get("/", [=](const Request & /*req*/, Response &res) {
        res.set_redirect("/obtain");
    });

    svr.Post("/obtain", [](const Request &req, Response &res) {
        BasePacket packet = BasePacket(req.body);
        cout << packet.format() << endl;
    });

    svr.set_error_handler([](const Request & /*req*/, Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });

    svr.set_logger([](const Request &req, const Response &res) {
        //printf("%s", log(req, res).c_str());
    });

    svr.listen("localhost", 8787);
    return 0;
}
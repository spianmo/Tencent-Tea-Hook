//
//  sample.cc
//
//  Copyright (c) 2019 Yuji Hirose. All rights reserved.
//  MIT License
//

#include <chrono>
#include "httplib.h"
#include "log.h"
#include "ban.h"
#include "ProtoParser.h"

using namespace httplib;
using namespace std;
using namespace logger;

enum PacketProto {
    oi_symmetry_encrypt2, oi_symmetry_decrypt2
};

std::map<std::string, PacketProto> packetProtoMap = {
        {"oi_symmetry_encrypt2", oi_symmetry_encrypt2},
        {"oi_symmetry_decrypt2", oi_symmetry_decrypt2}
};


class BasePacket {
public:
    PacketProto type;
    string key;
    string encrypt;
    string decrypt;

    explicit BasePacket(const string &data);

    [[nodiscard]] string format() const;
    void log() const;

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

void BasePacket::log() const {
    success("MAIN", ((this->type == oi_symmetry_encrypt2) ? "oi_symmetry_encrypt2" : "oi_symmetry_decrypt2"));
    warn("SIGNAL", this->key);
    info("MAIN", this->encrypt);
    info("QUEUE", this->decrypt);
}

int main(int argc, char *argv[]) {
    system("chcp 65001");
    char banner[256] = {'\0'};
    BAN(argv[0], banner, 256);
    cout << "\n"
            "_____._._______.______       .___.__  ._______  ._______  .____/\\      .________._______.______  .___     ._______.______  \n"
            "\\__ _:|: .____/:      \\      :   |  \\ : .___  \\ : .___  \\ :   /  \\     |    ___/: .____/: __   \\ |   |___ : .____/: __   \\ \n"
            "  |  :|| : _/\\ |   .   |     |   :   || :   |  || :   |  ||.  ___/     |___    \\| : _/\\ |  \\____||   |   || : _/\\ |  \\____|\n"
            "  |   ||   /  \\|   :   |     |   .   ||     :  ||     :  ||     \\      |       /|   /  \\|   :  \\ |   :   ||   /  \\|   :  \\ \n"
            "  |   ||_.: __/|___|   |     |___|   | \\_. ___/  \\_. ___/ |      \\     |__:___/ |_.: __/|   |___\\ \\      ||_.: __/|   |___\\\n"
            "  |___|   :/       |___|         |___|   :/        :/     |___\\  /        :        :/   |___|      \\____/    :/   |___|    \n"
            "                                         :         :           \\/                                                          \n"
            "  Version 0.01  © 2022 Finger. All Rights Reserved.\n";
    cout << "  " << banner << endl << endl << endl;
    Server svr;

    if (!svr.is_valid()) {
        cout << "server has an error" << endl;
        return -1;
    }

    svr.Post("/obtain", [](const Request &req, Response &res) {
        BasePacket packet = BasePacket(req.body);
        //packet.log();
        parsePacket(packet.type, packet.decrypt);
    });

    svr.listen("localhost", 8787);
    return 0;
}
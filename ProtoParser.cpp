//
// Created by Administrator on 2022/4/15.
//

#include "ProtoParser.h"

//hex to int
int hexToInt(const char *hex) {
    int len = strlen(hex);
    int result = 0;
    for (int i = 0; i < len; i++) {
        char c = hex[i];
        if (c >= '0' && c <= '9') {
            result = result * 16 + (c - '0');
        } else if (c >= 'a' && c <= 'f') {
            result = result * 16 + (c - 'a' + 10);
        } else if (c >= 'A' && c <= 'F') {
            result = result * 16 + (c - 'A' + 10);
        }
    }
    return result;
}

//substring
char *substring(const char *str, int start, int end) {
    int len = end - start;
    char *result = new char[len + 1];
    for (int i = 0; i < len; i++) {
        result[i] = str[start + i];
    }
    result[len] = '\0';
    return result;
}

//substring
char *substring(const char *str, int start) {
    int len = strlen(str) - start;
    char *result = new char[len + 1];
    for (int i = 0; i < len; i++) {
        result[i] = str[start + i];
    }
    result[len] = '\0';
    return result;
}

//hex2utf8
char *hex2utf8(const char *hex) {
    int len = strlen(hex);
    int utf8Len = len / 2;
    char *utf8 = new char[utf8Len + 1];
    for (int i = 0; i < utf8Len; i++) {
        int code = hexToInt(substring(hex, i * 2, i * 2 + 2));
        utf8[i] = (char) code;
    }
    utf8[utf8Len] = '\0';
    return utf8;
}

//format timestamp
char *formatTimestamp(int timestamp) {
    time_t time = timestamp;
    struct tm *tm = localtime(&time);
    char *result = new char[20];
    sprintf(result, "%04d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec);
    return result;
}


void parsePacket(int type, const string& hexStr) {
    if (type == 0) {
        stringstream ss;
        unsigned long long senderUin = hexToInt(substring(hexStr.c_str(), 0, 8));
        unsigned long long receiverUin = hexToInt(substring(hexStr.c_str(), 8, 16));
        string msgContent = substring(hexStr.c_str(), 232, hexStr.length());
        cout << "发送消息oi_symmetry_encrypt2" << endl;
        cout << "hexStr: " << hexStr << endl;
        cout << "senderUin: " << senderUin << endl;
        cout << "receiverUin: " << receiverUin << endl;
        cout << "msgContentRaw: " << msgContent.c_str() << endl;
        cout << "msgContent: " << hex2utf8(msgContent.c_str()) << endl;
    }
    /*else if (type == 1) {
        stringstream ss;
        unsigned long long senderUin = hexToInt(substring(hexStr.c_str(), 0, 8));
        unsigned long long receiverUin = hexToInt(substring(hexStr.c_str(), 8, 16));
        cout << "接收消息oi_symmetry_decrypt2" << endl;
        cout << "hexStr: " << hexStr << endl;
        cout << "senderUin: " << senderUin << endl;
        cout << "receiverUin: " << receiverUin << endl;
    }*/
}

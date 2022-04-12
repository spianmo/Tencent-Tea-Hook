//
// Created by Finger on 2022/4/11.
//

#include "Common.h"

BOOL SetHook(LPVOID pTarget, LPVOID pDest, LPVOID pOld) {
    MH_STATUS ret = MH_OK;

    ret = MH_CreateHook(pTarget, pDest, reinterpret_cast<LPVOID *>(pOld));
    if (ret != MH_OK) {
        return FALSE;
    }

    if ((ret = MH_EnableHook((LPVOID) pTarget)) != MH_OK) {
        return FALSE;
    }

    return TRUE;
}

BOOL UnHook(LPVOID pTarget) {
    if (MH_DisableHook(pTarget) != MH_OK)
        return FALSE;

    return TRUE;
}

string GBKToUTF8(string &strGBK) {
    string strOutUTF8 = "";
    WCHAR *str1;
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char *str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[]str1;
    str1 = NULL;
    delete[]str2;
    str2 = NULL;
    return strOutUTF8;
}

string UTF8ToGBK(string &strUtf8) {
    string strOutGBK = "";
    int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, NULL, 0);
    WCHAR *wszGBK = new WCHAR[len + 1];
    memset(wszGBK, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wszGBK, len);
    len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
    char *pszGBK = new char[len + 1];
    memset(pszGBK, 0, len + 1);
    WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, pszGBK, len, NULL, NULL);
    strOutGBK = pszGBK;
    delete[]pszGBK;
    delete[]wszGBK;
    return strOutGBK;
}

string binaryToHex(const char *bytes, int length) {
    string ret;
    static const char *hex = "0123456789ABCDEF";
    for (int i = 0; i < length; i++) {
        ret.push_back(hex[(bytes[i] >> 4) & 0xf]);
        ret.push_back(hex[bytes[i] & 0xf]);
    }
    return ret;
}

string binaryToHex(const unsigned char *bytes, unsigned int length) {
    std::stringstream ss;
    for (int i = 0; i < length; i++) {
        ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (0xff & (unsigned char) bytes[i]);
    }
    return ss.str();
}

string binaryToHex(const unsigned char *bytes, int length) {
    std::stringstream ss;
    for (int i = 0; i < length; i++) {
        ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (0xff & (unsigned char) bytes[i]);
    }
    return ss.str();
}

string binaryToHex(const string &binaryStr) {
    string ret;
    static const char *hex = "0123456789ABCDEF";
    for (auto c: binaryStr) {
        ret.push_back(hex[(c >> 4) & 0xf]);
        ret.push_back(hex[c & 0xf]);
    }
    return ret;
}

string hex2intToString(const std::string &hexStr) {
    char *offset;
    string result;
    stringstream ss;
    ss << strtoull(hexStr.c_str(), &offset, 16);
    ss >> result;
    return result;
}
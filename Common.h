//
// Created by Finger on 2022/4/11.
//

#ifndef TEAHOOKDLL_COMMON_H
#define TEAHOOKDLL_COMMON_H

#include <Windows.h>
#include <string>
#include <tlhelp32.h>
#include <atlstr.h>
#include <sstream>
#include <iomanip>
#include <MinHook.h>
#include "tea.h"

#define HOST "localhost:8787"

using std::wstring;
using std::string;
using namespace std;

BOOL SetHook(LPVOID pTarget, LPVOID pDest, LPVOID pOld);

BOOL UnHook(LPVOID pTarget);

string GBKToUTF8(string &strGBK);

string UTF8ToGBK(string &strUtf8);

string binaryToHex(const unsigned char *bytes, unsigned int length);

string binaryToHex(const unsigned char *bytes, int length);

string binaryToHex(const char *bytes, int length);

string binaryToHex(const string &binaryStr);

string hex2intToString(const std::string &hexStr);

#endif //TEAHOOKDLL_COMMON_H

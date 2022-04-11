#pragma once

#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>

#define oi_symmetry_encrypt2_Symbol "?oi_symmetry_encrypt2@@YAXPBEH0PAEPAH@Z"
#define oi_symmetry_decrypt2_Symbol "?oi_symmetry_decrypt2@@YAHPBEH0PAEPAH@Z"


typedef void (__cdecl* oi_symmetry_encrypt2_t)(const char *pInBuf, int nInBufLen, const char *pKey, char *pOutBuf, int *pOutBufLen);
typedef int (__cdecl* oi_symmetry_decrypt2_t)(const char *pInBuf, int nInBufLen, const char *pKey, char *pOutBuf, int *pOutBufLen);

extern oi_symmetry_encrypt2_t oi_symmetry_encrypt2;
extern oi_symmetry_decrypt2_t oi_symmetry_decrypt2;

void InitHookPtr();

bool CheckPtrValid();

extern ULONG_PTR oi_symmetry_encrypt2_Address;
extern ULONG_PTR oi_symmetry_decrypt2_Address;
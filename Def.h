#ifndef TEAHOOKDLL_DEF_H
#define TEAHOOKDLL_DEF_H

#include "httplib.h"
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
#define WSASendTo_Symbol "WSASendTo"
#define WSARecvFrom_Symbol "WSARecvFrom"


typedef void (__cdecl *oi_symmetry_encrypt2_t)(const BYTE *pInBuf, int nInBufLen, const BYTE *pKey, BYTE *pOutBuf,
                                               int *pOutBufLen);

typedef int (__cdecl *oi_symmetry_decrypt2_t)(const BYTE *pInBuf, int nInBufLen, const BYTE *pKey, BYTE *pOutBuf,
                                              int *pOutBufLen);

typedef int (__stdcall *WSASendTo_t)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent,
                                     DWORD dwFlags, const struct sockaddr *lpTo, int iToLen,
                                     LPWSAOVERLAPPED lpOverlapped,
                                     LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

typedef int (__stdcall *WSARecvFrom_t)(SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesRecvd,
                                       LPDWORD lpFlags, struct sockaddr *lpFrom, LPINT lpFromlen,
                                       LPWSAOVERLAPPED lpOverlapped,
                                       LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);

extern oi_symmetry_encrypt2_t oi_symmetry_encrypt2;
extern oi_symmetry_decrypt2_t oi_symmetry_decrypt2;
extern WSASendTo_t _WSASendTo;
extern WSARecvFrom_t _WSARecvFrom;

void InitHookPtr();

bool CheckPtrValid();

extern ULONG_PTR oi_symmetry_encrypt2_Address;
extern ULONG_PTR oi_symmetry_decrypt2_Address;
extern ULONG_PTR WSASendTo_Address;
extern ULONG_PTR WSARecvFrom_Address;

#endif //TEAHOOKDLL_DEF_H
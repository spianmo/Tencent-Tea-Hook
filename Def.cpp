#include "Def.h"

oi_symmetry_encrypt2_t oi_symmetry_encrypt2 = NULL;
ULONG_PTR oi_symmetry_encrypt2_Address = NULL;

oi_symmetry_decrypt2_t oi_symmetry_decrypt2 = NULL;
ULONG_PTR oi_symmetry_decrypt2_Address = NULL;

WSASendTo_t _WSASendTo = NULL;
ULONG_PTR WSASendTo_Address = NULL;

WSARecvFrom_t _WSARecvFrom = NULL;
ULONG_PTR WSARecvFrom_Address = NULL;

void InitHookPtr() {
    HMODULE hModule1 = GetModuleHandle("Common");
    oi_symmetry_encrypt2_Address = (ULONG_PTR) GetProcAddress(hModule1, oi_symmetry_encrypt2_Symbol);
    oi_symmetry_encrypt2 = (oi_symmetry_encrypt2_t) oi_symmetry_encrypt2_Address;

    HMODULE hModule2 = GetModuleHandle("Common");
    oi_symmetry_decrypt2_Address = (ULONG_PTR) GetProcAddress(hModule2, oi_symmetry_decrypt2_Symbol);
    oi_symmetry_decrypt2 = (oi_symmetry_decrypt2_t) oi_symmetry_decrypt2_Address;

    HMODULE hModule3 = GetModuleHandle("ws2_32");
    WSASendTo_Address = (ULONG_PTR) GetProcAddress(hModule3, WSASendTo_Symbol);
    _WSASendTo = (WSASendTo_t) WSASendTo_Address;

    HMODULE hModule4 = GetModuleHandle("ws2_32");
    WSARecvFrom_Address = (ULONG_PTR) GetProcAddress(hModule4, WSARecvFrom_Symbol);
    _WSARecvFrom = (WSARecvFrom_t) WSARecvFrom_Address;
}

bool CheckPtrValid() {
    if (oi_symmetry_encrypt2 && oi_symmetry_decrypt2 && _WSASendTo && _WSARecvFrom) {
        return true;
    }
    return false;
}

#include "Def.h"

oi_symmetry_encrypt2_t oi_symmetry_encrypt2 = NULL;
ULONG_PTR oi_symmetry_encrypt2_Address = NULL;

oi_symmetry_decrypt2_t oi_symmetry_decrypt2 = NULL;
ULONG_PTR oi_symmetry_decrypt2_Address = NULL;

void InitHookPtr() {
    HMODULE hModule1 = GetModuleHandle("Common");
    oi_symmetry_encrypt2_Address = (ULONG_PTR) GetProcAddress(hModule1, oi_symmetry_encrypt2_Symbol);
    oi_symmetry_encrypt2 = (oi_symmetry_encrypt2_t) oi_symmetry_encrypt2_Address;

    HMODULE hModule2 = GetModuleHandle("Common");
    oi_symmetry_decrypt2_Address = (ULONG_PTR) GetProcAddress(hModule2, oi_symmetry_decrypt2_Symbol);
    oi_symmetry_decrypt2 = (oi_symmetry_decrypt2_t) oi_symmetry_decrypt2_Address;
}

bool CheckPtrValid() {
    if (oi_symmetry_encrypt2 && oi_symmetry_decrypt2)
        return true;
    return false;
}

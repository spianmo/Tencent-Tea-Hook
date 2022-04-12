#include <windows.h>
#include <iostream>
#include <MinHook.h>
#include "Common.h"

#include "Def.h"


using namespace std;

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

void __cdecl my_oi_symmetry_encrypt2(const BYTE *pInBuf, int nInBufLen, const BYTE *pKey, BYTE *pOutBuf, int *pOutBufLen){
    oi_symmetry_encrypt2(pInBuf, nInBufLen, pKey, pOutBuf, pOutBufLen);
    OutputDebugString("my_oi_symmetry_encrypt2");
    //OutputDebugString(binaryToHex(pKey, 16).c_str());
    //OutputDebugString(*pOutBufLen);
    OutputDebugString(binaryToHex(pInBuf, nInBufLen).c_str());
}

void __cdecl my_oi_symmetry_decrypt2(const BYTE *pInBuf, int nInBufLen, const BYTE *pKey, BYTE *pOutBuf, int *pOutBufLen){
    //OutputDebugString("my_oi_symmetry_decrypt2");
    //OutputDebugString(binaryToHex(pKey, 16).c_str());
    //OutputDebugString(binaryToHex(pOutBuf, nInBufLen).c_str());
    oi_symmetry_decrypt2(pInBuf, nInBufLen, pKey, pOutBuf, pOutBufLen);
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH: {
            OutputDebugString("Hook Init");
            MH_Initialize();
            InitHookPtr();
            if (SetHook((LPVOID) oi_symmetry_encrypt2_Address, (LPVOID) &my_oi_symmetry_encrypt2, &oi_symmetry_encrypt2) &&
                SetHook((LPVOID) oi_symmetry_decrypt2_Address, (LPVOID) &my_oi_symmetry_decrypt2, &oi_symmetry_decrypt2)) {
                OutputDebugString("SetHook OK!");
            }
        }
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH: {
            if (UnHook((LPVOID) oi_symmetry_encrypt2_Address) &&
                UnHook((LPVOID) oi_symmetry_decrypt2_Address)) {
                OutputDebugString("UnHook OK!");
                MH_Uninitialize();
            }
        }
            break;
    }
    return TRUE;
}
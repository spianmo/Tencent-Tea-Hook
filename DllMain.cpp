#include <windows.h>
#include <iostream>
#include "Common.h"

#include "Def.h"


using namespace std;

void __cdecl my_oi_symmetry_encrypt2(const BYTE *pInBuf, int nInBufLen, const BYTE *pKey, BYTE *pOutBuf, int *pOutBufLen){
    oi_symmetry_encrypt2(pInBuf, nInBufLen, pKey, pOutBuf, pOutBufLen);
    OutputDebugString("my_oi_symmetry_encrypt2");
    //明文数据
    //OutputDebugString(binaryToHex(pInBuf, nInBufLen).c_str());
    //KEY
    //OutputDebugString(binaryToHex(pKey, 16).c_str());
    //密文数据
    OutputDebugString(binaryToHex(pOutBuf, *pOutBufLen).c_str());
    uint32_t encode_buf_len,decode_buf_len;
    unsigned char * encode_buf = tea_encode(pKey, pInBuf, nInBufLen, &encode_buf_len);
    //unsigned char * decode_buf = tea_decode(pKey,encode_buf,encode_buf_len,&decode_buf_len);
    OutputDebugString(binaryToHex(encode_buf, encode_buf_len).c_str());
    //OutputDebugString(binaryToHex(decode_buf, decode_buf_len).c_str());
}

void __cdecl my_oi_symmetry_decrypt2(const BYTE *pInBuf, int nInBufLen, const BYTE *pKey, BYTE *pOutBuf, int *pOutBufLen){
    oi_symmetry_decrypt2(pInBuf, nInBufLen, pKey, pOutBuf, pOutBufLen);
//    OutputDebugString("my_oi_symmetry_decrypt2");
//    //密文数据
//    OutputDebugString(binaryToHex(pInBuf, nInBufLen).c_str());
//    //KEY
//    OutputDebugString(binaryToHex(pKey, 16).c_str());
//    //明文数据
//    OutputDebugString(binaryToHex(pOutBuf, nInBufLen).c_str());
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
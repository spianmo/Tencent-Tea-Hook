//
// Created by Administrator on 2022/4/12.
//

#ifndef TEAHOOKDLL_TEA_H
#define TEAHOOKDLL_TEA_H

#include <cstdint>

/*
 * 描述:用qqtea来加密
 * 参数key:长度必须为16
 * 参数out_buf_len:加密后的数据长度
 * 返回值:加密后的数据，使用qqtea_free来释放
 */
unsigned char *tea_encode(const unsigned char *key, const unsigned char *buffer, uint32_t len, uint32_t *out_buf_len);

/*
 * 描述:用qqtea来解密
 * 参数key:长度必须为16
 * 参数out_buf_len:解密后的数据长度
 * 返回值:解密后的数据，使用qqtea_free来释放
 */
unsigned char *tea_decode(const unsigned char *key, const unsigned char *buffer, uint32_t len, uint32_t *out_buf_len);

/*
 * 描述:释放加解密函数返回指针指向的内存(空指针安全)
 */
void tea_free(unsigned char *buffer);

#endif //TEAHOOKDLL_TEA_H

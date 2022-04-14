#pragma once

#include <cstdint>
#include <cstdio>

#ifdef WIN32
#define BAN_EXPORT __declspec(dllexport)
#else
#define BAN_EXPORT
#endif

#define DEFAULT_TPL "@NAME@ \n  @HOSTNAME@ - @OS@ - @CORES@ - @MEM@ - @TIME@"

#define BAN(Name, Str, Length) bant(Name, DEFAULT_TPL, Str, Length)

BAN_EXPORT void bant(const char *, const char *, char *, size_t);
cmake_minimum_required(VERSION 3.10)
project(TeaHookDll)

set(CMAKE_CXX_STANDARD 14)
set(VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

set(MINHOOK_SOURCES
        minhook/src/buffer.c
        minhook/src/hook.c
        minhook/src/trampoline.c
        minhook/src/hde/hde32.c
        minhook/src/hde/hde64.c
        )

include_directories(minhook/include minhook/src minhook/src/hde)

add_library(minhook ${MINHOOK_SOURCES})

add_library(TeaHookDll SHARED DllMain.cpp Def.cpp Def.h Common.cpp Common.h)

target_link_libraries(TeaHookDll
        minhook)

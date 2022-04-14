cmake_minimum_required(VERSION 3.10)
project(TeaHookDll)

set(CMAKE_CXX_STANDARD 20)
set(VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(MINHOOK_SOURCES
        minhook/src/buffer.c
        minhook/src/hook.c
        minhook/src/trampoline.c
        minhook/src/hde/hde32.c
        minhook/src/hde/hde64.c
        )

include_directories(minhook/include minhook/src minhook/src/hde)

add_library(minhook ${MINHOOK_SOURCES})

add_library(TeaHookDll SHARED DllMain.cpp httplib.h Def.cpp Def.h Common.cpp Common.h tea.cpp tea.h)

add_executable(TeaHookServer console.cpp httplib.h log.h ban.cpp ban.h)

add_executable(TeaHookClient client.cpp httplib.h)

target_link_libraries(TeaHookDll
        minhook)

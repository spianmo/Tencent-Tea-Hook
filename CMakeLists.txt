cmake_minimum_required(VERSION 3.21)
project(TeaHookDll)

set(CMAKE_CXX_STANDARD 14)
set(VENDOR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)

add_library(MinHook STATIC IMPORTED)
include_directories(MinHook ${VENDOR}/minhook/include)
set_target_properties(MinHook PROPERTIES IMPORTED_LOCATION ${VENDOR}/minhook/lib/libMinHook-x86-v141-mdd.lib)

add_library(TeaHookDll SHARED DllMain.cpp Def.cpp Def.h)

target_link_libraries(TeaHookDll
        MinHook)

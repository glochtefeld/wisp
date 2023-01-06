cmake_minimum_required(VERSION 3.16)
project(wisp VERSION 0.1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(wisp-dev
    include/wscanner.h
    src/wscanner.c
)
target_include_directories(wisp-dev PUBLIC include)

# other libs: debug, hash, external

add_executable(wisp
    src/wisp.c
    include/wisp.h
)

target_link_libraries(wisp PRIVATE wisp-dev)
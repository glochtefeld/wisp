cmake_minimum_required(VERSION 3.16)
project(wisp VERSION 0.1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Logger Required Definitions
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
add_definitions("-DCLOGGER_USE_COLOR=1")

add_subdirectory(extern)
add_library(wisp
    include/wscanner.h
    include/wsymbol.h
    src/wscanner.c
    src/wsymbol.c
    src/wcompiler.c
)
target_include_directories(wisp PUBLIC include)

add_library(wisp-repl 
    include/wrepl.h
    src/wrepl.c
)
target_include_directories(wisp-repl PUBLIC include)
target_include_directories(wisp-repl PUBLIC extern)
target_link_libraries(wisp-repl PRIVATE linenoise)
target_link_libraries(wisp-repl PRIVATE wisp)
target_link_libraries(wisp-repl PRIVATE clogger)
# other libs: debug, hash, external

add_executable(wispr
    src/wisp.c
    include/wisp.h
)
target_link_libraries(wispr PRIVATE wisp)
target_link_libraries(wispr PRIVATE wisp-repl)
target_include_directories(wispr PUBLIC include)
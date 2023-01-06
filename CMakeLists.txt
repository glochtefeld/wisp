cmake_minimum_required(VERSION 3.16)
project(wisp VERSION 0.1.0 LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Logger Required Definitions
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")
add_definitions("-DCLOGGER_USE_COLOR=1")

add_subdirectory(extern)
add_library(wisp-dev
    include/wscanner.h
    src/wscanner.c
)
target_include_directories(wisp-dev PUBLIC include)

add_library(wisp-repl 
    include/wrepl.h
    src/wrepl.c
)
target_include_directories(wisp-repl PUBLIC include)
target_include_directories(wisp-repl PUBLIC extern)
target_link_libraries(wisp-repl PRIVATE linenoise)
target_link_libraries(wisp-repl PRIVATE wisp-dev)
target_link_libraries(wisp-repl PRIVATE clogger)
# other libs: debug, hash, external

add_executable(wisp
    src/wisp.c
    include/wisp.h
)
target_link_libraries(wisp PRIVATE wisp-dev)
target_link_libraries(wisp PRIVATE wisp-repl)
target_include_directories(wisp PUBLIC include)
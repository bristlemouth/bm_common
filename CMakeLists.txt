cmake_minimum_required(VERSION 3.29)

if(NOT ENABLE_TESTING)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)
endif()

project(BristlemouthCommon VERSION 0.11 LANGUAGES C)

include(FetchContent)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_EXTENSIONS NO)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/third_party/crc
)


if(ENABLE_TESTING)
    set(CMAKE_CXX_FLAGS "-g -Wall")
    set(CMAKE_C_FLAGS "-g -Wall -W")
    set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

    enable_testing()
    add_subdirectory("test")
else()
    set(SOURCES
        src/util.c
        src/ll.c
        src/timer_callback_handler.c
        third_party/crc/crc16.c
        third_party/crc/crc32.c
    )
    add_library(bmcommon ${SOURCES})
endif()

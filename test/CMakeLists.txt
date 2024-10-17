cmake_minimum_required(VERSION 3.29)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

include(CTest)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_Declare(
  fff
  GIT_REPOSITORY https://github.com/meekrosoft/fff.git
  GIT_TAG        5111c61
)
FetchContent_MakeAvailable(fff)

include(GoogleTest)
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/../src)
set(MOCK_DIR ${CMAKE_CURRENT_LIST_DIR}/mocks)
set(STUB_DIR ${CMAKE_CURRENT_LIST_DIR}/stubs)

include_directories(
    ${MOCK_DIR}
    ${fff_SOURCE_DIR}
    .
)

link_libraries(
    gmock
    gtest_main
)

file(GLOB TEST_STUBS stubs/*.c)

# - Create Unit Test
#
# This function creates a unit test with required source files.
# Coverage report information is compiled in for the file to be tested.
#
# test_name - the name to call the test
# srcs - list of sources necessary to build the test including the file to be tested
function(create_gtest test_name srcs)
    set(GTEST_NAME ${test_name}_test)
    add_executable(${GTEST_NAME})
    target_include_directories(${GTEST_NAME}
        PRIVATE
        ${includes})
    target_sources(${GTEST_NAME}
        PRIVATE
        ${srcs}
        src/${test_name}_test.cpp
    )
    gtest_discover_tests(${GTEST_NAME})
    # Generate artifacts for coverage report using lcov
    set_source_files_properties(${test_src} PROPERTIES
        COMPILE_FLAGS
        "-fprofile-arcs -ftest-coverage"
    )
endfunction()

#  Linked List (LL) unit tests
set (LL_TEST_SRCS
    # File we are testing
    ${SRC_DIR}/ll.c

    # Supporting files
    ${STUB_DIR}/bm_os.c
)
create_gtest("ll" "${LL_TEST_SRCS}")

#  State Machine unit tests
set (LIB_STATE_MACHINE_TEST_SRCS
    # File we are testing
    ${SRC_DIR}/lib_state_machine.c
)
create_gtest("lib_state_machine" "${LIB_STATE_MACHINE_TEST_SRCS}")

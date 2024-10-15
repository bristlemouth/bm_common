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
# test_src - test file that is to be unit tested
# srcs - list of sources necessary to build the application, if no external sources
#                are used, fill this in with the ${NONE} variable
# stubs - list of stubs that are required for the test
function(create_gtest test_name test_src srcs stubs)
    set(GTEST_NAME ${test_name}_test)
    add_executable(${GTEST_NAME})
    target_include_directories(${GTEST_NAME}
        PRIVATE
        ${includes})
    target_sources(${GTEST_NAME}
        PRIVATE
        ${srcs}
        ${test_src}
        ${stubs}
        src/${test_name}_test.cpp
    )
    gtest_discover_tests(${GTEST_NAME})
    # Generate artifacts for coverage report using lcov
    set_source_files_properties(${test_src} PROPERTIES
        COMPILE_FLAGS
        "-fprofile-arcs -ftest-coverage"
    )
endfunction()

# None variable for unit tests that require no source files (can also be used when no stubs are needed)
set(NONE src)

# Create a list of stubs for the next unit test
set (STUBS
    ${STUB_DIR}/bm_os.c
)
create_gtest("ll" "${SRC_DIR}/ll.c" "${NONE}" "${STUBS}")
create_gtest("lib_state_machine" "${SRC_DIR}/lib_state_machine.c" "${NONE}" "${NONE}")

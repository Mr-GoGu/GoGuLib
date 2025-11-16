cmake_minimum_required(VERSION 3.30)
project(GoGuLibTests)

set(TEST_NAME "unit_tests")

include(CTest)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
)
FetchContent_MakeAvailable(googletest)

set(TEST_SRC_FILES
    Tests.cpp
)

set(TEST_LIBS
    gtest_main
    gmock
    GoGuLib
)

add_executable(${TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${TEST_NAME} PRIVATE ${TEST_LIBS})

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

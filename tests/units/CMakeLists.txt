cmake_minimum_required(VERSION 3.30)
project(GoGuLibUnitTests)

enable_testing()

set(TEST_NAME "GoGuLib_UnitTests")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
include(CTest)
find_package(GTest REQUIRED)

set(TEST_SRC_FILES
    Tests.cpp
)

add_executable(${TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${TEST_NAME}
    PUBLIC
        GTest::gtest
        GTest::gtest_main
)

target_link_libraries(${TEST_NAME}
    PRIVATE
        GoGuLib
)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

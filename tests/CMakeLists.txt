cmake_minimum_required(VERSION 3.30)
project(GoGuLibTests)

set(TEST_NAME "GoGuLib_UnitTests")

include(CTest)

set(TEST_SRC_FILES
    Tests.cpp
)

add_executable(${TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${TEST_NAME}
    PUBLIC
        gtest_main
        gmock
)

target_link_libraries(${TEST_NAME}
    PRIVATE
        GoGuLib
)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

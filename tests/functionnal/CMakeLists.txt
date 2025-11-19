cmake_minimum_required(VERSION 3.30)
project(GoGuLibFunctionnalTests)

set(TEST_NAME "GoGuLib_FunctionnalTests")

set(TEST_SRC_FILES
    Tests.cpp
)

add_executable(${TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${TEST_NAME}
    PRIVATE
        GoGuLib
)

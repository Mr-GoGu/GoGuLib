cmake_minimum_required(VERSION 3.30)
project(GoGuLib)

#  INITIALIZATION
# ------------------------------------------------------------------------------

set(LIB_NAME "${PROJECT_NAME}")
set(LIB_DIR $<TARGET_FILE_DIR:${LIB_NAME}>)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

set(LIB_SRC_FILES
    ${SRC_DIR}/Process.cpp
    ${SRC_DIR}/String.cpp
    ${SRC_DIR}/Temp.cpp
    ${SRC_DIR}/Debug.cpp
)

add_library(${LIB_NAME} STATIC ${LIB_SRC_FILES} ${INC_DIR}/GoGuLib.hpp)

target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR})

enable_testing()
add_subdirectory(tests)

cmake_minimum_required(VERSION 3.30)
project(GoGuLib)

set(LIB_NAME "${PROJECT_NAME}")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/package/scripts/buildsystems/vcpkg.cmake" CACHE STRING "" FORCE)
endif()

find_package(unofficial-minizip REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

set(LIB_SRC_FILES
    ${SRC_DIR}/Core/Debug.cpp
    ${SRC_DIR}/Core/Process.cpp
    ${SRC_DIR}/Core/String.cpp
    ${SRC_DIR}/Core/Temp.cpp
    ${SRC_DIR}/Logic/File.cpp
    ${SRC_DIR}/Network/Request.cpp
    ${SRC_DIR}/Network/Updater.cpp
)

add_library(${LIB_NAME} STATIC ${LIB_SRC_FILES} ${INC_DIR}/GoGuLib.hpp)

target_include_directories(${LIB_NAME}
    PUBLIC
        ${INC_DIR}
)

target_link_libraries(${LIB_NAME}
    PUBLIC
        unofficial::minizip::minizip
        CURL::libcurl
        nlohmann_json::nlohmann_json
)

if (DEFINED GOGULIB_BUILD_TESTS AND GOGULIB_BUILD_TESTS)
    # add_subdirectory(tests/units)
    add_subdirectory(tests/functionnal)
endif()

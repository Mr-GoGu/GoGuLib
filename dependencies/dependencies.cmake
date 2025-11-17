
include(FetchContent)

FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG        curl-8_11_1
)
FetchContent_MakeAvailable(curl)

if (DEFINED GOGULIB_BUILD_TESTS AND GOGULIB_BUILD_TESTS)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.zip
    )
    FetchContent_MakeAvailable(googletest)
endif()

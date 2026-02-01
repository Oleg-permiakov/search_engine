cmake_minimum_required(VERSION 3.16)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(nlohmann_json)

add_library(search_engine_lib
        src/ConverterJSON.cpp
        src/invertedIndex.cpp
        src/searchServer.cpp
)
target_include_directories(search_engine_lib PUBLIC include)

add_executable(search_engine src/main.cpp)
target_link_libraries(search_engine PRIVATE search_engine_lib nlohmann_json::nlohmann_json)

include(FetchContent)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(tests tests/test.cpp)
target_link_libraries(tests PRIVATE search_engine_lib GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(tests)


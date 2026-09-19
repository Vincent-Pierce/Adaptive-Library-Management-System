cmake_minimum_required(VERSION 3.14)

project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    Library_test
    tests/Library_test.cpp
)


target_include_directories(
    Library_test
    PRIVATE inc
)

target_link_libraries(
    Library_test
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(Library_test)
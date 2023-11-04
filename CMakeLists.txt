cmake_minimum_required(VERSION 3.27)
project(coroutines)

include(FetchContent)
include(GoogleTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-L/usr/local/opt/llvm/lib/c++ -Wl,-rpath,/usr/local/opt/llvm/lib/c++")

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(coroutines_test coroutines_test.cpp)
target_link_libraries(coroutines_test PUBLIC GTest::gmock_main)

enable_testing()
gtest_discover_tests(coroutines_test)
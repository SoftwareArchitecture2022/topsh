cmake_minimum_required(VERSION 3.16)

project(topsh)

set(CMAKE_CXX_STANDARD 20)

include_directories("src/")

add_executable(
  topsh
  src/main.cpp
)

################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  test/hello_test.cpp
)

target_link_libraries(
  hello_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
################################

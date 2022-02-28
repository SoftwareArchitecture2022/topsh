cmake_minimum_required(VERSION 3.16)

project(topsh)

set(CMAKE_CXX_STANDARD 20)

include_directories("src/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wshadow -Wconversion -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wextra-semi -Wformat=2")

set(
  SOURCES
  src/main.cpp
)

if(DEFINED ENV{SANITIZER})
    if($ENV{SANITIZER} STREQUAL "ADDRESS")
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)
    elseif($ENV{SANITIZER} STREQUAL "UB")
        add_compile_options(-fsanitize=undefined)
        add_link_options(-fsanitize=undefined)
    endif()
endif()

add_executable(
  topsh
  ${SOURCES}
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
  parser_test
  test/unit/parser/test_parser.cpp
)

target_link_libraries(
  parser_test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_test)
################################

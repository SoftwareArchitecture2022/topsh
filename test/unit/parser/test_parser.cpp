#include "interpreter/parser/parser.h"

#include <gtest/gtest.h>

TEST(TestExternalCommand, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "aoeu", .args = ""};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("aoeu"));
}

TEST(TestEmptyCat, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "cat", .args = ""};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat"));
}

TEST(TestExit, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "exit", .args = ""};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("exit"));
}

TEST(TestCat, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "cat", .args = "file"};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat file"));
}

TEST(TestCatExit, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "cat", .args = "exit"};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat exit"));
}

TEST(TestExitCat, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "exit", .args = "cat"};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("exit cat"));
}

TEST(TestLongCat, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "cat", .args = "cat cat cat exit"};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat cat cat cat exit"));
}

TEST(TestEcho, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "echo", .args = "lol"};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("echo lol"));
}

TEST(TestWC, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "wc", .args = "lol kek"};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("wc lol kek"));
}

TEST(TestPWD, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "pwd", .args = ""};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("pwd"));
}

TEST(TestEmpty, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "", .args = ""};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse(""));
}

TEST(TestSpaces, BasicAssertions) {
    auto answer = interpreter::internal::Command{.name = "echo", .args = "echo echo echo"};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("echo  echo   echo           echo"));
}

#include "interpreter/parser/parser.h"

#include <gtest/gtest.h>

TEST(TestExternalCommand, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "aoeu", .args = {}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("aoeu"));
}

TEST(TestEmptyCat, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "cat", .args = {}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat"));
}

TEST(TestExit, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "exit", .args = {}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("exit"));
}

TEST(TestCat, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "cat", .args = {"file"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat file"));
}

TEST(TestCatExit, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "cat", .args = {"exit"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat exit"));
}

TEST(TestExitCat, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "exit", .args = {"cat"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("exit cat"));
}

TEST(TestLongCat, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "cat", .args = {"cat", "cat", "cat", "exit"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cat cat cat cat exit"));
}

TEST(TestEcho, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "echo", .args = {"lol"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("echo lol"));
}

TEST(TestWC, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "wc", .args = {"lol", "kek"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("wc lol kek"));
}

TEST(TestPWD, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "pwd", .args = {}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("pwd"));
}

TEST(TestEmpty, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "", .args = {}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse(""));
}

TEST(TestSpaces, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "echo", .args = {"echo", "echo", "echo"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("echo  echo   echo           echo"));
}

TEST(TestQuotes1, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "echo",
                                                                                         .args = {"arg1", "arg2", "arg3"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("echo arg1 'arg2' \"arg3\""));
}

TEST(TestQuotes2, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "echo",
                                                                                         .args = {"arg1", "arg2 arg2", "arg3 arg3"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("echo arg1 'arg2 arg2' \"arg3 arg3\""));
}

TEST(TestPipes1, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "cmd1", .args = {"arg1"}},
                                                          interpreter::internal::Command{.name = "cmd2", .args = {"arg2"}},
                                                          interpreter::internal::Command{.name = "cmd3", .args = {"arg3"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("cmd1 arg1 | cmd2 arg2 | cmd3 arg3"));
}

TEST(TestPipes2, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command(),
                                                          interpreter::internal::Command{.name = "cmd1", .args = {"arg1"}},
                                                          interpreter::internal::Command{.name = "cmd2", .args = {"arg2"}},
                                                          interpreter::internal::Command()};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("| cmd1 arg1 | cmd2 arg2 |"));
}

TEST(TestEq1, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "=",
                                                                                         .args = {"arg1", "arg2", "arg3"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("arg1=arg2 arg3"));
}

TEST(TestEq2, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "=",
                                                                                         .args = {"arg1", "arg2 arg3"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("arg1='arg2 arg3'"));
}

TEST(TestEq3, BasicAssertions) {
    std::vector<interpreter::internal::Command> answer = {interpreter::internal::Command{.name = "cmd",
                                                                                         .args = {"=arg"}}};
    ASSERT_EQ(answer, interpreter::parser::Parser().Parse("'cmd'=arg"));
}

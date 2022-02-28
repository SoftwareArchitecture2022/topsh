#include "interpreter/parser/parser.h"

#include <gtest/gtest.h>

TEST(BasicAssertions, ParserGroup) {
    auto answer = interpreter::internal::Command{.name = "aoeu", .args = ""};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("aoeu"));

    answer = interpreter::internal::Command{.name = "cat", .args = ""};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("cat"));

    answer = interpreter::internal::Command{.name = "exit", .args = ""};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("exit"));

    answer = interpreter::internal::Command{.name = "cat", .args = "file"};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("cat file"));

    answer = interpreter::internal::Command{.name = "cat", .args = "exit"};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("cat exit"));

    answer = interpreter::internal::Command{.name = "exit", .args = "cat"};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("exit cat"));

    answer = interpreter::internal::Command{.name = "cat", .args = "cat cat cat exit"};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("cat cat cat cat exit"));

    answer = interpreter::internal::Command{.name = "echo", .args = "lol"};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("echo lol"));

    answer = interpreter::internal::Command{.name = "wc", .args = "lol kek"};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("wc lol kek"));

    answer = interpreter::internal::Command{.name = "pwd", .args = ""};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse("pwd"));

    answer = interpreter::internal::Command{.name = "", .args = ""};
    EXPECT_EQ(answer, interpreter::parser::Parser().Parse(""));
}

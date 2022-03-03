#include "interpreter/executor/executor.h"

#include <gtest/gtest.h>

class ExecutorFixture:
  public ::testing::Test
{
public:
  void SetUp() override {
    testing::internal::CaptureStdout();
    testing::internal::CaptureStderr();
  }

  void check(std::string command, std::string args, std::string expectedOutResult, std::string expectedErrResult, int expectedStatusCode, bool expectedIsExited) const {
    auto execution_result = executor.Execute({{command, args}});

    ASSERT_EQ(expectedIsExited, execution_result.isExited());
    ASSERT_EQ(expectedStatusCode, execution_result.getProgramStatusCode());
    ASSERT_EQ(expectedOutResult, testing::internal::GetCapturedStdout());
    ASSERT_EQ(expectedErrResult, testing::internal::GetCapturedStderr());
  }
protected:
  interpreter::executor::Executor executor{};
};

TEST_F(ExecutorFixture, TestEcho) {
  check("echo", "Hi", "Hi\n", "", 0, false);
}

TEST_F(ExecutorFixture, TestEchoLong) {
  check("echo", "Hi Hi Hi", "Hi Hi Hi\n", "", 0, false);
}

TEST_F(ExecutorFixture, TestExit) {
  check("exit", "", "", "", 0, true);
}

TEST_F(ExecutorFixture, TestExitWithArgs) {
  check("exit", "Hi", "", "", 0, true);
}


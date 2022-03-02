#include "interpreter/executor/executor.h"

#include <gtest/gtest.h>

TEST(TestEcho, TestExecutor) {
  auto executor = interpreter::executor::Executor();
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();
  std::string hi = "Hi";
  auto execution_result = executor.Execute({{"echo", hi}});

  ASSERT_FALSE(execution_result.isExited());
  ASSERT_EQ(0, execution_result.getProgramStatusCode());
  ASSERT_EQ(hi, testing::internal::GetCapturedStdout());
  ASSERT_EQ("", testing::internal::GetCapturedStderr());
}


#pragma once

#include "interpreter/executor/command_executors/command_executor.h"

#include <memory>

namespace interpreter::executor {

class EchoExecutor :
    public CommandExecutor {
 public:
  [[nodiscard]] int Execute(std::istream&,
                            std::ostream& output,
                            std::ostream&,
                            const std::string& args) noexcept override {
    output << args << "\n";
    return 0;
  }
 private:
};

} // namespace

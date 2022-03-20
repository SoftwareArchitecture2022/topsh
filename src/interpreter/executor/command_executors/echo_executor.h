#pragma once

#include "interpreter/executor/command_executors/command_executor.h"

#include <memory>

namespace interpreter::executor {

class EchoExecutor :
    public CommandExecutor {
 public:
  [[nodiscard]] int Execute(std::istream*,
                            std::ostream* output,
                            std::ostream*,
                            const internal::Command& command) noexcept override {
    for (size_t i = 0; i < command.args.size(); ++i) {
      if (i > 0) {
        *output << " ";
      }
      *output << command.args[i];
    }
    *output << "\n";
    return 0;
  }
 private:
};

} // namespace

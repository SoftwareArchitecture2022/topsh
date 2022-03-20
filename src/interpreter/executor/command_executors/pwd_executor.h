#pragma once

#include "interpreter/executor/command_executors/command_executor.h"

#include <memory>
#include <filesystem>

namespace interpreter::executor {

class PWDExecutor :
    public CommandExecutor {
 public:

  [[nodiscard]] int Execute(std::istream*,
                            std::ostream* output,
                            std::ostream*,
                            const internal::Command&) noexcept override {
    *output << std::string(std::filesystem::current_path()) << "\n";
    return 0;
  }
 private:
};

} // namespace

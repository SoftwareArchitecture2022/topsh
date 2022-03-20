#pragma once

#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/internal/executer_helper.h"

#include <memory>
#include <filesystem>

namespace interpreter::executor {

namespace ii = interpreter::internal;

class CatExecutor :
    public CommandExecutor {
 public:
  [[nodiscard]] int Execute(std::istream* input,
                            std::ostream* output,
                            std::ostream* error,
                            const internal::Command& command) noexcept override {
    const auto& args = command.args;
    if (args.empty()) {
      *output << input->rdbuf();
      return 0;
    }

    for (auto& filename : args) {
      if (!std::filesystem::exists(filename)) {
        *error << filename << ": ex: no such file or directory\n";
        continue;
      }
      *output << std::ifstream(filename).rdbuf() << "\n";
    }
    return 0;
  }
};

} // namespace

#pragma once

#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/internal/executer_helper.h"

#include <memory>
#include <filesystem>

namespace interpreter::executor {

namespace ii = interpreter::internal;

class CatExecutor:
    public CommandExecutor
{
public:
  [[nodiscard]] int Execute(std::istream& input,
                                    std::ostream& output,
                                    std::ostream& error,
                                    const std::string& args) noexcept override {
    std::vector<ii::File> files = ii::ParseFiles(input, args);

    for (auto& [filename, file] : files) {
      if (!std::filesystem::exists(filename)) {
        error << filename << ": ex: no such file or directory\n";
        continue;
      }
      output << file.rdbuf() << "\n";
    }
    return 0;
  }
private:
};

} // namespace

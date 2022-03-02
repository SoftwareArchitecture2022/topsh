#pragma once

#include "interpreter/executor/command_executors/command_executor.h"

#include <memory>
#include <filesystem>

namespace interpreter::executor {

class PWDExecutor:
    public CommandExecutor
{
public:

  [[nodiscard]] int Execute(std::istream&,
                                    std::ostream& output,
                                    std::ostream&,
                                    const std::string&) noexcept override {
    output << std::filesystem::current_path() << "\n";
    return 0;
  }
private:
};

} // namespace

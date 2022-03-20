#pragma once

#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/storage/storage.h"

#include <memory>

namespace interpreter::executor {

class AssignExecutor :
    public CommandExecutor {
 public:
  AssignExecutor() : CommandExecutor() {}

  void SetStorage(const std::shared_ptr<storage::Storage>& s) {
    storage = s;
  }

  [[nodiscard]] int Execute(std::istream*,
                            std::ostream*,
                            std::ostream* error,
                            const internal::Command& command) noexcept override {
    const auto& args = command.args;
    if (auto args_size = args.size(); args_size != 2) {
      *error << command.name << " error: wrong amount of args " << args_size
            << " != 2\n";
      return 1;
    }
    storage->SetVariableValue(args[0], args[1]);
    return 0;
  }
 private:
  std::shared_ptr<storage::Storage> storage;
};

} // namespace

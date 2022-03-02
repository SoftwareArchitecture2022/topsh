#pragma once

#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/storage/storage.h"

#include <memory>

namespace interpreter::executor {

class AssignExecutor :
    public CommandExecutor {
 public:
  AssignExecutor()
      : CommandExecutor(), storage(std::make_shared<storage::Storage>()) {}

  [[nodiscard]] int Execute(std::istream&,
                                    std::ostream&,
                                    std::ostream& error,
                                    const std::string& args) noexcept override {
    size_t space_pos = args.find(' ');
    if (space_pos == std::string::npos) {
      error << "assign parse error\n";
      return 1;
    }
    std::string var = args.substr(0, space_pos);
    std::string val = args.substr(space_pos + 1);
    storage->SetVariableValue(var, val);
    return 0;
  }
 private:
  std::shared_ptr<storage::Storage> storage;
};

} // namespace

#pragma once

#include "interpreter/internal/command.h"
#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/executor/command_executors/exit_executor.h"
#include "interpreter/executor/command_executors/echo_executor.h"
#include "interpreter/executor/command_executors/assign_executor.h"
#include "interpreter/executor/command_executors/cat_executor.h"
#include "interpreter/executor/command_executors/pwd_executor.h"
#include "interpreter/executor/command_executors/wc_executor.h"
#include "interpreter/internal/execute_result.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cassert>

namespace interpreter::executor {

class Executor {
 public:
  [[nodiscard]] internal::ExecuteResult
  Execute(const std::vector<internal::Command>& commands) const {

    int exit_code = 0;
    if (commands.size() == 1) {
      auto exec = MapNameToCommandExecutor(commands.front().name);
      if (exec.has_value()
          && std::dynamic_pointer_cast<executor::ExitExecutor>(exec.value())) {
        return {true, exit_code};
      }
    }
    std::stringstream in_buf;
    std::stringstream out_buf;
    std::istream* in = &std::cin;
    std::ostream* out = &out_buf;

    for (const auto& command : commands) {
      auto exec = MapNameToCommandExecutor(command.name);
      std::string command_args;
      if (!exec.has_value()) {
        exec = external_executor_;
      }
      exit_code = exec.value()->Execute(in, out, &std::cerr, command);
      std::stringstream().swap(in_buf);
      in_buf << out_buf.str();
      std::stringstream().swap(out_buf);
      in = &in_buf;
      out = &out_buf;
    }
    std::cout << in_buf.str();
    return {false, exit_code};
  }

  void SetStorage(const std::shared_ptr<storage::Storage>& s) {
    dynamic_cast<AssignExecutor*>(command_to_executor_.at("=").get())->SetStorage(
        s);
  }

 private:
  std::optional<std::shared_ptr<CommandExecutor>>
  MapNameToCommandExecutor(const std::string& command) const {
    auto exec = command_to_executor_.find(command);

    if (exec != command_to_executor_.end()) {
      return exec->second;
    }
    return std::nullopt;
  }

 private:
  const std::unordered_map<std::string, std::shared_ptr<CommandExecutor>>
      command_to_executor_ = {
      {"=", std::make_shared<executor::AssignExecutor>()},
      {"cat", std::make_shared<executor::CatExecutor>()},
      {"echo", std::make_shared<executor::EchoExecutor>()},
      {"exit", std::make_shared<executor::ExitExecutor>()},
      {"pwd", std::make_shared<executor::PWDExecutor>()},
      {"wc", std::make_shared<executor::WCExecutor>()},
  };
  std::shared_ptr<CommandExecutor>
      external_executor_ = std::make_shared<CommandExecutor>();
};

} // namespace
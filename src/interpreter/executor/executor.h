#pragma once

#include "interpreter/internal/command.h"
#include "interpreter/executor/command_executors/command_executor.h"

#include <memory>
#include <vector>

namespace interpreter::executor {

class Executor {
public:
    [[nodiscard]] internal::ExecuteResult Execute(const std::vector<internal::Command>) const noexcept {
        return {0, 0};
    }
private:
    std::shared_ptr<CommandExecutor> MapNameToCommandExecutor(std::string_view) const noexcept {
        return {};
    }
private:
};

} // namespace

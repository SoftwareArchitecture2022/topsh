#pragma once

#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/storage/storage.h"

#include <memory>


namespace interpreter::executor {

class AssignExecutor:
    public CommandExecutor
{
public:
    [[nodiscard]] int Execute(std::istream& input, std::ostream& output, std::ostream& error) noexcept override {
        return 0;
    }

private:
    std::shared_ptr<storage::Storage> storage;
};

} // namespace

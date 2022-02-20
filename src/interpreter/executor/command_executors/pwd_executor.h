#pragma once

#include "interpreter/executor/command_executors/command_executor.h"

#include <memory>


namespace interpreter::executor {

class PWDExecutor:
    public CommandExecutor
{
public:
    [[nodiscard]] int Execute(std::istream& input, std::ostream& output, std::ostream& error) noexcept override {
        return 0;
    }
private:
};

} // namespace

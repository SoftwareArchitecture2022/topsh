#pragma once

#include <iostream>

namespace interpreter::executor {

class CommandExecutor {
public:
    [[nodiscard]] virtual int Execute(std::istream& input, std::ostream& output, std::ostream& error) noexcept {
        return 0;
    }
};

} // namespace

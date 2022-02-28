#pragma once

#include <string>

namespace interpreter::internal {

struct Command {
    std::string name;
    std::string args;

    bool operator==(const Command& other) const noexcept {
        return name == other.name && args == other.args;
    }
};

} // namespace

#pragma once

#include <string>
#include <vector>

namespace interpreter::internal {

struct Command {
    std::string name;
    std::vector<std::string> args;

    bool operator==(const Command& other) const noexcept {
        return name == other.name && args == other.args;
    }
};

} // namespace

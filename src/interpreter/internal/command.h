#pragma once

#include <string>
#include <vector>

namespace interpreter::internal {

using Args = std::vector<std::string>;

struct Command {
    std::string name;
    Args args;

    bool operator==(const Command& other) const noexcept {
        return name == other.name && args == other.args;
    }
};

} // namespace

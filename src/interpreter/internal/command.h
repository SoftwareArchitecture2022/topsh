#pragma once

#include <string>

namespace interpreter::internal {

struct Command {
    std::string name;
    std::string args;
};

} // namespace

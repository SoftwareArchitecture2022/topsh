#pragma once

#include <string>

namespace interpreter::internal {

struct RawString {
    std::string value;
    bool quoted;
};

} // namespace

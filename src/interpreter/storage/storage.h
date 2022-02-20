#pragma once

#include <string>

namespace interpreter::storage {

class Storage {
public:
    std::string MapVariableToValue(std::string var) {
        return "";
    }

    void SetVariableValue(std::string var, std::string val) {
        return;
    }
private:
};

} // namespace

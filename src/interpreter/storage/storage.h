#pragma once

#include <string>
#include <cstdlib>
#include <stdlib.h>

namespace interpreter::storage {

class Storage {
 public:
  std::string MapVariableToValue(const std::string& var) const {
    return std::getenv(var.data());
  }

  void SetVariableValue(const std::string& var, const std::string& val) const {
    setenv(var.data(), val.data(), 1);
  }
 private:
};

} // namespace

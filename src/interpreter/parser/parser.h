#pragma once

#include "interpreter/storage/storage.h"
#include "interpreter/internal/command.h"
#include "interpreter/internal/raw_string.h"

#include <memory>
#include <vector>

namespace interpreter::parser {

class Parser {
public:
    [[nodiscard]] internal::Command Parse(std::string_view) const noexcept {
        return {};
    }
private:
    [[nodiscard]] std::vector<internal::RawString> SplitByDelimiters(std::string_view) const noexcept {
        return {};
    }

    [[nodiscard]] std::vector<std::string> SubstituteVariables(const std::vector<internal::RawString>&) const noexcept {
        return {};
    }

    [[nodiscard]] internal::Command ParseCommand(const std::vector<std::string>&) const noexcept {
        return {};
    }
private:
    std::shared_ptr<storage::Storage> storage;
};

} // namespace

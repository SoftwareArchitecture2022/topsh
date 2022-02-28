#pragma once

#include "interpreter/storage/storage.h"
#include "interpreter/internal/command.h"
#include "interpreter/internal/execute_result.h"
#include "interpreter/internal/raw_string.h"

#include <memory>
#include <vector>
#include <exception>

namespace interpreter::parser {

class ParseException : public std::runtime_error {
public:
    ParseException() : runtime_error("error during input parsing: unpaired quotes") {};
};

class Parser {
public:
    [[nodiscard]] internal::Command Parse(std::string_view input) const noexcept {
        std::vector<internal::RawString> raw_str = SplitByDelimiters(input);
        std::vector<std::string> str_sub = SubstituteVariables(raw_str);
        internal::Command cmd = ParseCommand(str_sub);
        return cmd;
    }
private:
    [[nodiscard]] std::vector<internal::RawString> SplitByDelimiters(std::string_view input) const noexcept {
        std::vector<internal::RawString> raw_str;
        std::string s;
        for (size_t i; i < input.length(); i++) {
            if (isblank(input[i]) && s.length() != 0) {
                raw_str.push_back({s, false});
                s.clear();
            } else if (input[i] == '"' || input[i] == '\'') {
                int begin = i + 1;
                int end = input.find(input[i], begin);
                if (end == std::string::npos) {
                    throw ParseException();
                }
                s.assign(input, begin, end - begin);
                raw_str.push_back({s, input[i] == '\''});
                s.clear();
                i = end;
            } else {
                s.push_back(input[i]);
            }
        }
        if (s.length() != 0) {
            raw_str.push_back({s, false});
        }
        return raw_str;
    }

    [[nodiscard]] std::vector<std::string> SubstituteVariables(const std::vector<internal::RawString>& raw_str) const noexcept {
        std::vector<std::string> str_sub;
        for (internal::RawString s : raw_str) {
            str_sub.push_back(s.value);
        }
        return str_sub;
    }

    [[nodiscard]] internal::Command ParseCommand(const std::vector<std::string>& str_vec) const noexcept {
        size_t eq_idx = str_vec[0].find('=');
        if (eq_idx == std::string::npos) {
            std::string args;
            for (int i = 1; i < str_vec.size(); i++) {
                args.append(str_vec[i]);
                args.push_back(' ');
            }
            return {str_vec[0], args};
        }
        std::string args;
        args.append(str_vec[0].data(), eq_idx);
        args.push_back(' ');
        if (eq_idx + 1 < str_vec[0].length()) {
            args.append(str_vec[0].data(), eq_idx + 1, str_vec[0].length() - eq_idx - 1);
        }
        return {"=", args};
    }
private:
    std::shared_ptr<storage::Storage> storage;
};

} // namespace

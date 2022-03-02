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
  ParseException()
      : runtime_error("error during input parsing: unpaired quotes") {}
};

class Parser {
 public:
  // converts a string from user into a Command structure, containing command name and its arguments
  [[nodiscard]] static internal::Command Parse(std::string_view input) {
    std::vector<internal::RawString> raw_str = SplitByDelimiters(input);
    std::vector<std::string> str_sub = SubstituteVariables(raw_str);
    internal::Command cmd = ParseCommand(str_sub);
    return cmd;
  }
 private:
  [[nodiscard]] static std::vector<internal::RawString> SplitByDelimiters(std::string_view input) {
    std::vector<internal::RawString> raw_str;
    std::string s;
    for (size_t i = 0; i < input.length(); i++) {
      if (isblank(input[i]) && s.length() != 0) {
        raw_str.push_back({s, false});
        s.clear();
      } else if (input[i] == '"' || input[i] == '\'') {
        size_t begin = i + 1;
        size_t end = input.find(input[i], begin);
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

  [[nodiscard]] static std::vector<std::string> SubstituteVariables(const std::vector<
      internal::RawString>& raw_str) noexcept {
    std::vector<std::string> str_sub;
    str_sub.reserve(raw_str.size());
    for (const internal::RawString& s : raw_str) {
      str_sub.push_back(s.value);
    }
    return str_sub;
  }

  [[nodiscard]] static internal::Command ParseCommand(const std::vector<std::string>& str_vec) noexcept {
    if (str_vec.empty()) {
      return {"", ""};
    }
    size_t eq_idx = str_vec[0].find('=');
    if (eq_idx == std::string::npos) {
      std::string args;
      for (size_t i = 1; i < str_vec.size(); i++) {
        args.append(str_vec[i]);
        if (i != str_vec.size() - 1) {
          args.push_back(' ');
        }
      }
      return {str_vec[0], args};
    }
    std::string args;
    args.append(str_vec[0].data(), eq_idx);
    if (eq_idx + 1 < str_vec[0].length()) {
      args.push_back(' ');
      args.append(str_vec[0],
                  eq_idx + 1,
                  str_vec[0].length() - eq_idx - 1);
    }
    return {"=", args};
  }
 private:
  std::shared_ptr<storage::Storage> storage;
};

} // namespace

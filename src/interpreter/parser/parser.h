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
  [[nodiscard]] std::vector<internal::Command> Parse(const std::string_view& input) {
    std::vector<internal::RawString> str_vect = SplitByDelimiters(input);
    std::vector<std::string> str_subs = SubstituteVariables(str_vect);
    std::vector<std::vector<std::string>> str_pipes = SplitByPipes(str_subs);
    std::vector<internal::Command> cmd_vect = ParseCommands(str_pipes);
    return cmd_vect;
  }

  void SetStorage(const std::shared_ptr<storage::Storage>& s) {
    storage = s;
  }
 private:
  [[nodiscard]] static std::vector<internal::RawString> SplitByDelimiters(const std::string_view& input) {
    std::vector<internal::RawString> str_vect;
    std::string s;
    for (size_t i = 0; i < input.length(); i++) {
      bool is_blank = std::isblank(input[i]);
      bool is_quote = input[i] == '"' || input[i] == '\'';
      if ((is_blank || is_quote) && s.length() != 0) {
        str_vect.push_back({s, false});
        s.clear();
      }
      if (is_quote) {
        size_t begin = i + 1;
        size_t end = input.find(input[i], begin);
        if (end == std::string::npos) {
          throw ParseException();
        }
        s.assign(input, begin, end - begin);
        str_vect.push_back({s, input[i] == '\''});
        s.clear();
        i = end;
      }
      if (!is_blank && !is_quote) {
        s.push_back(input[i]);
      }
    }
    if (s.length() != 0) {
      str_vect.push_back({s, false});
    }
    return str_vect;
  }

  [[nodiscard]] std::vector<std::string> SubstituteVariables(const std::vector<
      internal::RawString>& raw_str) noexcept {
    std::vector<std::string> str_subs;
    for (const internal::RawString& rs : raw_str) {
      std::string s = rs.value;
      size_t subs_idx = s.find('$');
      while (!rs.quoted && subs_idx != std::string::npos) {
        std::string name;
        for (size_t i = subs_idx + 1; i < s.length(); i++) {
          char c = s[i];
          if (!std::isblank(c) && c != '=' && c != '$') {
            name += c;
          } else {
            break;
          }
        }
        std::string value = storage->MapVariableToValue(name);
        s = s.replace(subs_idx, name.length() + 1, value);
        subs_idx = s.find('$');
      }
      str_subs.push_back(s);
    }
    return str_subs;
  }

  [[nodiscard]] static std::vector<std::vector<std::string>>
  SplitByPipes(const std::vector<std::string>& str_vect) noexcept {
    std::vector<std::vector<std::string>> str_pipes;
    std::vector<std::string> cur;
    for (const std::string& s : str_vect) {
      if (s == "|") {
        str_pipes.push_back(cur);
        cur.clear();
      } else {
        cur.push_back(s);
      }
    }
    str_pipes.push_back(cur);
    return str_pipes;
  }

  [[nodiscard]] static std::vector<internal::Command> ParseCommands(const std::vector<
      std::vector<std::string>>& str_pipes) noexcept {
    std::vector<internal::Command> cmd_vect;
    cmd_vect.reserve(str_pipes.size());
    for (const std::vector<std::string>& v : str_pipes) {
      cmd_vect.push_back(ParseCommand(v));
    }
    return cmd_vect;
  }

  [[nodiscard]] static internal::Command ParseCommand(const std::vector<std::string>& str_vec) noexcept {
    if (str_vec.empty()) {
      return {};
    }
    size_t eq_idx = str_vec[0].find('=');
    if (eq_idx == std::string::npos) {
      std::vector<std::string> args;
      for (size_t i = 1; i < str_vec.size(); i++) {
        args.push_back(str_vec[i]);
      }
      return {str_vec[0], args};
    }
    std::vector<std::string> args;
    args.push_back(str_vec[0].substr(0, eq_idx));
    if (eq_idx + 1 < str_vec[0].length()) {
      args.push_back(str_vec[0].substr(eq_idx + 1));
    }
    for (size_t i = 1; i < str_vec.size(); i++) {
      args.push_back(str_vec[i]);
    }
    return {"=", args};
  }

 private:
  std::shared_ptr<storage::Storage> storage;
};

} // namespace

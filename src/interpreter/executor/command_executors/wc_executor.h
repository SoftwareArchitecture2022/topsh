
#pragma once

#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/internal/executer_helper.h"

#include <memory>

namespace interpreter::executor {

namespace ii = interpreter::internal;

class WCExecutor :
    public CommandExecutor {
 public:
  [[nodiscard]] int Execute(std::istream* input,
                            std::ostream* output,
                            std::ostream* error,
                            const internal::Command& command) noexcept override {
    const auto& args = command.args;
    if (args.empty()) {
      WCInfo count_input = WordCount(*input);
      FormatWC(*output, count_input);
      return 0;
    }

    WCInfo count_total;

    for (const auto& filename : command.args) {
      if (!std::filesystem::exists(filename)) {
        *error << filename << ": ex: no such file or directory\n";
        continue;
      }
      std::ifstream file(filename);

      WCInfo count_file = WordCount(file);

      FormatWC(*output, count_file, filename);
      count_total += count_file;
    }
    if (args.size() > 1) {
      FormatWC(*output, count_total, "total");
    }
    return 0;
  }
 private:
  struct WCInfo {
    size_t lines = 0;
    size_t words = 0;
    size_t bytes = 0;

    WCInfo& operator+=(const WCInfo& other) {
      lines += other.lines;
      words += other.words;
      bytes += other.bytes;
      return *this;
    }
  };

  void static FormatWC(std::ostream& output,
                       const WCInfo& count_info,
                       const std::optional<std::string>& filename = std::nullopt) {
    output << count_info.lines << " " << count_info.words << " "
           << count_info.bytes;
    if (filename.has_value()) {
      output << " " << filename.value();
    }
    output << "\n";
  }

  static WCInfo WordCount(std::istream& file) {
    WCInfo count_file;
    std::string data;
    for (; !file.eof(); ++count_file.lines) {
      std::getline(file, data, '\n');
      count_file.words += ii::CountWords(data);
      count_file.bytes += data.size() + 1;
    }
    return count_file;
  }
};

} // namespace

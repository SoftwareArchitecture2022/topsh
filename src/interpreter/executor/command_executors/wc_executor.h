
#pragma once

#include "interpreter/executor/command_executors/command_executor.h"
#include "interpreter/internal/executer_helper.h"

#include <memory>

namespace interpreter::executor {

namespace ii = interpreter::internal;

class WCExecutor :
    public CommandExecutor {
 public:
  [[nodiscard]] int Execute(std::istream& input,
                                    std::ostream& output,
                                    std::ostream& error,
                                    const std::string& args) noexcept override {
    std::vector<ii::File> files = ii::ParseFiles(input, args);

    size_t lines_t = 0;
    size_t words_t = 0;
    size_t bytes_t = 0;

    for (auto& [filename, file] : files) {
      if (!std::filesystem::exists(filename)) {
        error << filename << ": ex: no such file or directory\n";
        continue;
      }
      size_t lines = 0;
      size_t words = 0;


      std::string data;
      for (; std::getline(file, data); ++lines) {
        words += ii::CountWords(data);
      }
      std::fstream fbin(filename);
      fbin.seekp(0);
      auto begin = fbin.tellg();
      fbin.seekg(0, std::ios::end);
      auto end  = fbin.tellg();
      auto bytes = static_cast<size_t>(end - begin);

      FormatWC(output, lines, words, bytes, filename);

      lines_t += lines;
      words_t += words;
      bytes_t += bytes_t;
    }
    if (files.size() > 1) {
      FormatWC(output, lines_t, words_t, bytes_t, "total");
    }
    return 0;
  }
 private:
  void static FormatWC(std::ostream& output,
                       size_t lines,
                       size_t words,
                       size_t bytes,
                       const std::string& filename) {
    output << lines << " " << words << " " << bytes << " " << filename
           << "\n";
  }

};

} // namespace

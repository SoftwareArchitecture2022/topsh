#pragma once

#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <random>

namespace interpreter::executor {

class CommandExecutor {
 public:
  virtual ~CommandExecutor() = default;

  [[nodiscard]] virtual int Execute(std::istream*,
                                    std::ostream* output,
                                    std::ostream* error,
                                    const internal::Command& command) noexcept {
    std::mt19937 generator(12);
    std::uniform_int_distribution<int> distribution(100, 999);

    std::filesystem::create_directories("/tmp/topsh");
    std::string tmp_out =
        "/tmp/topsh/tmp_out_" + std::to_string(distribution(generator))
            + ".txt";
    std::string tmp_err =
        "/tmp/topsh/tmp_err_" + std::to_string(distribution(generator))
            + ".txt";
    std::stringstream ss;
    ss << command.name << " ";
    for (const auto& arg : command.args) {
      ss << arg << " ";
    }
    ss << "1>" << tmp_out << " 2>" << tmp_err;
    std::string cmd = ss.str();
    *output << std::flush;
    *error << std::flush;
    int result = std::system(cmd.data());

    Print(*output, tmp_out);
    Print(*error, tmp_err);
    return result;
  }
 private:
  static void Print(std::ostream& output, const std::string& filename) {
    std::ifstream in(filename);
    std::stringstream ss;
    ss << in.rdbuf();
    output << ss.str();
  }
};

} // namespace

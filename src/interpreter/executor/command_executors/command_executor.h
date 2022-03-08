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

  [[nodiscard]] virtual int Execute(std::istream&,
                                    std::ostream& output,
                                    std::ostream& error,
                                    const std::string& args) noexcept {
    std::mt19937 generator(12);
    std::uniform_int_distribution<int> distribution(100, 999);

    std::filesystem::create_directories("/tmp/topsh");
    std::string tmp_out =
        "/tmp/topsh/tmp_out_" + std::to_string(distribution(generator))
            + ".txt";
    std::string tmp_err =
        "/tmp/topsh/tmp_err_" + std::to_string(distribution(generator))
            + ".txt";
    std::string command = args + " 1>" + tmp_out + " 2>" + tmp_err;
    output << std::flush;
    error << std::flush;
    int result = std::system(command.data());
    output << std::ifstream(tmp_out).rdbuf();
    error << std::ifstream(tmp_err).rdbuf();
    return result;
  }
};

} // namespace

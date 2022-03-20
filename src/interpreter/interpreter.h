#pragma once

#include "interpreter/parser/parser.h"
#include "interpreter/executor/executor.h"

#include <memory>

namespace interpreter {

class Interpreter {
 public:
  Interpreter()
      : parser(std::make_unique<parser::Parser>()),
        executor(std::make_unique<executor::Executor>()) {
  }
  // launches a loop that reads user input, parses it and executes commands
  void Run() noexcept {
    std::shared_ptr<storage::Storage> storage = std::make_shared<storage::Storage>();
    parser->SetStorage(storage);
    executor->SetStorage(storage);
    while (!std::cin.eof()) {
      std::string input;
      std::getline(std::cin, input);
      try {
        std::vector<internal::Command> cmd = parser->Parse(input);
        internal::ExecuteResult res = executor->Execute(cmd);
        if (res.getProgramStatusCode() != 0) {
          std::cout << "program exited with code " << res.getProgramStatusCode()
                    << std::endl;
        }
        if (res.isExited()) {
          break;
        }
      } catch (parser::ParseException& exc) {
        std::cerr << exc.what() << std::endl;
      }
    }
  }
 private:
  std::unique_ptr<parser::Parser> parser;
  std::unique_ptr<executor::Executor> executor;
};

} // namespace

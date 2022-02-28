#pragma once

#include "interpreter/parser/parser.h"
#include "interpreter/executor/executor.h"

#include <memory>

namespace interpreter {

class Interpreter {
    void Run() noexcept {
        while (true) {
            std::string input;
            std::cin >> input;
            try {
                internal::Command cmd = parser->Parse(input);
                internal::ExecuteResult res = executor->Execute({cmd});
                if (res.getProgramStatusCode() != 0) {
                    std::cout << "program exited with code " << res.getProgramStatusCode() << std::endl;
                }
                if (res.isExited()) {
                    break;
                }
            } catch (parser::ParseException &exc) {
                std::cerr << exc.what() << std::endl;
            }
        }
    }
private:
    std::unique_ptr<parser::Parser> parser;
    std::unique_ptr<executor::Executor> executor;
};

} // namespace

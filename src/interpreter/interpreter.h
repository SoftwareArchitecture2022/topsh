#pragma once

#include "interpreter/parser/parser.h"
#include "interpreter/executor/executor.h"

#include <memory>

namespace interpreter {

class Interpreter {
    void Run() noexcept {
    }
private:
    std::unique_ptr<parser::Parser> parser;
    std::unique_ptr<executor::Executor> executor;
};

} // namespace

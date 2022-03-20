#pragma once

namespace interpreter::internal {

class ExecuteResult {
public:
    ExecuteResult(int e, int p):
        exited(e),
        programStatusCode(p)
    {}

    [[nodiscard]] int getProgramStatusCode() const noexcept {
        return programStatusCode;
    }

    [[nodiscard]] bool isExited() const noexcept {
        return exited;
    }
private:
    bool exited = false;
    int programStatusCode = 0;
};

} // namespace

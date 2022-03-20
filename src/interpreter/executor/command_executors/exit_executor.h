#include "interpreter/executor/command_executors/command_executor.h"

#include <memory>

namespace interpreter::executor {

class ExitExecutor :
    public CommandExecutor {
 public:
  [[nodiscard]] int Execute(std::istream*,
                            std::ostream*,
                            std::ostream*,
                            const internal::Command&) noexcept override {
    return 0;
  }
 private:
};

} // namespace

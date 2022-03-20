#pragma once

#include <fstream>
#include <utility>
#include <vector>
#include <regex>

namespace interpreter::internal {

struct File {
  File(std::string fname,
       std::fstream f)
      : filename(std::move(fname)), file(std::move(f)) {
  }
  std::string filename;
  std::fstream file;
};


[[nodiscard]] size_t CountWords(const std::string& data) {
  const std::regex expression("[^\\s]+");
  return static_cast<size_t>(std::distance(
      std::sregex_iterator(data.begin(), data.end(), expression),
      std::sregex_iterator()));
}

} // namespace internal::executor

//
// Created by Michael Wittmann on 15/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_LOG_HPP
#define SPOTIFYWEBAPIADAPTER_LOG_HPP

#include <memory>  // for shared_ptr

#include "Core.hpp"
namespace spdlog {
class logger;
}

namespace spotify {
inline namespace v1 {

class Log {
 public:
  static void init();
  static Ref<spdlog::logger> &logger() { return core_logger_; }

 private:
  static Ref<spdlog::logger> core_logger_;
  static constexpr int max_file_size = 1024 * 1024 * 10;
  static constexpr int max_files = 3;
  static constexpr int max_threads = 1;
  static constexpr int max_items = 8192;
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

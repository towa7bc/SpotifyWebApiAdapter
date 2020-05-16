//
// Created by Michael Wittmann on 15/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_LOG_HPP
#define SPOTIFYWEBAPIADAPTER_LOG_HPP

#include <spdlog/async.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include "Core.hpp"

namespace spotify::inline v1 {

class Log {
 public:
  static void init();
  static Ref<spdlog::logger> &logger() { return _core_logger; }

 private:
  static Ref<spdlog::logger> _core_logger;
  static constexpr int max_file_size = 1024 * 1024 * 10;
  static constexpr int max_files = 3;
  static constexpr int max_threads = 1;
  static constexpr int max_items = 8192;
};

}  // namespace spotify::inline v1

#endif

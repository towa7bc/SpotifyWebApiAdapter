//
// Created by Michael Wittmann on 15/05/2020.
//

#include "Log.hpp"

#include <spdlog/async.h>                     // for init_thread_pool, threa...
#include <spdlog/async_logger.h>              // for async_logger, async_ove...
#include <spdlog/common.h>                    // for sink_ptr, spdlog_ex, trace
#include <spdlog/logger.h>                    // for logger
#include <spdlog/sinks/rotating_file_sink.h>  // for rotating_file_sink_mt
#include <spdlog/sinks/stdout_color_sinks.h>  // for stdout_color_sink_mt
#include <spdlog/spdlog.h>                    // for register_logger

#include <string>  // for operator+
#include <vector>  // for vector

#include "Core.hpp"  // for create_ref

namespace spotify::inline v1 {

Ref<spdlog::logger> core_logger_;

void Log::init() {
  try {
    spdlog::init_thread_pool(max_items, max_threads);
    auto stdout_sink = create_ref<spdlog::sinks::stdout_color_sink_mt>();
    auto rotating_sink = create_ref<spdlog::sinks::rotating_file_sink_mt>(
        "spotify.log", max_file_size, max_files);
    stdout_sink->set_pattern("%^[%T] %n: %v%$");
    rotating_sink->set_pattern("[%T] [%1] %n: %v");
    std::vector<spdlog::sink_ptr> sinks{stdout_sink, rotating_sink};
    core_logger_ = create_ref<spdlog::async_logger>(
        "SPOTIFY", sinks.begin(), sinks.end(), spdlog::thread_pool(),
        spdlog::async_overflow_policy::block);
    spdlog::register_logger(core_logger_);
    core_logger_->set_level(spdlog::level::trace);
    core_logger_->flush_on(spdlog::level::trace);

  } catch (const spdlog::spdlog_ex &ex) {
    spdlog::logger("Log initialization failed: " + std::string(ex.what()));
  }
}

}  // namespace spotify::inline v1
//
// Created by Michael Wittmann on 15/05/2020.
//

#include "Log.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace spotify::inline v1 {

Ref<spdlog::logger> _core_logger;

void Log::init() {
    try {
        _core_logger = spdlog::rotating_logger_mt<spdlog::async_factory>(
                "SPOTIFY", "spotify.log", max_file_size, max_files);
        spdlog::register_logger(_core_logger);
        _core_logger->set_level(spdlog::level::trace);
        _core_logger->flush_on(spdlog::level::trace);

    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::logger("Log initialization failed: " + std::string(ex.what()));
    }
}

}// namespace spotify::inline v1
//
// Created by Michael Wittmann on 15/05/2020.
//

#include "Log.hpp"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace spotify::inline v1 {

Ref<spdlog::logger> _core_logger;

void Log::init() {
    try {
        spdlog::init_thread_pool(max_items, max_threads);
        auto stdout_sink = create_ref<spdlog::sinks::stdout_color_sink_mt>();
        auto rotating_sink = create_ref<spdlog::sinks::rotating_file_sink_mt>("spotify.log", max_file_size, max_files);
        stdout_sink->set_pattern("%^[%T] %n: %v%$");
        rotating_sink->set_pattern("[%T] [%1] %n: %v");
        std::vector<spdlog::sink_ptr> sinks{stdout_sink, rotating_sink};
        _core_logger = create_ref<spdlog::async_logger>("SPOTIFY",
                                                        sinks.begin(),
                                                        sinks.end(),
                                                        spdlog::thread_pool(),
                                                        spdlog::async_overflow_policy::block);
        spdlog::register_logger(_core_logger);
        _core_logger->set_level(spdlog::level::trace);
        _core_logger->flush_on(spdlog::level::trace);

    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::logger("Log initialization failed: " + std::string(ex.what()));
    }
}

}// namespace spotify::inline v1
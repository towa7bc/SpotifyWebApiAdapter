//
// Created by Michael Wittmann on 15/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_LOG_HPP
#define SPOTIFYWEBAPIADAPTER_LOG_HPP

#include "Core.hpp"
#include <spdlog/async.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace spotify::inline v1 {

class Log {
public:
    static void init();
    static Ref<spdlog::logger> &logger() { return _core_logger; }

private:
    static Ref<spdlog::logger> _core_logger;
    static constexpr int max_file_size = 1048576 * 5;
    static constexpr int max_files = 1048576 * 5;
};

}// namespace spotify::inline v1

#endif

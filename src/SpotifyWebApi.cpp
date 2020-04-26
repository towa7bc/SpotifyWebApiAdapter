#include "SpotifyWebApi.h"

void SpotifyWebApi::Initialize() {
    constexpr int max_file_size = 1048576 * 5;
    constexpr int max_files = 1048576 * 5;
    try {
        m_asyncLogger = spdlog::rotating_logger_mt<spdlog::async_factory>("async_file_logger",
                                                                          "logs/async_log.txt",
                                                                          max_file_size, max_files);

        m_asyncLogger->set_level(spdlog::level::debug);
        m_asyncLogger->debug("Initialize called.");
    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "Log initialization failed: " << ex.what() << '\n';
    }
}

void SpotifyWebApi::Authorize() {
}

void SpotifyWebApi::post() {
}

void SpotifyWebApi::update() {
}

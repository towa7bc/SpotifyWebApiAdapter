#include "SpotifyWebApiAdapter.h"

void SpotifyWebApiAdapter::Initialize() {
    try {
        m_asyncLogger = spdlog::rotating_logger_mt<spdlog::async_factory>("async_file_logger",
                                                                          "logs/async_log.txt",
                                                                          max_file_size, max_files);
        m_asyncLogger->set_level(spdlog::level::debug);
        m_asyncLogger->debug("Initialize called.");
        m_manager.performGetRequest("", "", "");
    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::logger("Log initialization failed: " + std::string(ex.what()));
    }
}

void SpotifyWebApiAdapter::Authorize() {
}

void SpotifyWebApiAdapter::post() {
}

void SpotifyWebApiAdapter::update() {
}

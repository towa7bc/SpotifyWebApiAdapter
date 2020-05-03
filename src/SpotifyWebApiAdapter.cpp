//
// Created by Michael Wittmann on 01/05/2020.
//

#include "SpotifyWebApiAdapter.hpp"

auto spotify::SpotifyWebApiAdapter::Initialize() -> void {
    try {
        _async_logger = spdlog::rotating_logger_mt<spdlog::async_factory>(
                "async_file_logger", "logs/async_log.txt", max_file_size, max_files);
        _async_logger->set_level(spdlog::level::debug);
        _async_logger->debug("Initialize called.");
        _manager.performGetRequest("", "", "");
    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::logger("Log initialization failed: " + std::string(ex.what()));
    }
}

auto spotify::SpotifyWebApiAdapter::Authorize() -> void {}

auto spotify::SpotifyWebApiAdapter::post() -> void {
    stlab::sender<int> send;
    stlab::receiver<int> receive;

    std::tie(send, receive) = stlab::channel<int>(stlab::default_executor);
    std::atomic_bool done{false};

    auto hold = receive | [&_done = done](int x) {
        std::cout << x << '\n';
        _done = true;
    };

    // It is necessary to mark the receiver side as ready, when all connections are
    // established
    receive.set_ready();

    send(1);
    send(2);
    send(3);

    // Waiting just for illustrational purpose
    while (!done.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

auto spotify::SpotifyWebApiAdapter::update() -> void {}
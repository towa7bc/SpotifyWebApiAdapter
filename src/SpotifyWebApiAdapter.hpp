#ifndef SPOTIFYWEBAPI_SPOTIFYWEBAPI_H
#define SPOTIFYWEBAPI_SPOTIFYWEBAPI_H

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 20
#endif

#include "SpotifyNetworkManager.hpp"
#include <array>
#include <atomic>
#include <iostream>
#include <memory>
#include <stlab/concurrency/channel.hpp>
#include <stlab/concurrency/default_executor.hpp>
#include <thread>

namespace spotify {

inline namespace v1 {

class SpotifyWebApiAdapter {
public:
    auto Initialize() -> void;
    auto Authorize() -> void;

private:
    static constexpr int dim = 33;
    const std::string clientId = "636b0c0e79f34ce39855f58337583f84";
    const std::string clientSecret = "6c3d3d78017347bfaacf451a3789811e";
    static constexpr std::array<char, dim> clientSecretEncrypted{"{.~)~)zu}|z~yz/+,,.+yx|,~zutu||("};
    static constexpr int max_file_size = 1048576 * 5;
    static constexpr int max_files = 1048576 * 5;
    std::shared_ptr<spdlog::logger> _async_logger;
    SpotifyNetworkManager _manager;
    auto post() -> void;
    auto update() -> void;
};

}// namespace v1

}// namespace spotify

#endif

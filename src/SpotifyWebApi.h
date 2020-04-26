#ifndef SPOTIFYWEBAPI_SPOTIFYWEBAPI_H
#define SPOTIFYWEBAPI_SPOTIFYWEBAPI_H

#include <iostream>
#include <memory>
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>

class SpotifyWebApi {
public:
    void Initialize();
    void Authorize();

private:
    void post();
    void update();
    const std::string clientId = "636b0c0e79f34ce39855f58337583f84";
    const std::string clientSecret = "6c3d3d78017347bfaacf451a3789811e";
    //char clientSecretEncrypted[33] = "{.~)~)zu}|z~yz/+,,.+yx|,~zutu||(";
    std::shared_ptr<spdlog::logger> m_asyncLogger;
};

#endif//SPOTIFYWEBAPI_SPOTIFYWEBAPI_H

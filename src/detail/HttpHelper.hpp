//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP
#define SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP

#include "../AuthentificationToken.hpp"
//#include "../model/playlistdata.hpp"
#include "../model/modeldata.hpp"
#include "SpotifyNetworkManager.hpp"
#include <map>
//#include <stlab/concurrency/default_executor.hpp>
//#include <stlab/concurrency/future.hpp>
//#include <stlab/concurrency/utility.hpp>
#include <string>

namespace spotify {

inline namespace v1 {

class SpotifyNetworkManager;

class AuthentificationToken;

namespace detail {

class HttpHelper {
private:
    static spotify::SpotifyNetworkManager _manager;

public:
    static auto post1(std::string_view url, const std::map<std::string, std::string> &postData) -> std::string;
    static auto post2(std::string_view url, spotify::AuthentificationToken &token,
                      const std::map<std::string, std::string> &postData, bool include_bearer = true) -> std::string;
    static auto post3(std::string_view url, spotify::AuthentificationToken &token,
                      const spotify::model::playlistdata &pD, bool include_bearer = true) -> std::string;
    static auto get1(std::string_view url) -> std::string;
    static auto get2(std::string_view url, spotify::AuthentificationToken &token, bool include_bearer = true) -> std::string;
    static std::string put1(std::string_view url, AuthentificationToken &token,
                            const std::map<std::string, std::string> &postData, bool include_bearer);
    static std::string put2(std::string_view url, AuthentificationToken &token,
                            const model::playlistdata &pD, bool include_bearer);
    static std::string delete_(std::string_view url, AuthentificationToken &token, bool include_bearer);
};

}// namespace detail
}// namespace v1
}// namespace spotify

#endif

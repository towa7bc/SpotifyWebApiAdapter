//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP
#define SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP

#define STLAB_FUTURE_COROUTINE_SUPPORT

#include "../SpotifyNetworkManager.hpp"
#include <map>
//#include <stlab/concurrency/default_executor.hpp>
//#include <stlab/concurrency/future.hpp>
//#include <stlab/concurrency/utility.hpp>
#include <string>

namespace spotify {

inline namespace v1 {

namespace detail {

class HttpHelper {
private:
    static SpotifyNetworkManager _manager;

public:
    static auto post(std::string_view url, const std::map<std::string, std::string> &postData) -> std::string;
};

}// namespace detail
}// namespace v1
}// namespace spotify

#endif

//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP
#define SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP

#define STLAB_FUTURE_COROUTINE_SUPPORT

#include <map>
#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>
#include <stlab/concurrency/utility.hpp>
#include <string>

namespace spotify {

inline namespace v1 {

namespace detail {

class HttpHelper {
public:
    static auto post(std::string_view url, const std::map<std::string, std::string> &postData) -> stlab::future<std::string> {
        std::string s = "dhdheh";
        co_return s;
    }
};

}// namespace detail
}// namespace v1
}// namespace spotify

#endif

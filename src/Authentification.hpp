//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_AUTHENTIFICATION_HPP
#define SPOTIFYWEBAPIADAPTER_AUTHENTIFICATION_HPP

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 20
#endif

#define STLAB_FUTURE_COROUTINE_SUPPORT

#include "AuthentificationToken.hpp"
#include "detail/BaseModel.hpp"
#include "detail/HttpHelper.hpp"
#include "model/accesstoken.hpp"
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <map>
#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>
#include <stlab/concurrency/utility.hpp>
#include <string>

namespace spotify {

inline namespace v1 {

class AuthentificationToken;

class Authentification : public spotify::BaseModel {
    using date_time_t = boost::posix_time::ptime;
    using json_t = nlohmann::json;

public:
    static std::string _client_id;
    static std::string _client_secret;
    static std::string _redirect_uri;
    static auto getAccessToken(std::string_view code) -> spotify::AuthentificationToken;
};

}// namespace v1
}// namespace spotify

#endif

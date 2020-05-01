//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_AUTHENTIFICATION_HPP
#define SPOTIFYWEBAPIADAPTER_AUTHENTIFICATION_HPP

#include "AuthentificationToken.hpp"
#include "HttpHelper.hpp"
#include <map>
#include <string>

namespace spotify {

inline namespace v1 {

class Authentification {
    using date_time_t = boost::posix_time::ptime;
    using json_t = nlohmann::json;

public:
    static std::string _client_id;
    static std::string _client_secret;
    static std::string _redirect_uri;
    static auto getAccessToken(std::string_view code) -> stlab::future<AuthentificationToken> {
        AuthentificationToken auth_token;
        std::map<std::string, std::string> postData;
        postData["grant_type"] = "authorization_code";
        postData["code"] = code;
        postData["redirect_uri"] = _redirect_uri;
        postData["client_id"] = _client_id;
        postData["client_secret"] = _client_secret;
        auto json_s = co_await spotify::detail::HttpHelper::post("https://accounts.spotify.com/api/token", postData);
        auto json = json_t::parse(json_s);
        auth_token.setAccessToken(json["access_token"]);
        auth_token.setRefreshToken(json["refresh_token"]);
        auth_token.setTokenType(json["token_type"]);
        auth_token.setRefreshToken(json["refresh_token"]);
        date_time_t currentTime(boost::gregorian::day_clock::universal_day(), boost::posix_time::second_clock::universal_time().time_of_day());
        auth_token.setExpiresOn(currentTime + boost::posix_time::seconds(std::stoi(json["expires_in"])));
        co_return auth_token;
    }
};

}// namespace v1
}// namespace spotify

#endif

//
// Created by Michael Wittmann on 03/05/2020.
//

#include "Authentification.hpp"

namespace spotify {

inline namespace v1 {

/* static */ auto spotify::Authentification::get_access_token(std::string_view code)
        -> spotify::AuthentificationToken {
    AuthentificationToken auth_token;
    std::map<std::string, std::string> postData;
    postData["grant_type"] = "authorization_code";
    postData["code"] = code;
    postData["redirect_uri"] = _redirect_uri;
    postData["client_id"] = _client_id;
    postData["client_secret"] = _client_secret;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::post1,
                                     "https://accounts.spotify.com/api/token", postData)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<model::accesstoken>(); });
    auto access_token = stlab::blocking_get(local_future);
    auth_token.setAccessToken(access_token.access_token);
    auth_token.setRefreshToken(access_token.refresh_token);
    auth_token.setTokenType(access_token.token_type);
    date_time_t currentTime(boost::gregorian::day_clock::universal_day(),
                            boost::posix_time::second_clock::universal_time().time_of_day());
    auth_token.setExpiresOn(currentTime + boost::posix_time::seconds(access_token.expires_in));
    return auth_token;
}

}// namespace v1
}// namespace spotify
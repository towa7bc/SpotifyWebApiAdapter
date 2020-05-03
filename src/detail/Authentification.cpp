//
// Created by Michael Wittmann on 03/05/2020.
//

#include "Authentification.hpp"

/* static */ auto spotify::Authentification::getAccessToken(std::string_view code) -> spotify::AuthentificationToken {
    AuthentificationToken auth_token;
    std::map<std::string, std::string> postData;
    postData["grant_type"] = "authorization_code";
    postData["code"] = code;
    postData["redirect_uri"] = _redirect_uri;
    postData["client_id"] = _client_id;
    postData["client_secret"] = _client_secret;
    auto post_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::post, "https://accounts.spotify.com/api/token", postData);
    auto json_obj_future = post_future | ([](std::string s) { return json_t::parse(s); });
    auto json_obj = stlab::blocking_get(json_obj_future);
    auto access_token = json_obj.get<model::accesstoken>();// deserialize json object to accesstoken
    auth_token.setAccessToken(access_token.access_token);
    auth_token.setRefreshToken(access_token.refresh_token);
    auth_token.setTokenType(access_token.token_type);
    date_time_t currentTime(boost::gregorian::day_clock::universal_day(), boost::posix_time::second_clock::universal_time().time_of_day());
    auth_token.setExpiresOn(currentTime + boost::posix_time::seconds(access_token.expires_in));
    return auth_token;
}

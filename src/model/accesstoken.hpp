//
// Created by Michael Wittmann on 03/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_ACCESSTOKEN_HPP
#define SPOTIFYWEBAPIADAPTER_ACCESSTOKEN_HPP

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct accesstoken {
    std::string access_token;
    std::string token_type;
    int expires_in{0};
    std::string refresh_token;
};

void to_json(json &j, const accesstoken &token) {
    j = json{{"access_token", token.access_token},
             {"token_type", token.token_type},
             {"expires_in", token.expires_in},
             {"refresh_token", token.refresh_token}};
}

void from_json(const json &j, accesstoken &token) {
    j.at("access_token").get_to(token.access_token);
    j.at("token_type").get_to(token.token_type);
    j.at("expires_in").get_to(token.expires_in);
    j.at("refresh_token").get_to(token.refresh_token);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

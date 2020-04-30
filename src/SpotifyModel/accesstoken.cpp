//
// Created by Michael Wittmann on 30/04/2020.
//

#include "accesstoken.h"

auto spotify::model::accesstoken::to_poco() const -> AuthentificationToken {
    AuthentificationToken token;
    date_time_t currentTime(boost::gregorian::day_clock::universal_day(), boost::posix_time::second_clock::universal_time().time_of_day());
    token.setAccessToken(_access_token);
    token.setExpiresOn(currentTime + boost::posix_time::seconds(_expires_in));
    token.setTokenType(_token_type);
    token.setRefreshToken(_refresh_token);
    return token;
}

std::string_view spotify::model::accesstoken::getTokenType() const {
    return _token_type;
}

void spotify::model::accesstoken::setTokenType(std::string_view tokenType) {
    _token_type = tokenType;
}

std::string_view spotify::model::accesstoken::getAccessToken() const {
    return _access_token;
}

void spotify::model::accesstoken::setAccessToken(std::string_view accessToken) {
    _access_token = accessToken;
}

int spotify::model::accesstoken::getExpiresIn() const {
    return _expires_in;
}

void spotify::model::accesstoken::setExpiresIn(int expiresIn) {
    _expires_in = expiresIn;
}

std::string_view spotify::model::accesstoken::getRefreshToken() const {
    return _refresh_token;
}

void spotify::model::accesstoken::setRefreshToken(std::string_view refreshToken) {
    _refresh_token = refreshToken;
}

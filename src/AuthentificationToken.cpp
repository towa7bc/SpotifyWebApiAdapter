//
// Created by Michael Wittmann on 03/05/2020.
//

#include "AuthentificationToken.hpp"

auto spotify::AuthentificationToken::setMHasExpired(bool mHasExpired) -> void {
    _has_expired = mHasExpired;
}

auto spotify::AuthentificationToken::isMHasExpired() const -> bool {
    date_time_t currentTime(boost::gregorian::day_clock::universal_day(),
                            boost::posix_time::second_clock::universal_time().time_of_day());
    return currentTime > _expires_on;
}

auto spotify::AuthentificationToken::getMAccessToken() -> const std::string & {
    if (isMHasExpired()) {
        refresh();
    }
    return _access_token;
}

auto spotify::AuthentificationToken::setAccessToken(std::string_view mAccessToken) -> void {
    _access_token = mAccessToken;
}

auto spotify::AuthentificationToken::getMExpiresOn() const -> const boost::posix_time::ptime & {
    return _expires_on;
}

auto spotify::AuthentificationToken::setExpiresOn(const boost::posix_time::ptime &mExpiresOn)
        -> void {
    _expires_on = mExpiresOn;
}

auto spotify::AuthentificationToken::refresh() -> void {
    auto auth_token_future = stlab::async(stlab::default_executor, spotify::Authentification::get_access_token, _refresh_token);
    auto auth_token = stlab::blocking_get(auth_token_future);
    _access_token = auth_token._access_token;
    _refresh_token = auth_token._refresh_token;
    _token_type = auth_token._token_type;
    _has_expired = auth_token._has_expired;
    _expires_on = auth_token._expires_on;
}

void spotify::AuthentificationToken::setTokenType(std::string_view tokenType) {
    _token_type = tokenType;
}

void spotify::AuthentificationToken::setRefreshToken(std::string_view refreshToken) {
    _refresh_token = refreshToken;
}

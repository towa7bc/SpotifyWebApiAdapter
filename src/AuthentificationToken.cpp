//
// Created by Michael Wittmann on 15/04/2020.
//

#include "AuthentificationToken.h"

auto AuthentificationToken::getMAccessToken() -> const std::string & {
    if (isMHasExpired()) {
        refresh();
    }
    return _access_token;
}

auto AuthentificationToken::setMAccessToken(std::string_view mAccessToken) -> void {
    _access_token = mAccessToken;
}

auto AuthentificationToken::refresh() -> void {
}

auto AuthentificationToken::isMHasExpired() const -> bool {
    boost::posix_time::ptime currentTime(boost::gregorian::day_clock::universal_day(), boost::posix_time::second_clock::universal_time().time_of_day());
    return currentTime > _expires_on;
}

auto AuthentificationToken::setMHasExpired(bool mHasExpired) -> void {
    _has_expired = mHasExpired;
}

auto AuthentificationToken::getMExpiresOn() const -> const boost::posix_time::ptime & {
    return _expires_on;
}

auto AuthentificationToken::setMExpiresOn(const boost::posix_time::ptime &mExpiresOn) -> void {
    _expires_on = mExpiresOn;
}

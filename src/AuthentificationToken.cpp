//
// Created by Michael Wittmann on 15/04/2020.
//

#include "AuthentificationToken.h"

const std::string &AuthentificationToken::getMAccessToken() {
    if (isMHasExpired()) {
        refresh();
    }
    return m_accessToken;
}

void AuthentificationToken::setMAccessToken(std::string_view mAccessToken) {
    m_accessToken = mAccessToken;
}

void AuthentificationToken::refresh() {
}

bool AuthentificationToken::isMHasExpired() const {
    boost::posix_time::ptime currentTime(boost::gregorian::day_clock::universal_day(), boost::posix_time::second_clock::universal_time().time_of_day());
    return currentTime > m_ExpiresOn;
}

void AuthentificationToken::setMHasExpired(bool mHasExpired) {
    m_hasExpired = mHasExpired;
}

const boost::posix_time::ptime &AuthentificationToken::getMExpiresOn() const {
    return m_ExpiresOn;
}

void AuthentificationToken::setMExpiresOn(const boost::posix_time::ptime &mExpiresOn) {
    m_ExpiresOn = mExpiresOn;
}

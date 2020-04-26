//
// Created by Michael Wittmann on 15/04/2020.
//

#ifndef SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H
#define SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H

#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <nlohmann/json.hpp>
#include <string>

class AuthentificationToken {
private:
    std::string m_accessToken;
    std::string m_tokenType;
    boost::posix_time::ptime m_ExpiresOn;
    std::string m_refreshToken;
    bool m_hasExpired;
    nlohmann::json m_json;

public:
    void setMHasExpired(bool mHasExpired);
    bool isMHasExpired() const;
    const std::string &getMAccessToken();
    void setMAccessToken(const std::string &mAccessToken);
    const boost::posix_time::ptime &getMExpiresOn() const;
    void setMExpiresOn(const boost::posix_time::ptime &mExpiresOn);
    void refresh();
};


#endif//SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H

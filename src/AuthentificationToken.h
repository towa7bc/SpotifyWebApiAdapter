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
    std::string _access_token;
    std::string _token_type;
    boost::posix_time::ptime _expires_on;
    std::string _refresh_token;
    bool _has_expired;
    nlohmann::json _json;

public:
    auto setMHasExpired(bool mHasExpired) -> void;
    [[nodiscard]] auto isMHasExpired() const -> bool;
    auto getMAccessToken() -> const std::string &;
    auto setMAccessToken(std::string_view mAccessToken) -> void;
    [[nodiscard]] auto getMExpiresOn() const -> const boost::posix_time::ptime &;
    auto setMExpiresOn(const boost::posix_time::ptime &mExpiresOn) -> void;
    auto refresh() -> void;
};


#endif

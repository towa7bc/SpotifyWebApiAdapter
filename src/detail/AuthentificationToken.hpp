//
// Created by Michael Wittmann on 15/04/2020.
//

#ifndef SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H
#define SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H

#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace spotify {

inline namespace v1 {

class AuthentificationToken {
    using date_time_t = boost::posix_time::ptime;
    using json_t = nlohmann::json;

private:
    std::string _access_token;
    std::string _token_type;
    boost::posix_time::ptime _expires_on;
    std::string _refresh_token;
    bool _has_expired{false};
    json_t _json;

public:
    AuthentificationToken() = default;

    auto setMHasExpired(bool mHasExpired) -> void {
        _has_expired = mHasExpired;
    }

    [[nodiscard]] auto isMHasExpired() const -> bool {
        date_time_t currentTime(boost::gregorian::day_clock::universal_day(), boost::posix_time::second_clock::universal_time().time_of_day());
        return currentTime > _expires_on;
    }

    auto getMAccessToken() -> const std::string & {
        if (isMHasExpired()) {
            refresh();
        }
        return _access_token;
    }

    auto setAccessToken(std::string_view mAccessToken) -> void {
        _access_token = mAccessToken;
    }

    [[nodiscard]] auto getMExpiresOn() const -> const boost::posix_time::ptime & {
        return _expires_on;
    }

    auto setExpiresOn(const boost::posix_time::ptime &mExpiresOn) -> void {
        _expires_on = mExpiresOn;
    }

    auto refresh() -> void {
    }

    void setTokenType(std::string_view tokenType) {
        _token_type = tokenType;
    }

    void setRefreshToken(std::string_view refreshToken) {
        _refresh_token = refreshToken;
    }
};

}// namespace v1

}// namespace spotify

#endif

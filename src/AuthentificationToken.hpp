//
// Created by Michael Wittmann on 15/04/2020.
//

#ifndef SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H
#define SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H

#include "Authentification.hpp"
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
    AuthentificationToken(const AuthentificationToken &) = default;
    ~AuthentificationToken() = default;
    AuthentificationToken &operator=(const AuthentificationToken &) = default;
    AuthentificationToken &operator=(AuthentificationToken &&) = default;
    AuthentificationToken(AuthentificationToken &&) noexcept = default;
    auto setMHasExpired(bool mHasExpired) -> void;
    [[nodiscard]] auto isMHasExpired() const -> bool;
    auto getMAccessToken() -> const std::string &;
    auto setAccessToken(std::string_view mAccessToken) -> void;
    [[nodiscard]] auto getMExpiresOn() const -> const boost::posix_time::ptime &;
    auto setExpiresOn(const boost::posix_time::ptime &mExpiresOn) -> void;
    auto refresh() -> void;
    void setTokenType(std::string_view tokenType);
    void setRefreshToken(std::string_view refreshToken);
};

}// namespace v1

}// namespace spotify

#endif

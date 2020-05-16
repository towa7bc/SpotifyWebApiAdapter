//
// Created by Michael Wittmann on 15/04/2020.
//

#ifndef SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H
#define SPOTIFYWEBAPI_AUTHENTIFICATIONTOKEN_H

#include <boost/date_time/posix_time/ptime.hpp>  // for ptime
#include <nlohmann/json.hpp>                     // for basic_json, json
#include <string>                                // for basic_string
#include <string_view>                           // for string_view

#include "model/modeldata.hpp"  // for json

namespace spotify::inline v1 {

class AuthenticationToken {
  using date_time_t = boost::posix_time::ptime;
  using json_t = nlohmann::json;

 private:
  mutable std::string _access_token;
  mutable std::string _token_type;
  mutable boost::posix_time::ptime _expires_on;
  mutable std::string _refresh_token;
  mutable bool _has_expired{false};
  json_t _json;

 public:
  AuthenticationToken() = default;
  AuthenticationToken(const AuthenticationToken &) = default;
  ~AuthenticationToken() = default;
  AuthenticationToken &operator=(const AuthenticationToken &) = default;
  AuthenticationToken &operator=(AuthenticationToken &&) noexcept = default;
  AuthenticationToken(AuthenticationToken &&) noexcept = default;
  auto setMHasExpired(bool mHasExpired) -> void;
  [[nodiscard]] auto isMHasExpired() const -> bool;
  auto getMAccessToken() const -> const std::string &;
  auto setAccessToken(std::string_view mAccessToken) -> void;
  [[nodiscard]] auto getMExpiresOn() const -> const boost::posix_time::ptime &;
  auto setExpiresOn(const boost::posix_time::ptime &mExpiresOn) -> void;
  auto refresh() const -> void;
  void setTokenType(std::string_view tokenType);
  void setRefreshToken(std::string_view refreshToken);
};

}  // namespace spotify::inline v1

#endif

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

namespace spotify {
inline namespace v1 {

class AuthenticationToken {
  using date_time_t = boost::posix_time::ptime;
  using json_t = nlohmann::json;

 private:
  mutable std::string access_token_;
  mutable std::string token_type_;
  mutable boost::posix_time::ptime expires_on_;
  mutable std::string refresh_token_;
  mutable bool has_expired_{false};
  json_t json_;

 public:
  AuthenticationToken() = default;
  AuthenticationToken(const AuthenticationToken &) = default;
  ~AuthenticationToken() = default;
  AuthenticationToken &operator=(const AuthenticationToken &) = default;
  AuthenticationToken &operator=(AuthenticationToken &&) noexcept = default;
  AuthenticationToken(AuthenticationToken &&) noexcept = default;
  auto SetHasExpired(bool mHasExpired) -> void;
  [[nodiscard]] auto hasExpired() const -> bool;
  auto getAccessToken() const -> const std::string &;
  auto setAccessToken(std::string_view mAccessToken) -> void;
  [[nodiscard]] auto getExpiresOn() const -> const boost::posix_time::ptime &;
  auto setExpiresOn(const boost::posix_time::ptime &mExpiresOn) -> void;
  auto Refresh() const -> void;
  void SetTokenType(std::string_view tokenType);
  void SetRefreshToken(std::string_view refreshToken);
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

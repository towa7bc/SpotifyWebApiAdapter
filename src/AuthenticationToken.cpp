//
// Created by Michael Wittmann on 03/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 20
#endif

#include "AuthenticationToken.hpp"

#include <boost/date_time/gregorian/gregorian_types.hpp>    // for day_clock
#include <boost/date_time/posix_time/posix_time_types.hpp>  // for second_clock
#include <boost/operators.hpp>                              // for operator>
#include <functional>                                       // for __base
#include <stlab/concurrency/default_executor.hpp>           // for executor_...
#include <stlab/concurrency/future.hpp>                     // for async
#include <stlab/concurrency/utility.hpp>                    // for blocking_get

#include "Authentication.hpp"  // for Authentic...

namespace spotify::inline v1 {

auto AuthenticationToken::SetHasExpired(bool mHasExpired) -> void {
  has_expired_ = mHasExpired;
}

auto AuthenticationToken::HasExpired() const -> bool {
  date_time_t currentTime(
      boost::gregorian::day_clock::universal_day(),
      boost::posix_time::second_clock::universal_time().time_of_day());
  return currentTime > expires_on_;
}

auto AuthenticationToken::GetAccessToken() const -> const std::string & {
  if (HasExpired()) {
    Refresh();
  }
  return access_token_;
}

auto AuthenticationToken::SetAccessToken(std::string_view mAccessToken)
    -> void {
  access_token_ = mAccessToken;
}

auto AuthenticationToken::GetExpiresOn() const
    -> const boost::posix_time::ptime & {
  return expires_on_;
}

auto AuthenticationToken::SetExpiresOn(
    const boost::posix_time::ptime &mExpiresOn) -> void {
  expires_on_ = mExpiresOn;
}

auto AuthenticationToken::Refresh() const -> void {
  auto auth_token_future = stlab::async(
      stlab::default_executor, Authentication::GetAccessToken, refresh_token_);
  auto auth_token = stlab::blocking_get(auth_token_future);
  access_token_ = auth_token.access_token_;
  refresh_token_ = auth_token.refresh_token_;
  token_type_ = auth_token.token_type_;
  has_expired_ = auth_token.has_expired_;
  expires_on_ = auth_token.expires_on_;
}

void AuthenticationToken::SetTokenType(std::string_view tokenType) {
  token_type_ = tokenType;
}

void AuthenticationToken::SetRefreshToken(std::string_view refreshToken) {
  refresh_token_ = refreshToken;
}

}  // namespace spotify::inline v1
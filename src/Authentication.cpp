//
// Created by Michael Wittmann on 03/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 20
#endif

#include "Authentication.hpp"

#include <boost/date_time/gregorian/gregorian_types.hpp>       // for day_clock
#include <boost/date_time/posix_time/posix_time_duration.hpp>  // for seconds
#include <boost/date_time/posix_time/posix_time_types.hpp>     // for second...
#include <map>                                                 // for map
#include <memory>                                              // for shared...
#include <stlab/concurrency/default_executor.hpp>              // for execut...
#include <stlab/concurrency/future.hpp>                        // for async
#include <stlab/concurrency/utility.hpp>                       // for blocki...
#include <string>                                              // for basic_...

#include "AuthenticationToken.hpp"  // for Authen...
#include "detail/HttpHelper.hpp"    // for HttpHe...
#include "detail/Log.hpp"           // for Log

namespace spotify::inline v1 {

/* static */ auto Authentication::get_access_token(std::string_view code)
    -> AuthenticationToken {
  if (!Log::logger()) {
    Log::init();
  }
  AuthenticationToken auth_token;
  std::map<std::string, std::string> postData;
  postData["grant_type"] = "authorization_code";
  postData["code"] = code;
  postData["redirect_uri"] = _redirect_uri;
  postData["client_id"] = _client_id;
  postData["client_secret"] = _client_secret;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::post1,
                   "https://accounts.spotify.com/api/token", postData) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::accesstoken>(); });
  auto access_token = stlab::blocking_get(local_future);
  auth_token.setAccessToken(access_token.access_token);
  auth_token.setRefreshToken(access_token.refresh_token);
  auth_token.setTokenType(access_token.token_type);
  date_time_t currentTime(
      boost::gregorian::day_clock::universal_day(),
      boost::posix_time::second_clock::universal_time().time_of_day());
  auth_token.setExpiresOn(currentTime +
                          boost::posix_time::seconds(access_token.expires_in));
  return auth_token;
}

void Authentication::initialize_spotify() { Log::init(); }

}  // namespace spotify::inline v1

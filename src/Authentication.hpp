//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_AUTHENTICATION_HPP
#define SPOTIFYWEBAPIADAPTER_AUTHENTICATION_HPP

#define STLAB_FUTURE_COROUTINE_SUPPORT

#include <boost/date_time/posix_time/ptime.hpp>  // for ptime
#include <nlohmann/json.hpp>                     // for json
#include <string>                                // for string
#include <string_view>                           // for string_view

#include "detail/BaseModel.hpp"  // for BaseModel
#include "model/modeldata.hpp"   // for json
namespace spotify::inline v1 {
class AuthenticationToken;
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

class Authentication : public BaseModel {
  using date_time_t = boost::posix_time::ptime;
  using json_t = nlohmann::json;

 public:
  Authentication() = delete;
  Authentication(const Authentication &) = delete;
  ~Authentication() override = default;
  Authentication &operator=(const Authentication &) = delete;
  Authentication &operator=(Authentication &&) noexcept = delete;
  Authentication(Authentication &&) noexcept = delete;
  static std::string _client_id;
  static std::string _client_secret;
  static std::string _redirect_uri;
  static auto get_access_token(std::string_view code) -> AuthenticationToken;
  static void initialize_spotify();
};

}  // namespace spotify::inline v1

#endif

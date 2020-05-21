//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP
#define SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP

#include <map>          // for map
#include <string>       // for string
#include <string_view>  // for string_view

#include "../model/modeldata.hpp"
namespace spotify {
inline namespace v1 {
class AuthenticationToken;
class SpotifyNetworkManager;
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {
namespace detail {

class HttpHelper {
 private:
  static SpotifyNetworkManager manager_;

 public:
  static auto Post1(std::string_view url,
                    const std::map<std::string, std::string> &postData)
      -> std::string;
  static auto Post2(std::string_view url, const AuthenticationToken &token,
                    const std::map<std::string, std::string> &postData,
                    bool include_bearer) -> std::string;
  static auto Post3(std::string_view url, const AuthenticationToken &token,
                    const model::playlistdata &pD, bool include_bearer = true)
      -> std::string;
  static auto Get1(std::string_view url) -> std::string;
  static auto Get2(std::string_view url, const AuthenticationToken &token,
                   bool include_bearer) -> std::string;
  static std::string Put1(std::string_view url,
                          const AuthenticationToken &token,
                          const std::map<std::string, std::string> &postData,
                          bool include_bearer);
  static std::string Put2(std::string_view url,
                          const AuthenticationToken &token,
                          const model::playlistdata &pD, bool include_bearer);
  static std::string Delete(std::string_view url,
                            const AuthenticationToken &token,
                            bool include_bearer);
};

}  // namespace detail
}  // namespace spotify::inline v1
}  // namespace spotify

#endif

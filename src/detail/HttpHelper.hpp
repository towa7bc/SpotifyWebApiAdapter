//
// Created by Michael Wittmann on 01/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP
#define SPOTIFYWEBAPIADAPTER_HTTPHELPER_HPP

#include <map>          // for map
#include <string>       // for string
#include <string_view>  // for string_view

#include "../model/modeldata.hpp"
namespace spotify::inline v1 {
class AuthenticationToken;
class SpotifyNetworkManager;
}  // namespace spotify::inline v1

namespace spotify::inline v1 {
namespace detail {

class HttpHelper {
 private:
  static SpotifyNetworkManager _manager;

 public:
  static auto post1(std::string_view url,
                    const std::map<std::string, std::string> &postData)
      -> std::string;
  static auto post2(std::string_view url, const AuthenticationToken &token,
                    const std::map<std::string, std::string> &postData,
                    bool include_bearer) -> std::string;
  static auto post3(std::string_view url, const AuthenticationToken &token,
                    const model::playlistdata &pD, bool include_bearer = true)
      -> std::string;
  static auto get1(std::string_view url) -> std::string;
  static auto get2(std::string_view url, const AuthenticationToken &token,
                   bool include_bearer) -> std::string;
  static std::string put1(std::string_view url,
                          const AuthenticationToken &token,
                          const std::map<std::string, std::string> &postData,
                          bool include_bearer);
  static std::string put2(std::string_view url,
                          const AuthenticationToken &token,
                          const model::playlistdata &pD, bool include_bearer);
  static std::string delete_(std::string_view url,
                             const AuthenticationToken &token,
                             bool include_bearer);
};

}  // namespace detail
}  // namespace spotify::inline v1

#endif

//
// Created by Michael Wittmann on 03/05/2020.
//

#include "HttpHelper.hpp"

#include <nlohmann/json.hpp>
#include <string>

#include "SpotifyNetworkManager.hpp"

namespace spotify::inline v1 {
namespace detail {

/* static */ auto detail::HttpHelper::get1(std::string_view url)
    -> std::string {
  _manager.perform_get_request(url);
  return _manager.get_reply();
}

/* static */ auto detail::HttpHelper::get2(std::string_view url,
                                           const AuthenticationToken &token,
                                           bool include_bearer) -> std::string {
  _manager.perform_get_request(url, token, include_bearer);
  return _manager.get_reply();
}

/* static */ auto detail::HttpHelper::post1(
    std::string_view url, const std::map<std::string, std::string> &postData)
    -> std::string {
  _manager.perform_post_request(url, postData);
  return _manager.get_reply();
}

/* static */ auto detail::HttpHelper::post2(
    std::string_view url, const AuthenticationToken &token,
    const std::map<std::string, std::string> &postData, bool include_bearer)
    -> std::string {
  _manager.perform_post_request(url, token, postData, include_bearer);
  return _manager.get_reply();
}

/* static */ auto detail::HttpHelper::post3(std::string_view url,
                                            const AuthenticationToken &token,
                                            const model::playlistdata &pD,
                                            bool include_bearer)
    -> std::string {
  nlohmann::json j = pD;
  _manager.perform_post_request(url, token, j.dump(), include_bearer);
  return _manager.get_reply();
}

/* static */ auto detail::HttpHelper::put1(
    std::string_view url, const AuthenticationToken &token,
    const std::map<std::string, std::string> &postData, bool include_bearer)
    -> std::string {
  _manager.perform_put_request(url, token, postData, include_bearer);
  return _manager.get_reply();
}

/* static */ auto detail::HttpHelper::put2(std::string_view url,
                                           const AuthenticationToken &token,
                                           const model::playlistdata &pD,
                                           bool include_bearer) -> std::string {
  nlohmann::json j = pD;
  _manager.perform_put_request(url, token, j.dump(), include_bearer);
  return _manager.get_reply();
}

/* static */ auto detail::HttpHelper::delete_(std::string_view url,
                                              const AuthenticationToken &token,
                                              bool include_bearer)
    -> std::string {
  _manager.perform_delete_request(url, token, include_bearer);
  return _manager.get_reply();
}

}  // namespace detail
}  // namespace spotify::inline v1
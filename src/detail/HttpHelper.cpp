//
// Created by Michael Wittmann on 03/05/2020.
//

#include "HttpHelper.hpp"

#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "SpotifyNetworkManager.hpp"

namespace spotify {
inline namespace v1 {
namespace detail {

/* static */ auto detail::HttpHelper::Get1(std::string_view url)
    -> std::string {
  manager_.perform_get_request(url);
  return manager_.get_reply();
}

/* static */ auto detail::HttpHelper::Get2(std::string_view url,
                                           const AuthenticationToken &token,
                                           bool include_bearer) -> std::string {
  manager_.perform_get_request(url, token, include_bearer);
  return manager_.get_reply();
}

/* static */ auto detail::HttpHelper::Post1(
    std::string_view url,
    const std::unordered_map<std::string, std::string> &postData)
    -> std::string {
  manager_.perform_post_request(url, postData);
  return manager_.get_reply();
}

/* static */ auto detail::HttpHelper::Post2(
    std::string_view url, const AuthenticationToken &token,
    const std::unordered_map<std::string, std::string> &postData,
    bool include_bearer) -> std::string {
  manager_.perform_post_request(url, token, postData, include_bearer);
  return manager_.get_reply();
}

/* static */ auto detail::HttpHelper::Post3(std::string_view url,
                                            const AuthenticationToken &token,
                                            const model::playlistdata &pD,
                                            bool include_bearer)
    -> std::string {
  nlohmann::json j = pD;
  manager_.perform_post_request(url, token, j.dump(), include_bearer);
  return manager_.get_reply();
}

/* static */ auto detail::HttpHelper::Put1(
    std::string_view url, const AuthenticationToken &token,
    const std::unordered_map<std::string, std::string> &postData,
    bool include_bearer) -> std::string {
  manager_.perform_put_request(url, token, postData, include_bearer);
  return manager_.get_reply();
}

/* static */ auto detail::HttpHelper::Put2(std::string_view url,
                                           const AuthenticationToken &token,
                                           const model::playlistdata &pD,
                                           bool include_bearer) -> std::string {
  nlohmann::json j = pD;
  manager_.perform_put_request(url, token, j.dump(), include_bearer);
  return manager_.get_reply();
}

/* static */ auto detail::HttpHelper::Delete(std::string_view url,
                                             const AuthenticationToken &token,
                                             bool include_bearer)
    -> std::string {
  manager_.perform_delete_request(url, token, include_bearer);
  return manager_.get_reply();
}

}  // namespace detail
}  // namespace spotify::inline v1
}  // namespace spotify
//
// Created by Michael Wittmann on 07/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 20
#endif

#include "User.hpp"

#include <functional>                              // for __base
#include <stlab/concurrency/default_executor.hpp>  // for executor_type, def...
#include <stlab/concurrency/future.hpp>            // for async, future
#include <stlab/concurrency/utility.hpp>           // for blocking_get
#include <string>                                  // for basic_string, oper...
#include <type_traits>                             // for move

#include "Page.hpp"               // for Page
#include "Playlist.hpp"           // for Playlist
#include "Track.hpp"              // for Track
#include "detail/HttpHelper.hpp"  // for HttpHelper
namespace spotify::inline v1 {
class AuthenticationToken;
}

namespace spotify::inline v1 {

User::User(const model::user &t_user)
    : country_(t_user.country),
      displayName_(t_user.display_name),
      external_url_(t_user.external_urls.at(0)),
      href_(t_user.href),
      id_(t_user.id),
      product_(t_user.product),
      type_(t_user.type),
      uri_(t_user.uri) {
  images_.reserve(t_user.images.capacity());
  for (const auto &imag : t_user.images) {
    Image image(imag);
    images_.push_back(std::move(image));
  }
}

User::User(model::user &&t_user) noexcept
    : country_(std::move(t_user.country)),
      displayName_(std::move(t_user.display_name)),
      external_url_(std::move(t_user.external_urls.at(0))),
      href_(std::move(t_user.href)),
      id_(std::move(t_user.id)),
      product_(std::move(t_user.product)),
      type_(std::move(t_user.type)),
      uri_(std::move(t_user.uri)) {
  images_.reserve(t_user.images.capacity());
  for (auto &imag : t_user.images) {
    Image image(std::move(imag));
    images_.push_back(std::move(image));
  }
}

User User::GetUser(std::string_view user_id) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   "https://api.spotify.com/v1/users/" + std::string(user_id)) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::user>(); });
  auto local_obj = stlab::blocking_get(local_future);
  User user(local_obj);
  return user;
}

User User::GetCurrentUserProfile(const AuthenticationToken &token) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   "https://api.spotify.com/v1/me", token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::user>(); });
  auto local_obj = stlab::blocking_get(local_future);
  User user(local_obj);
  return user;
}

Page<Playlist> User::GetPlaylists(const AuthenticationToken &token) const {
  return Playlist::GetUsersPlaylists(id_, token);
}

Page<Track> User::GetUserSavedTracks(const AuthenticationToken &token,
                                     int limit, int offset) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   "https://api.spotify.com/v1/me/tracks?limit=" +
                       std::to_string(limit) +
                       "&offset=" + std::to_string(offset),
                   token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::savedtrack>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Track> track(local_obj);
  return track;
}

Page<Track> User::GetSavedTracks(const AuthenticationToken &token, int limit,
                                 int offset) {
  return GetUserSavedTracks(token, limit, offset);
}

void User::SaveTracks(const std::vector<std::string> &ids,
                      const AuthenticationToken &token) {
  auto uri = CreateCommaSeparatedList(ids);
  bool include_bearer{true};
  model::playlistdata pd;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Put2,
                   "https://api.spotify.com/v1/me/tracks?ids=" + uri, token, pd,
                   include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

void User::DeleteTracks(const std::vector<std::string> &ids,
                        const AuthenticationToken &token) {
  auto uri = CreateCommaSeparatedList(ids);
  bool include_bearer{true};
  auto local_future = stlab::async(
      stlab::default_executor, detail::HttpHelper::Delete,
      "https://api.spotify.com/v1/me/tracks?ids=" + uri, token, include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

bool User::AreSaved(const std::vector<std::string> &ids,
                    const AuthenticationToken &token) {
  auto uri = CreateCommaSeparatedList(ids);
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   "https://api.spotify.com/v1/me/tracks/contains?ids=" + uri,
                   token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); });
  auto local_obj = stlab::blocking_get(local_future);
  auto bool_string = local_obj.dump();
  bool_string = StrToUpper(bool_string);
  return bool_string.find("TRUE") != std::string::npos;
}

bool User::IsSaved(std::string_view id, const AuthenticationToken &token) {
  std::vector<std::string> ids{std::string(id)};
  return AreSaved(ids, token);
}

}  // namespace spotify::inline v1

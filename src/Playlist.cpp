//
// Created by Michael Wittmann on 08/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 20
#endif

#include "Playlist.hpp"

#include <algorithm>                               // for transform
#include <functional>                              // for __base
#include <map>                                     // for map
#include <stlab/concurrency/default_executor.hpp>  // for executor_type, def...
#include <stlab/concurrency/future.hpp>            // for async, future
#include <stlab/concurrency/utility.hpp>           // for blocking_get
#include <string>                                  // for basic_string, oper...
#include <type_traits>                             // for move

#include "Browse.hpp"             // for Browse
#include "Page.hpp"               // for Page
#include "PlaylistTrack.hpp"      // for PlaylistTrack
#include "Track.hpp"              // for Track
#include "User.hpp"               // for User
#include "detail/HttpHelper.hpp"  // for HttpHelper

namespace spotify::inline v1 {

Playlist::Playlist(const model::playlist &pl)
    : collaborative_(pl.is_collaborative),
      description_(pl.description),
      external_url_(pl.external_urls.at(0)),
      followers_(pl.followers_),
      href_(pl.href),
      id_(pl.id),
      name_(pl.name),
      owner_(pl.owner),
      public_(pl.is_public),
      tracks_(pl.tracks),
      type_(pl.type),
      uri_(pl.uri) {
  images_.reserve(pl.images.capacity());
  for (const auto &item : pl.images) {
    Image image(item);
    images_.push_back(std::move(image));
  }
}

Playlist::Playlist(model::playlist &&pl) noexcept
    : collaborative_(pl.is_collaborative),
      description_(std::move(pl.description)),
      external_url_(std::move(pl.external_urls.at(0))),
      followers_(pl.followers_),
      href_(std::move(pl.href)),
      id_(std::move(pl.id)),
      name_(std::move(pl.name)),
      owner_(pl.owner),
      public_(pl.is_public),
      tracks_(pl.tracks),
      type_(std::move(pl.type)),
      uri_(std::move(pl.uri)) {
  images_.reserve(pl.images.capacity());
  for (auto &item : pl.images) {
    Image image(std::move(item));
    images_.push_back(std::move(image));
  }
}

Page<Playlist> Playlist::GetUsersPlaylists(std::string_view user_id,
                                           const AuthenticationToken &token) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists",
                   token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::playlist>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Playlist> play_list(local_obj);
  return play_list;
}

Page<Playlist> Playlist::GetUsersPlaylists(const User &user,
                                           const AuthenticationToken &token) {
  return GetUsersPlaylists(user.id_, token);
}

Page<Playlist> Playlist::GetPlaylist(std::string_view user_id,
                                     std::string_view playlist_id,
                                     const AuthenticationToken &token) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists/" + std::string(playlist_id),
                   token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::playlist>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Playlist> play_list(local_obj);
  return play_list;
}

Page<Playlist> Playlist::GetPlaylist(const User &user,
                                     std::string_view playlist_id,
                                     const AuthenticationToken &token) {
  return GetPlaylist(user.id_, playlist_id, token);
}

Page<PlaylistTrack> Playlist::GetPlaylistTracks(
    std::string_view user_id, std::string_view playlist_id,
    const AuthenticationToken &token) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists/" + std::string(playlist_id) + "/tracks",
                   token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) {
        return j.get<model::page<model::playlisttrack>>();
      });
  auto local_obj = stlab::blocking_get(local_future);
  Page<PlaylistTrack> play_list(local_obj);
  return play_list;
}

Page<PlaylistTrack> Playlist::GetPlaylistTracks(
    const AuthenticationToken &token) const {
  return GetPlaylistTracks(owner_.id_, id_, token);
}

void Playlist::AddTrack(const Track &track, AuthenticationToken &token) const {
  bool include_bearer{true};
  std::map<std::string, std::string> d;
  auto local_future = stlab::async(
      stlab::default_executor, detail::HttpHelper::Post2,
      "https://api.spotify.com/v1/users/" + std::string(owner_.id_) +
          "/playlists/" + std::string(id_) + "/tracks?uris=" + track.uri_,
      token, d, include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

void Playlist::AddTracks(const std::vector<Track> &track_uris,
                         AuthenticationToken &token) const {
  std::vector<std::string> uris;
  std::transform(track_uris.begin(), track_uris.end(), uris.begin(),
                 [](const Track &track) -> std::string { return track.uri_; });

  bool include_bearer{true};
  std::map<std::string, std::string> d;
  auto local_future = stlab::async(
      stlab::default_executor, detail::HttpHelper::Post2,
      "https://api.spotify.com/v1/users/" + std::string(owner_.id_) +
          "/playlists/" + std::string(id_) +
          "/tracks?uris=" + CreateCommaSeparatedList(uris),
      token, d, include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

Playlist Playlist::CreatePlaylist(std::string_view user_id,
                                  std::string_view name, bool is_public,
                                  const AuthenticationToken &token) {
  bool include_bearer{true};
  model::playlistdata pd;
  pd.name = name;
  pd.is_public = is_public;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Post3,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists",
                   token, pd, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::playlist>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Playlist playlist(local_obj);
  return playlist;
}

void Playlist::UpdateUsersPlaylist(std::string_view user_id,
                                   std::string_view playlist_id,
                                   std::string_view name, bool is_public,
                                   const AuthenticationToken &token) {
  bool include_bearer{true};
  model::playlistdata pd;
  pd.name = name;
  pd.is_public = is_public;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Put2,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists/" + std::string(playlist_id),
                   token, pd, include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

void Playlist::UpdateUsersPlaylist(std::string_view name, bool is_public,
                                   const AuthenticationToken &token) const {
  UpdateUsersPlaylist(owner_.id_, id_, name, is_public, token);
}

Page<Playlist> Playlist::GetFeaturedPlaylists(const AuthenticationToken &token,
                                              std::string_view locale,
                                              std::string_view country,
                                              std::string_view timestamp,
                                              int limit, int offset) {
  return Browse::GetFeaturedPlaylists(token, locale, country, timestamp, limit,
                                      offset);
}

}  // namespace spotify::inline v1

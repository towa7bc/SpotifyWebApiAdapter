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
    : _collaborative(pl.is_collaborative),
      _description(pl.description),
      _external_url(pl.external_urls.at(0)),
      _followers(pl.followers_),
      _href(pl.href),
      _id(pl.id),
      _name(pl.name),
      _owner(pl.owner),
      _public(pl.is_public),
      _tracks(pl.tracks),
      _type(pl.type),
      _uri(pl.uri) {
  _images.reserve(pl.images.capacity());
  for (const auto &item : pl.images) {
    Image image(item);
    _images.push_back(std::move(image));
  }
}

Playlist::Playlist(model::playlist &&pl) noexcept
    : _collaborative(pl.is_collaborative),
      _description(std::move(pl.description)),
      _external_url(std::move(pl.external_urls.at(0))),
      _followers(pl.followers_),
      _href(std::move(pl.href)),
      _id(std::move(pl.id)),
      _name(std::move(pl.name)),
      _owner(pl.owner),
      _public(pl.is_public),
      _tracks(pl.tracks),
      _type(std::move(pl.type)),
      _uri(std::move(pl.uri)) {
  _images.reserve(pl.images.capacity());
  for (auto &item : pl.images) {
    Image image(std::move(item));
    _images.push_back(std::move(image));
  }
}

Page<Playlist> Playlist::get_users_playlists(std::string_view user_id,
                                             const AuthenticationToken &token) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get2,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists",
                   token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::playlist>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Playlist> play_list(local_obj);
  return play_list;
}

Page<Playlist> Playlist::get_users_playlists(const User &user,
                                             const AuthenticationToken &token) {
  return get_users_playlists(user._id, token);
}

Page<Playlist> Playlist::get_playlist(std::string_view user_id,
                                      std::string_view playlist_id,
                                      const AuthenticationToken &token) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get2,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists/" + std::string(playlist_id),
                   token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::playlist>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Playlist> play_list(local_obj);
  return play_list;
}

Page<Playlist> Playlist::get_playlist(const User &user,
                                      std::string_view playlist_id,
                                      const AuthenticationToken &token) {
  return get_playlist(user._id, playlist_id, token);
}

Page<PlaylistTrack> Playlist::get_playlist_tracks(
    std::string_view user_id, std::string_view playlist_id,
    const AuthenticationToken &token) {
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get2,
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

Page<PlaylistTrack> Playlist::get_playlist_tracks(
    const AuthenticationToken &token) const {
  return get_playlist_tracks(_owner._id, _id, token);
}

void Playlist::add_track(const Track &track, AuthenticationToken &token) const {
  bool include_bearer{true};
  std::map<std::string, std::string> d;
  auto local_future = stlab::async(
      stlab::default_executor, detail::HttpHelper::post2,
      "https://api.spotify.com/v1/users/" + std::string(_owner._id) +
          "/playlists/" + std::string(_id) + "/tracks?uris=" + track.uri,
      token, d, include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

void Playlist::add_tracks(const std::vector<Track> &track_uris,
                          AuthenticationToken &token) const {
  std::vector<std::string> uris;
  std::transform(track_uris.begin(), track_uris.end(), uris.begin(),
                 [](const Track &track) -> std::string { return track.uri; });

  bool include_bearer{true};
  std::map<std::string, std::string> d;
  auto local_future = stlab::async(
      stlab::default_executor, detail::HttpHelper::post2,
      "https://api.spotify.com/v1/users/" + std::string(_owner._id) +
          "/playlists/" + std::string(_id) +
          "/tracks?uris=" + create_comma_separated_List(uris),
      token, d, include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

Playlist Playlist::create_playlist(std::string_view user_id,
                                   std::string_view name, bool is_public,
                                   const AuthenticationToken &token) {
  bool include_bearer{true};
  model::playlistdata pd;
  pd.name = name;
  pd.is_public = is_public;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::post3,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists",
                   token, pd, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::playlist>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Playlist playlist(local_obj);
  return playlist;
}

void Playlist::update_users_playlist(std::string_view user_id,
                                     std::string_view playlist_id,
                                     std::string_view name, bool is_public,
                                     const AuthenticationToken &token) {
  bool include_bearer{true};
  model::playlistdata pd;
  pd.name = name;
  pd.is_public = is_public;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::put2,
                   "https://api.spotify.com/v1/users/" + std::string(user_id) +
                       "/playlists/" + std::string(playlist_id),
                   token, pd, include_bearer);
  auto local_obj = stlab::blocking_get(local_future);
}

void Playlist::update_users_playlist(std::string_view name, bool is_public,
                                     const AuthenticationToken &token) const {
  update_users_playlist(_owner._id, _id, name, is_public, token);
}

Page<Playlist> Playlist::get_featured_playlists(
    const AuthenticationToken &token, std::string_view locale,
    std::string_view country, std::string_view timestamp, int limit,
    int offset) {
  return Browse::get_featured_playlists(token, locale, country, timestamp,
                                        limit, offset);
}

}  // namespace spotify::inline v1

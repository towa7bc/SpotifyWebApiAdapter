//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Playlist.hpp"
#include "Browse.hpp"
#include <algorithm>

namespace spotify {

inline namespace v1 {

spotify::Playlist::Playlist(const spotify::model::playlist &pl) : _collaborative(pl.is_collaborative),
                                                                  _description(pl.description),
                                                                  _external_url(pl.external_urls.at(0)),
                                                                  _followers(pl.followers_),
                                                                  _href(pl.href),
                                                                  _id(pl.id),
                                                                  _name(pl.name),
                                                                  _owner(std::make_shared<spotify::User>(pl.owner)),
                                                                  _public(pl.is_public),
                                                                  _tracks(std::make_shared<spotify::Page<spotify::PlaylistTrack>>(pl.tracks)),
                                                                  _type(pl.type),
                                                                  _uri(pl.uri) {
    _images.reserve(pl.images.capacity());
    for (const auto &item : pl.images) {
        spotify::Image image(item);
        _images.push_back(std::move(image));
    }
}

spotify::Page<spotify::Playlist> spotify::Playlist::get_users_playlists(std::string_view user_id, const spotify::AuthentificationToken &token) {
    bool include_bearer{true};
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get2,
                                     "https://api.spotify.com/v1/users/" + std::string(user_id) + "/playlists", token, include_bearer)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::page<spotify::model::playlist>>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Page<spotify::Playlist> play_list(local_obj);
    return play_list;
}

spotify::Page<spotify::Playlist> spotify::Playlist::get_users_playlists(const spotify::User &user, const spotify::AuthentificationToken &token) {
    return get_users_playlists(user._id, token);
}

spotify::Page<spotify::Playlist> spotify::Playlist::get_playlist(std::string_view user_id,
                                                                 std::string_view playlist_id,
                                                                 const spotify::AuthentificationToken &token) {
    bool include_bearer{true};
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get2,
                                     "https://api.spotify.com/v1/users/" + std::string(user_id) + "/playlists/" + std::string(playlist_id),
                                     token, include_bearer)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::page<spotify::model::playlist>>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Page<spotify::Playlist> play_list(local_obj);
    return play_list;
}

spotify::Page<spotify::Playlist> spotify::Playlist::get_playlist(const spotify::User &user,
                                                                 std::string_view playlist_id,
                                                                 const spotify::AuthentificationToken &token) {
    return get_playlist(user._id, playlist_id, token);
}

spotify::Page<spotify::PlaylistTrack> spotify::Playlist::get_playlist_tracks(std::string_view user_id,
                                                                             std::string_view playlist_id,
                                                                             const spotify::AuthentificationToken &token) {
    bool include_bearer{true};
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get2,
                                     "https://api.spotify.com/v1/users/" + std::string(user_id) + "/playlists/" + std::string(playlist_id) + "/tracks",
                                     token, include_bearer)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::page<spotify::model::playlisttrack>>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Page<spotify::PlaylistTrack> play_list(local_obj);
    return play_list;
}

spotify::Page<spotify::PlaylistTrack> spotify::Playlist::get_playlist_tracks(const spotify::AuthentificationToken &token) const {
    return get_playlist_tracks(_owner->_id, _id, token);
}

void spotify::Playlist::add_track(const spotify::Track &track, spotify::AuthentificationToken &token) const {
    bool include_bearer{true};
    std::map<std::string, std::string> d;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::post2,
                                     "https://api.spotify.com/v1/users/" + std::string(_owner->_id)
                                             + "/playlists/" + std::string(_id) + "/tracks?uris=" + track.uri,
                                     token, d, include_bearer);
    auto local_obj = stlab::blocking_get(local_future);
}

void spotify::Playlist::add_tracks(const std::vector<spotify::Track> &track_uris, spotify::AuthentificationToken &token) const {
    std::vector<std::string> uris;
    std::transform(track_uris.begin(), track_uris.end(), uris.begin(),
                   [](const spotify::Track &track) -> std::string { return track.uri; });

    bool include_bearer{true};
    std::map<std::string, std::string> d;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::post2,
                                     "https://api.spotify.com/v1/users/" + std::string(_owner->_id)
                                             + "/playlists/" + std::string(_id) + "/tracks?uris=" + create_comma_separated_List(uris),
                                     token, d, include_bearer);
    auto local_obj = stlab::blocking_get(local_future);
}

spotify::Playlist spotify::Playlist::create_playlist(std::string_view user_id,
                                                     std::string_view name,
                                                     bool is_public,
                                                     const spotify::AuthentificationToken &token) {
    bool include_bearer{true};
    spotify::model::playlistdata pd;
    pd.name = name;
    pd.is_public = is_public;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::post3,
                                     "https://api.spotify.com/v1/users/" + std::string(user_id) + "/playlists",
                                     token, pd, include_bearer)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::playlist>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Playlist playlist(local_obj);
    return playlist;
}

void spotify::Playlist::update_users_playlist(std::string_view user_id, std::string_view playlist_id,
                                              std::string_view name,
                                              bool is_public,
                                              const spotify::AuthentificationToken &token) {
    bool include_bearer{true};
    spotify::model::playlistdata pd;
    pd.name = name;
    pd.is_public = is_public;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::put2,
                                     "https://api.spotify.com/v1/users/" + std::string(user_id) + "/playlists/" + std::string(playlist_id),
                                     token, pd, include_bearer);
    auto local_obj = stlab::blocking_get(local_future);
}

void spotify::Playlist::update_users_playlist(std::string_view name,
                                              bool is_public,
                                              const spotify::AuthentificationToken &token) const {
    update_users_playlist(_owner->_id, _id, name, is_public, token);
}

spotify::Page<spotify::Playlist> spotify::Playlist::get_featured_playlists(const spotify::AuthentificationToken &token,
                                                                           std::string_view locale,
                                                                           std::string_view country,
                                                                           std::string_view timestamp,
                                                                           int limit,
                                                                           int offset) {
    return spotify::Browse::get_featured_playlists(token, locale, country, timestamp, limit, offset);
}

}// namespace v1
}// namespace spotify

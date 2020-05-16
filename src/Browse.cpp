//
// Created by Michael Wittmann on 12/05/2020.
//

#include "Browse.hpp"

namespace spotify::inline v1 {

Page<Playlist> Browse::get_featured_playlists(const AuthenticationToken &token,
                                              std::string_view locale,
                                              std::string_view country,
                                              std::string_view timestamp,
                                              int limit, int offset) {
  std::string queryString =
      "https://api.spotify.com/v1/browse/featured-playlists?";
  queryString += "limit=" + std::to_string(limit);
  queryString += "&offset=" + std::to_string(offset);
  if (!timestamp.empty()) {
    queryString += "&timestamp=" + std::string(timestamp);
  }
  if (!locale.empty()) {
    queryString += "&locale=" + std::string(locale);
  }
  if (!country.empty()) {
    queryString += "&country=" + std::string(country);
  }
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get2,
                   queryString, token, include_bearer)
      | ([](std::string_view s) { return json_t::parse(s); })
      | ([](const json_t &j) {
          return j.get<model::featured_playlist_search_result>();
        });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Playlist> play_list;
  play_list._href = local_obj.playlists.href;
  play_list._next = local_obj.playlists.next;
  play_list._previous = local_obj.playlists.previous;
  play_list._total = local_obj.playlists.total;
  play_list._offset = local_obj.playlists.offset;
  play_list._limit = local_obj.playlists.limit;
  for (const auto &item : local_obj.playlists.items) {
    Playlist pl(item);
    play_list._items.push_back(pl);
  }
  return play_list;
}

Page<Album> Browse::get_new_releases(const AuthenticationToken &token,
                                     std::string_view country, int limit,
                                     int offset) {
  std::string queryString = "https://api.spotify.com/v1/browse/new-releases?";
  queryString += "limit=" + std::to_string(limit);
  queryString += "&offset=" + std::to_string(offset);
  if (!country.empty()) {
    queryString += "&country=" + std::string(country);
  }
  bool include_bearer{true};
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get2,
                   queryString, token, include_bearer)
      | ([](std::string_view s) { return json_t::parse(s); })
      | ([](const json_t &j) { return j.get<model::album_search_result>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Album> page;
  page._href = local_obj.albums.href;
  page._next = local_obj.albums.next;
  page._previous = local_obj.albums.previous;
  page._total = local_obj.albums.total;
  page._offset = local_obj.albums.offset;
  page._limit = local_obj.albums.limit;
  for (const auto &item : local_obj.albums.items) {
    Album album(item);
    page._items.push_back(album);
  }
  return page;
}

}  // namespace spotify::inline v1

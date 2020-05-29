//
// Created by Michael Wittmann on 12/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 17
#endif

#include "Browse.hpp"

#include <functional>                              // for __base
#include <stlab/concurrency/default_executor.hpp>  // for executor_type, def...
#include <stlab/concurrency/future.hpp>            // for async, future
#include <stlab/concurrency/utility.hpp>           // for blocking_get
#include <string>                                  // for basic_string, oper...
#include <type_traits>
#include <vector>

#include "Album.hpp"              // for Album
#include "Playlist.hpp"           // for Playlist
#include "detail/HttpHelper.hpp"  // for HttpHelper
namespace spotify {
inline namespace v1 {
class AuthenticationToken;
}
}  // namespace spotify

namespace spotify {
inline namespace v1 {

Page<Playlist> Browse::GetFeaturedPlaylists(const AuthenticationToken &token,
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
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   queryString, token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) {
        return j.get<model::featured_playlist_search_result>();
      });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Playlist> play_list;
  play_list.setHref(local_obj.playlists.href);
  play_list.setNext(local_obj.playlists.next);
  play_list.setPrevious(local_obj.playlists.previous);
  play_list.setTotal(local_obj.playlists.total);
  play_list.setOffset(local_obj.playlists.offset);
  play_list.setLimit(local_obj.playlists.limit);
  std::vector<Playlist> vec;
  for (const auto &item : local_obj.playlists.items) {
    Playlist pl(item);
    vec.push_back(std::move(pl));
  }
  play_list.setItems(vec);
  return play_list;
}

Page<Album> Browse::GetNewReleases(const AuthenticationToken &token,
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
      stlab::async(stlab::default_executor, detail::HttpHelper::Get2,
                   queryString, token, include_bearer) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::album_search_result>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Album> page;
  page.setHref(local_obj.albums.href);
  page.setNext(local_obj.albums.next);
  page.setPrevious(local_obj.albums.previous);
  page.setTotal(local_obj.albums.total);
  page.setOffset(local_obj.albums.offset);
  page.setLimit(local_obj.albums.limit);
  std::vector<Album> vec;
  for (const auto &item : local_obj.albums.items) {
    Album album(item);
    vec.push_back(std::move(album));
  }
  page.setItems(vec);
  return page;
}

}  // namespace spotify::inline v1
}  // namespace spotify
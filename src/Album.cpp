//
// Created by Michael Wittmann on 08/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 20
#endif

#include "Album.hpp"

#include <boost/date_time/posix_time/time_parsers.hpp>  // for time_from_string
#include <functional>                                   // for __base
#include <stlab/concurrency/default_executor.hpp>       // for executor_type
#include <stlab/concurrency/future.hpp>                 // for async, future
#include <stlab/concurrency/utility.hpp>                // for blocking_get
#include <string>                                       // for basic_string
#include <type_traits>                                  // for move

#include "Artist.hpp"             // for Artist
#include "Browse.hpp"             // for Browse
#include "Page.hpp"               // for Page
#include "Track.hpp"              // for Track
#include "detail/HttpHelper.hpp"  // for HttpHelper
namespace spotify::inline v1 {
class AuthenticationToken;
}

namespace spotify::inline v1 {

Page<Album> Album::get_artist_albums(std::string_view artist_id) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   "https://api.spotify.com/v1/artists/" +
                       std::string(artist_id) + "/albums") |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::album>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Album> album_page(local_obj);
  return album_page;
}

Page<Album> Album::search(std::string &albumName, std::string &artistName,
                          std::string &year, std::string &genre,
                          std::string &upc, std::string &isrc, int limit,
                          int offset) {
  albumName = replace_all(albumName, " ", "%20");
  std::string queryString =
      "https://api.spotify.com/v1/search?q=album:" + albumName;
  if (!artistName.empty()) {
    artistName = replace_all(artistName, " ", "%20");
    queryString += "%20:artist:" + artistName;
  }
  if (!year.empty()) {
    year = replace_all(year, " ", "%20");
    queryString += "%20:year:" + year;
  }
  if (!genre.empty()) {
    genre = replace_all(genre, " ", "%20");
    queryString += "%20:genre:" + genre;
  }
  if (!upc.empty()) {
    upc = replace_all(upc, " ", "%20");
    queryString += "%20:upc:" + upc;
  }
  if (!isrc.empty()) {
    isrc = replace_all(isrc, " ", "%20");
    queryString += "%20:isrc:" + isrc;
  }
  queryString += "&limit=" + std::to_string(limit);
  queryString += "&offset=" + std::to_string(offset);
  queryString += "&type=album";
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   queryString) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::album_search_result>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Album> page;
  page._next = local_obj.albums.next;
  page._previous = local_obj.albums.previous;
  page._href = local_obj.albums.href;
  page._total = local_obj.albums.total;
  page._offset = local_obj.albums.offset;
  page._limit = local_obj.albums.limit;
  for (const model::album &item : local_obj.albums.items) {
    Album album_(item);
    page._items.push_back(album_);
  }
  return page;
}

Album::Album(const model::album &t_album)
    : _availableMarkets(t_album.available_markets),
      _external_id(t_album.external_ids.at(0)),
      _external_url(t_album.external_urls.at(0)),
      _genres(t_album.genres),
      _href(t_album.href),
      _id(t_album.id),
      _name(t_album.name),
      _release_date_precision(t_album.release_date_precision),
      _type(t_album.type),
      _uri(t_album.uri),
      _ptracks(create_ref<Page<Track>>(t_album.tracks)) {
  if (str_toupper(t_album.album_type) == "ALBUM") {
    this->_album_type = Album::AlbumType::Album;
  } else if (str_toupper(t_album.album_type) == "SINGLE") {
    this->_album_type = Album::AlbumType::Single;
  } else if (str_toupper(t_album.album_type) == "COMPILATION") {
    this->_album_type = Album::AlbumType::Compilation;
  }
  this->_images.reserve(t_album.images.capacity());
  for (const model::image &image : t_album.images) {
    Image elem(image);
    this->_images.push_back(std::move(elem));
  }
  this->_artists.reserve(t_album.artists.capacity());
  for (const model::artist &artist : t_album.artists) {
    Artist elem(artist);
    this->_artists.push_back(std::move(elem));
  }
  const int base{10};
  _popularity = std::stoi(t_album.popularity, nullptr, base);
  _release_date = boost::posix_time::time_from_string(t_album.release_date);
}

Album::Album(model::album &&t_album) noexcept
    : _availableMarkets(std::move(t_album.available_markets)),
      _external_id(std::move(t_album.external_ids.at(0))),
      _external_url(std::move(t_album.external_urls.at(0))),
      _genres(std::move(t_album.genres)),
      _href(std::move(t_album.href)),
      _id(std::move(t_album.id)),
      _name(std::move(t_album.name)),
      _release_date_precision(std::move(t_album.release_date_precision)),
      _type(std::move(t_album.type)),
      _uri(std::move(t_album.uri)),
      _ptracks(create_ref<Page<Track>>(t_album.tracks)) {
  if (str_toupper(std::move(t_album.album_type)) == "ALBUM") {
    this->_album_type = Album::AlbumType::Album;
  } else if (str_toupper(std::move(t_album.album_type)) == "SINGLE") {
    this->_album_type = Album::AlbumType::Single;
  } else if (str_toupper(std::move(t_album.album_type)) == "COMPILATION") {
    this->_album_type = Album::AlbumType::Compilation;
  }
  this->_images.reserve(t_album.images.capacity());
  for (auto &image : t_album.images) {
    Image elem(std::move(image));
    this->_images.push_back(std::move(elem));
  }
  this->_artists.reserve(t_album.artists.capacity());
  for (auto &artist : t_album.artists) {
    Artist elem(std::move(artist));
    this->_artists.push_back(std::move(elem));
  }
  const int base{10};
  _popularity = std::stoi(std::move(t_album.popularity), nullptr, base);
  _release_date = boost::posix_time::time_from_string(t_album.release_date);
}

Album Album::get_album(std::string_view album_id) {
  auto local_future =
      stlab::async(
          stlab::default_executor, detail::HttpHelper::get1,
          "https://api.spotify.com/v1/albums/" + std::string(album_id)) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::album>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Album album_(local_obj);
  return album_;
}

Page<Track> v1::Album::get_album_tracks(std::string_view album_id, int limit,
                                        int offset) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   "https://api.spotify.com/v1/albums/" +
                       std::string(album_id) +
                       "/tracks?limit=" + std::to_string(limit) +
                       "&offset=" + std::to_string(offset)) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::track>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Track> album_page(local_obj);
  return album_page;
}

std::vector<Album> Album::get_albums(
    const std::vector<std::string> &album_ids) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   "https://api.spotify.com/v1/albums/?ids=" +
                       create_comma_separated_List(album_ids)) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::album_array>(); });
  auto local_obj = stlab::blocking_get(local_future);
  std::vector<Album> album_array;
  for (const auto &item : local_obj.albums) {
    Album a(item);
    album_array.push_back(a);
  }
  return album_array;
}

Page<Track> v1::Album::get_album_tracks(int limit, int offset) const {
  return get_album_tracks(this->_id, limit, offset);
}

Page<Album> v1::Album::get_new_releases(const AuthenticationToken &token,
                                        std::string_view country, int limit,
                                        int offset) {
  return Browse::get_new_releases(token, country, limit, offset);
}

}  // namespace spotify::inline v1

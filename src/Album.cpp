//
// Created by Michael Wittmann on 08/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 17
#endif

#include "Album.hpp"

#include <boost/date_time/posix_time/time_parsers.hpp>  // for time_from_string
#include <functional>                                   // for __base
#include <stlab/concurrency/default_executor.hpp>       // for executor_type
#include <stlab/concurrency/future.hpp>                 // for async, future
#include <stlab/concurrency/utility.hpp>                // for blocking_get
#include <string>                                       // for basic_string
#include <type_traits>                                  // for move
#include <vector>

#include "Artist.hpp"             // for Artist
#include "Browse.hpp"             // for Browse
#include "Page.hpp"               // for Page
#include "Track.hpp"              // for Track
#include "detail/HttpHelper.hpp"  // for HttpHelper
namespace spotify {
inline namespace v1 {
class AuthenticationToken;
}
}  // namespace spotify

namespace spotify {
inline namespace v1 {

Page<Album> Album::GetArtistAlbums(std::string_view artist_id) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   "https://api.spotify.com/v1/artists/" +
                       std::string(artist_id) + "/albums") |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::page<model::album>>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Album> album_page(local_obj);
  return album_page;
}

Page<Album> Album::Search(std::string &albumName, std::string &artistName,
                          std::string &year, std::string &genre,
                          std::string &upc, std::string &isrc, int limit,
                          int offset) {
  albumName = ReplaceAll(albumName, " ", "%20");
  std::string queryString =
      "https://api.spotify.com/v1/search?q=album:" + albumName;
  if (!artistName.empty()) {
    artistName = ReplaceAll(artistName, " ", "%20");
    queryString += "%20:artist:" + artistName;
  }
  if (!year.empty()) {
    year = ReplaceAll(year, " ", "%20");
    queryString += "%20:year:" + year;
  }
  if (!genre.empty()) {
    genre = ReplaceAll(genre, " ", "%20");
    queryString += "%20:genre:" + genre;
  }
  if (!upc.empty()) {
    upc = ReplaceAll(upc, " ", "%20");
    queryString += "%20:upc:" + upc;
  }
  if (!isrc.empty()) {
    isrc = ReplaceAll(isrc, " ", "%20");
    queryString += "%20:isrc:" + isrc;
  }
  queryString += "&limit=" + std::to_string(limit);
  queryString += "&offset=" + std::to_string(offset);
  queryString += "&type=album";
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   queryString) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::album_search_result>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Album> page;
  page.setNext(local_obj.albums.next);
  page.setPrevious(local_obj.albums.previous);
  page.setHref(local_obj.albums.href);
  page.setTotal(local_obj.albums.total);
  page.setOffset(local_obj.albums.offset);
  page.setLimit(local_obj.albums.limit);
  std::vector<Album> vec;
  for (const model::album &item : local_obj.albums.items) {
    Album album_(item);
    vec.push_back(std::move(album_));
  }
  page.setItems(vec);
  return page;
}

Album::Album(const model::album &t_album)
    : availableMarkets_(t_album.available_markets),
      external_id_(t_album.external_ids.at(0)),
      external_url_(t_album.external_urls.at(0)),
      genres_(t_album.genres),
      href_(t_album.href),
      id_(t_album.id),
      name_(t_album.name),
      release_date_precision_(t_album.release_date_precision),
      type_(t_album.type),
      uri_(t_album.uri),
      tracks_(t_album.tracks) {
  if (StrToUpper(t_album.album_type) == "ALBUM") {
    this->album_type_ = Album::AlbumType::Album;
  } else if (StrToUpper(t_album.album_type) == "SINGLE") {
    this->album_type_ = Album::AlbumType::Single;
  } else if (StrToUpper(t_album.album_type) == "COMPILATION") {
    this->album_type_ = Album::AlbumType::Compilation;
  }
  this->images_.reserve(t_album.images.size());
  for (const model::image &image : t_album.images) {
    Image elem(image);
    this->images_.push_back(std::move(elem));
  }
  this->artists_.reserve(t_album.artists.size());
  for (const model::artist &artist : t_album.artists) {
    Artist elem(artist);
    this->artists_.push_back(std::move(elem));
  }
  const int base{10};
  popularity_ = std::stoi(t_album.popularity, nullptr, base);
  release_date_ = boost::posix_time::time_from_string(t_album.release_date);
}

Album::Album(model::album &&t_album) noexcept
    : availableMarkets_(std::move(t_album.available_markets)),
      external_id_(std::move(t_album.external_ids.at(0))),
      external_url_(std::move(t_album.external_urls.at(0))),
      genres_(std::move(t_album.genres)),
      href_(std::move(t_album.href)),
      id_(std::move(t_album.id)),
      name_(std::move(t_album.name)),
      release_date_precision_(std::move(t_album.release_date_precision)),
      type_(std::move(t_album.type)),
      uri_(std::move(t_album.uri)),
      tracks_(t_album.tracks) {
  if (StrToUpper(std::move(t_album.album_type)) == "ALBUM") {
    this->album_type_ = Album::AlbumType::Album;
  } else if (StrToUpper(std::move(t_album.album_type)) == "SINGLE") {
    this->album_type_ = Album::AlbumType::Single;
  } else if (StrToUpper(std::move(t_album.album_type)) == "COMPILATION") {
    this->album_type_ = Album::AlbumType::Compilation;
  }
  this->images_.reserve(t_album.images.size());
  for (auto &image : t_album.images) {
    Image elem(std::move(image));
    this->images_.push_back(std::move(elem));
  }
  this->artists_.reserve(t_album.artists.size());
  for (auto &artist : t_album.artists) {
    Artist elem(std::move(artist));
    this->artists_.push_back(std::move(elem));
  }
  const int base{10};
  popularity_ = std::stoi(t_album.popularity, nullptr, base);
  release_date_ = boost::posix_time::time_from_string(t_album.release_date);
}

Album Album::GetAlbum(std::string_view album_id) {
  auto local_future =
      stlab::async(
          stlab::default_executor, detail::HttpHelper::Get1,
          "https://api.spotify.com/v1/albums/" + std::string(album_id)) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::album>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Album album_(local_obj);
  return album_;
}

Page<Track> Album::GetAlbumTracks(std::string_view album_id, int limit,
                                  int offset) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
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

std::vector<Album> Album::GetAlbums(const std::vector<std::string> &album_ids) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   "https://api.spotify.com/v1/albums/?ids=" +
                       CreateCommaSeparatedList(album_ids)) |
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

Page<Track> Album::GetAlbumTracks(int limit, int offset) const {
  return GetAlbumTracks(this->id_, limit, offset);
}

Page<Album> Album::GetNewReleases(const AuthenticationToken &token,
                                  std::string_view country, int limit,
                                  int offset) {
  return Browse::GetNewReleases(token, country, limit, offset);
}

}  // namespace spotify::inline v1
}  // namespace spotify
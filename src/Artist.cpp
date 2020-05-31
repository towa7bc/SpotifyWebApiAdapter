//
// Created by Michael Wittmann on 07/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 17
#endif

#include "Artist.hpp"

#include <functional>                              // for __base
#include <stlab/concurrency/default_executor.hpp>  // for executor_type, def...
#include <stlab/concurrency/future.hpp>            // for async, future
#include <stlab/concurrency/utility.hpp>           // for blocking_get
#include <string>                                  // for basic_string, oper...
#include <string_view>                             // for string_view
#include <type_traits>                             // for move
#include <vector>

#include "Album.hpp"              // for Album
#include "Page.hpp"               // for Page
#include "Track.hpp"              // for Track
#include "detail/HttpHelper.hpp"  // for HttpHelper

namespace spotify {
inline namespace v1 {

Artist Artist::GetArtist(const std::string &artist_id) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   "https://api.spotify.com/v1/artists/" + artist_id) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::artist>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Artist artist_(local_obj);
  return artist_;
}

std::vector<Artist> Artist::GetArtists(
    const std::vector<std::string> &artist_ids) {
  std::vector<Artist> artists_list;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   "https://api.spotify.com/v1/artists/?ids=" +
                       CreateCommaSeparatedList(artist_ids)) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::artist_array>(); });
  auto local_obj = stlab::blocking_get(local_future);
  for (const auto &item : local_obj.artists) {
    Artist artist_(item);
    artists_list.push_back(artist_);
  }
  return artists_list;
}

Page<Artist> Artist::Search(std::string &artistName, std::string &year,
                            std::string &genre, std::string &upc,
                            std::string &isrc, int limit, int offset) {
  artistName = ReplaceAll(artistName, " ", "%20");
  std::string queryString =
      "https://api.spotify.com/v1/search?q=artist:" + artistName;
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
  queryString += "&type=artist";
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   queryString) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::artist_search_result>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Artist> page;
  page.setNext(local_obj.artists.next);
  page.setPrevious(local_obj.artists.previous);
  page.setHref(local_obj.artists.href);
  page.setTotal(local_obj.artists.total);
  page.setOffset(local_obj.artists.offset);
  page.setLimit(local_obj.artists.limit);
  std::vector<Artist> vec;
  for (const model::artist &item : local_obj.artists.items) {
    Artist artist_(item);
    vec.push_back(std::move(artist_));
  }
  page.setItems(vec);
  return page;
}

Page<Album> Artist::GetAlbums() {
  auto local_future =
      stlab::async(stlab::default_executor, Album::GetArtistAlbums, this->id_);
  return stlab::blocking_get(local_future);
}

std::vector<Track> Artist::GetTopTracks(const std::string &artist_id,
                                        const std::string &country_code) {
  std::vector<Track> tracks_list;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   "https://api.spotify.com/v1/artists/" + artist_id +
                       "/top-tracks?country=" + country_code) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::track_array>(); });
  auto local_obj = stlab::blocking_get(local_future);
  for (const auto &item : local_obj.tracks) {
    Track track_;
    track_.setTrackNumber(item.track_number);

    tracks_list.push_back(track_);
  }
  return tracks_list;
}

std::vector<Track> Artist::GetTopTracks(const std::string &country_code) const {
  return GetTopTracks(this->id_, country_code);
}

std::vector<Artist> Artist::GetRelatedArtists(const std::string &artist_id,
                                              const std::string &country_code) {
  std::vector<Artist> artists_list;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1,
                   "https://api.spotify.com/v1/artists/" + artist_id +
                       "/top-tracks?country=" + country_code) |
      ([](std::string_view s) { return json_t::parse(s); }) |
      ([](const json_t &j) { return j.get<model::artist_array>(); });
  auto local_obj = stlab::blocking_get(local_future);
  for (const auto &item : local_obj.artists) {
    Artist artist_(item);
    artists_list.push_back(artist_);
  }
  return artists_list;
}

std::vector<Artist> Artist::GetRelatedArtists(
    const std::string &country_code) const {
  return GetRelatedArtists(this->id_, country_code);
}

Artist::Artist(const model::artist &t_artist)
    : genres_(t_artist.genres),
      external_url_(t_artist.external_urls.at(0)),
      href_(t_artist.href),
      id_(t_artist.id),
      name_(t_artist.name),
      type_(t_artist.type),
      uri_(t_artist.uri) {
  this->images_.reserve(t_artist.images.size());
  for (const model::image &image : t_artist.images) {
    Image elem(image);
    this->images_.push_back(std::move(elem));
  }
  const int base{10};
  this->popularity_ = std::stoi(t_artist.popularity, nullptr, base);
}

Artist::Artist(model::artist &&t_artist) noexcept
    : genres_(std::move(t_artist.genres)),
      external_url_(std::move(t_artist.external_urls.at(0))),
      href_(std::move(t_artist.href)),
      id_(std::move(t_artist.id)),
      name_(std::move(t_artist.name)),
      type_(std::move(t_artist.type)),
      uri_(std::move(t_artist.uri)) {
  this->images_.reserve(t_artist.images.size());
  for (auto &image : t_artist.images) {
    Image elem(std::move(image));
    this->images_.push_back(std::move(elem));
  }
  const int base{10};
  this->popularity_ = std::stoi(t_artist.popularity, nullptr, base);
}

}  // namespace spotify::inline v1
}  // namespace spotify
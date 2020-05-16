//
// Created by Michael Wittmann on 07/05/2020.
//

#include "Artist.hpp"

namespace spotify::inline v1 {

Artist Artist::get_artist(const std::string &artist_id) {
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   "https://api.spotify.com/v1/artists/" + artist_id)
      | ([](std::string_view s) { return json_t::parse(s); })
      | ([](const json_t &j) { return j.get<model::artist>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Artist artist_(local_obj);
  return artist_;
}

std::vector<Artist> Artist::get_artists(
    const std::vector<std::string> &artist_ids) {
  std::vector<Artist> artists_list;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   "https://api.spotify.com/v1/artists/?ids="
                       + create_comma_separated_List(artist_ids))
      | ([](std::string_view s) { return json_t::parse(s); })
      | ([](const json_t &j) { return j.get<model::artist_array>(); });
  auto local_obj = stlab::blocking_get(local_future);
  for (const auto &item : local_obj.artists) {
    Artist artist_(item);
    artists_list.push_back(artist_);
  }
  return artists_list;
}

Page<Artist> Artist::search(std::string &artistName, std::string &year,
                            std::string &genre, std::string &upc,
                            std::string &isrc, int limit, int offset) {
  artistName = replace_all(artistName, " ", "%20");
  std::string queryString =
      "https://api.spotify.com/v1/search?q=artist:" + artistName;
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
  queryString += "&type=artist";
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   queryString)
      | ([](std::string_view s) { return json_t::parse(s); })
      | ([](const json_t &j) { return j.get<model::artist_search_result>(); });
  auto local_obj = stlab::blocking_get(local_future);
  Page<Artist> page;
  page._next = local_obj.artists.next;
  page._previous = local_obj.artists.previous;
  page._href = local_obj.artists.href;
  page._total = local_obj.artists.total;
  page._offset = local_obj.artists.offset;
  page._limit = local_obj.artists.limit;
  for (const model::artist &item : local_obj.artists.items) {
    Artist artist_(item);
    page._items.push_back(artist_);
  }
  return page;
}

Page<Album> Artist::get_albums() {
  auto local_future = stlab::async(stlab::default_executor,
                                   Album::get_artist_albums, this->_id);
  return stlab::blocking_get(local_future);
}

std::vector<Track> Artist::get_top_tracks(const std::string &artist_id,
                                          const std::string &country_code) {
  std::vector<Track> tracks_list;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   "https://api.spotify.com/v1/artists/" + artist_id
                       + "/top-tracks?country=" + country_code)
      | ([](std::string_view s) { return json_t::parse(s); })
      | ([](const json_t &j) { return j.get<model::track_array>(); });
  auto local_obj = stlab::blocking_get(local_future);
  for (const auto &item : local_obj.tracks) {
    Track track_;
    track_.track_number = item.track_number;

    tracks_list.push_back(track_);
  }
  return tracks_list;
}

std::vector<Track> Artist::get_top_tracks(
    const std::string &country_code) const {
  return get_top_tracks(this->_id, country_code);
}

std::vector<Artist> Artist::get_related_artists(
    const std::string &artist_id, const std::string &country_code) {
  std::vector<Artist> artists_list;
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                   "https://api.spotify.com/v1/artists/" + artist_id
                       + "/top-tracks?country=" + country_code)
      | ([](std::string_view s) { return json_t::parse(s); })
      | ([](const json_t &j) { return j.get<model::artist_array>(); });
  auto local_obj = stlab::blocking_get(local_future);
  for (const auto &item : local_obj.artists) {
    Artist artist_(item);
    artists_list.push_back(artist_);
  }
  return artists_list;
}

std::vector<Artist> Artist::get_related_artists(
    const std::string &country_code) const {
  return get_related_artists(this->_id, country_code);
}

Artist::Artist(const model::artist &t_artist)
    : _genres(t_artist.genres),
      _external_url(t_artist.external_urls.at(0)),
      _href(t_artist.href),
      _id(t_artist.id),
      _name(t_artist.name),
      _type(t_artist.type),
      _uri(t_artist.uri) {
  this->_images.reserve(t_artist.images.capacity());
  for (const model::image &image : t_artist.images) {
    Image elem(image);
    this->_images.push_back(std::move(elem));
  }
  const int base{10};
  this->_popularity = std::stoi(t_artist.popularity, nullptr, base);
}

Artist::Artist(model::artist &&t_artist) noexcept
    : _genres(std::move(t_artist.genres)),
      _external_url(std::move(t_artist.external_urls.at(0))),
      _href(std::move(t_artist.href)),
      _id(std::move(t_artist.id)),
      _name(std::move(t_artist.name)),
      _type(std::move(t_artist.type)),
      _uri(std::move(t_artist.uri)) {
  this->_images.reserve(t_artist.images.capacity());
  for (auto &image : t_artist.images) {
    Image elem(std::move(image));
    this->_images.push_back(std::move(elem));
  }
  const int base{10};
  this->_popularity = std::stoi(std::move(t_artist.popularity), nullptr, base);
}

}  // namespace spotify::inline v1
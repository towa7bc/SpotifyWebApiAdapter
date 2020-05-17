//
// Created by Michael Wittmann on 03/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_MODELDATA_HPP
#define SPOTIFYWEBAPIADAPTER_MODELDATA_HPP

#include <nlohmann/json.hpp>  // for json, basic_json, basic_json<>::object_t
#include <string>             // for basic_string
#include <vector>             // for vector
namespace spotify::inline v1 {
namespace model {
struct track;
}
}  // namespace spotify::inline v1

using nlohmann::json;

namespace spotify::inline v1 {
namespace model {

struct accesstoken {
  accesstoken() = default;
  accesstoken(const accesstoken &) = default;
  ~accesstoken() = default;
  accesstoken &operator=(const accesstoken &) = default;
  accesstoken &operator=(accesstoken &&) noexcept = default;
  accesstoken(accesstoken &&) noexcept = default;
  std::string access_token;
  std::string token_type;
  int expires_in{0};
  std::string refresh_token;
};

void to_json(json &j, const accesstoken &token) {
  j = json{{"access_token", token.access_token},
           {"token_type", token.token_type},
           {"expires_in", token.expires_in},
           {"refresh_token", token.refresh_token}};
}

void from_json(const json &j, accesstoken &token) {
  j.at("access_token").get_to(token.access_token);
  j.at("token_type").get_to(token.token_type);
  j.at("expires_in").get_to(token.expires_in);
  j.at("refresh_token").get_to(token.refresh_token);
}

struct image {
  image(const image &) = default;
  image() = default;
  ~image() = default;
  image &operator=(const image &) = default;
  image &operator=(image &&) noexcept = default;
  image(image &&) noexcept = default;
  int height{0};
  std::string url;
  int width{0};
};

void to_json(json &j, const image &data) {
  j = json{{"height", data.height}, {"url", data.url}, {"width", data.width}};
}

void from_json(const json &j, image &data) {
  j.at("height").get_to(data.height);
  j.at("url").get_to(data.url);
  j.at("width").get_to(data.width);
}

template <typename>
struct page;

template <typename T>
struct page {
  page() = default;
  ~page() = default;
  page &operator=(const page &) = default;
  page(const page &) = default;
  page &operator=(page &&) noexcept = default;
  page(page &&) noexcept = default;
  int limit{0};
  std::string href;
  std::string next;
  std::string previous;
  int offset{0};
  int total{0};
  std::vector<T> items;
};

template <typename T>
void to_json(json &j, const page<T> &data) {
  j = json{{"href", data.href},         {"next", data.next},
           {"previous", data.previous}, {"offset", data.offset},
           {"total", data.total},       {"items", data.items},
           {"limit", data.limit}};
}

template <typename T>
void from_json(const json &j, page<T> &data) {
  j.at("href").get_to(data.href);
  j.at("next").get_to(data.next);
  j.at("previous").get_to(data.previous);
  j.at("offset").get_to(data.offset);
  j.at("total").get_to(data.total);
  j.at("items").get_to(data.items);
  j.at("limit").get_to(data.limit);
}

struct artist {
  artist() = default;
  ~artist() = default;
  artist(const artist &) = default;
  artist &operator=(const artist &) = default;
  artist &operator=(artist &&) noexcept = default;
  artist(artist &&) noexcept = default;
  std::string name;
  std::string href;
  std::string id;
  std::string popularity;
  std::string type;
  std::string uri;
  std::vector<std::string> external_urls;
  std::vector<std::string> genres;
  std::vector<image> images;
};

struct artist_array {
  artist_array() = default;
  ~artist_array() = default;
  artist_array(const artist_array &) = default;
  artist_array &operator=(const artist_array &) = default;
  artist_array &operator=(artist_array &&) noexcept = default;
  artist_array(artist_array &&) noexcept = default;
  std::vector<artist> artists;
};

struct artist_search_result {
  artist_search_result() = default;
  ~artist_search_result() = default;
  artist_search_result(const artist_search_result &) = default;
  artist_search_result &operator=(const artist_search_result &) = default;
  artist_search_result &operator=(artist_search_result &&) noexcept = default;
  artist_search_result(artist_search_result &&) noexcept = default;
  page<artist> artists;
};

void to_json(json &j, const artist &data) {
  j = json{{"href", data.href},
           {"name", data.name},
           {"popularity", data.popularity},
           {"id", data.id},
           {"type", data.type},
           {"uri", data.uri},
           {"external_urls", data.external_urls},
           {"genres", data.genres},
           {"images", data.images}};
}

void from_json(const json &j, artist &data) {
  j.at("href").get_to(data.href);
  j.at("name").get_to(data.name);
  j.at("popularity").get_to(data.popularity);
  j.at("id").get_to(data.id);
  j.at("type").get_to(data.type);
  j.at("uri").get_to(data.uri);
  j.at("external_urls").get_to(data.external_urls);
  j.at("genres").get_to(data.genres);
  j.at("images").get_to(data.images);
}

void to_json(json &j, const artist_array &data) {
  j = json{{"artists", data.artists}};
}

void from_json(const json &j, artist_array &data) {
  j.at("artists").get_to(data.artists);
}

void to_json(json &j, const artist_search_result &data) {
  j = json{{"artists", data.artists}};
}

void from_json(const json &j, artist_search_result &data) {
  j.at("artists").get_to(data.artists);
}

struct followers {
  followers() = default;
  followers(const followers &) = default;
  ~followers() = default;
  followers &operator=(const followers &) = default;
  followers &operator=(followers &&) noexcept = default;
  followers(followers &&) noexcept = default;
  std::string href;
  int total{0};
};

void to_json(json &j, const followers &data) {
  j = json{{"href", data.href}, {"total", data.total}};
}

void from_json(const json &j, followers &data) {
  j.at("href").get_to(data.href);
  j.at("total").get_to(data.total);
}

struct user {
  user() = default;
  user(const user &) = default;
  ~user() = default;
  user &operator=(const user &) = default;
  user &operator=(user &&) noexcept = default;
  user(user &&) noexcept = default;
  std::string country;
  std::string display_name;
  std::string email;
  std::string href;
  std::string id;
  std::string product;
  std::string type;
  std::string uri;
  std::vector<std::string> external_urls;
  std::vector<image> images;
};

void to_json(json &j, const user &data) {
  j = json{{"href", data.href},
           {"display_name", data.display_name},
           {"email", data.email},
           {"country", data.country},
           {"id", data.id},
           {"product", data.product},
           {"type", data.type},
           {"uri", data.uri},
           {"external_urls", data.external_urls},
           {"images", data.images}};
}

void from_json(const json &j, user &data) {
  j.at("href").get_to(data.href);
  j.at("display_name").get_to(data.display_name);
  j.at("email").get_to(data.email);
  j.at("country").get_to(data.country);
  j.at("id").get_to(data.id);
  j.at("product").get_to(data.product);
  j.at("type").get_to(data.type);
  j.at("uri").get_to(data.uri);
  j.at("external_urls").get_to(data.external_urls);
  j.at("images").get_to(data.images);
}

struct track;

struct album {
  album() = default;
  album(const album &) = default;
  ~album() = default;
  album &operator=(const album &) = default;
  album &operator=(album &&) noexcept = default;
  album(album &&) noexcept = default;
  std::string album_type;
  std::vector<artist> artists;
  std::vector<std::string> available_markets;
  std::vector<std::string> external_ids;
  std::vector<std::string> external_urls;
  std::vector<std::string> genres;
  std::string href;
  std::string id;
  std::vector<image> images;
  std::string name;
  std::string popularity;
  std::string release_date;
  std::string release_date_precision;
  page<track> tracks;
  std::string type;
  std::string uri;
};

struct track {
  track() = default;
  track(const track &) = default;
  ~track() = default;
  track &operator=(const track &) = default;
  track &operator=(track &&) noexcept = default;
  track(track &&) noexcept = default;
  album album_;
  std::vector<artist> artists;
  std::vector<std::string> available_markets;
  int disc_number{0};
  int duration_ms{0};
  bool is_explicit{false};
  std::vector<std::string> external_ids;
  std::vector<std::string> external_urls;
  std::vector<std::string> genres;
  std::string href;
  std::string id;
  std::string name;
  std::string popularity;
  std::string type;
  std::string uri;
  std::string preview_url;
  int track_number{0};
};

struct album_array {
  album_array() = default;
  album_array(const album_array &) = default;
  ~album_array() = default;
  album_array &operator=(const album_array &) = default;
  album_array &operator=(album_array &&) noexcept = default;
  album_array(album_array &&) noexcept = default;
  std::vector<album> albums;
};

struct album_search_result {
  album_search_result() = default;
  album_search_result(const album_search_result &) = default;
  ~album_search_result() = default;
  album_search_result &operator=(const album_search_result &) = default;
  album_search_result &operator=(album_search_result &&) noexcept = default;
  album_search_result(album_search_result &&) noexcept = default;
  page<album> albums;
};

struct track_array {
  track_array() = default;
  track_array(const track_array &) = default;
  ~track_array() = default;
  track_array &operator=(const track_array &) = default;
  track_array &operator=(track_array &&) noexcept = default;
  track_array(track_array &&) noexcept = default;
  std::vector<track> tracks;
};

struct track_search_result {
  track_search_result() = default;
  track_search_result(const track_search_result &) = default;
  ~track_search_result() = default;
  track_search_result &operator=(const track_search_result &) = default;
  track_search_result &operator=(track_search_result &&) noexcept = default;
  track_search_result(track_search_result &&) noexcept = default;
  page<track> tracks;
};

void to_json(json &j, const album &data) {
  j = json{{"album_type", data.album_type},
           {"artists", data.artists},
           {"available_markets", data.available_markets},
           {"external_ids", data.external_ids},
           {"href", data.href},
           {"name", data.name},
           {"popularity", data.popularity},
           {"release_date", data.release_date},
           {"release_date_precision", data.release_date_precision},
           {"tracks", data.tracks},
           {"id", data.id},
           {"type", data.type},
           {"uri", data.uri},
           {"external_urls", data.external_urls},
           {"genres", data.genres},
           {"images", data.images}};
}

void from_json(const json &j, album &data) {
  j.at("album_type").get_to(data.album_type);
  j.at("artists").get_to(data.artists);
  j.at("available_markets").get_to(data.available_markets);
  j.at("external_ids").get_to(data.external_ids);
  j.at("href").get_to(data.href);
  j.at("name").get_to(data.name);
  j.at("popularity").get_to(data.popularity);
  j.at("release_date").get_to(data.release_date);
  j.at("release_date_precision").get_to(data.release_date_precision);
  j.at("tracks").get_to(data.tracks);
  j.at("id").get_to(data.id);
  j.at("type").get_to(data.type);
  j.at("uri").get_to(data.uri);
  j.at("external_urls").get_to(data.external_urls);
  j.at("genres").get_to(data.genres);
  j.at("images").get_to(data.images);
}

void to_json(json &j, const track &data) {
  j = json{{"album", data.album_},
           {"artists", data.artists},
           {"available_markets", data.available_markets},
           {"external_ids", data.external_ids},
           {"disc_number", data.disc_number},
           {"duration_ms", data.duration_ms},
           {"explicit", data.is_explicit},
           {"href", data.href},
           {"name", data.name},
           {"popularity", data.popularity},
           {"id", data.id},
           {"type", data.type},
           {"uri", data.uri},
           {"external_urls", data.external_urls},
           {"genres", data.genres},
           {"track_number", data.track_number},
           {"preview_url", data.preview_url}};
}

void from_json(const json &j, track &data) {
  j.at("album").get_to(data.album_);
  j.at("artists").get_to(data.artists);
  j.at("available_markets").get_to(data.available_markets);
  j.at("external_ids").get_to(data.external_ids);
  j.at("disc_number").get_to(data.disc_number);
  j.at("duration_ms").get_to(data.duration_ms);
  j.at("explicit").get_to(data.is_explicit);
  j.at("href").get_to(data.href);
  j.at("name").get_to(data.name);
  j.at("poularity").get_to(data.popularity);
  j.at("id").get_to(data.id);
  j.at("type").get_to(data.type);
  j.at("uri").get_to(data.uri);
  j.at("external_urls").get_to(data.external_urls);
  j.at("genres").get_to(data.genres);
  j.at("track_number").get_to(data.track_number);
  j.at("preview_url").get_to(data.preview_url);
}

void to_json(json &j, const album_array &data) {
  j = json{{"albums", data.albums}};
}

void from_json(const json &j, album_array &data) {
  j.at("albums").get_to(data.albums);
}

void to_json(json &j, const album_search_result &data) {
  j = json{{"albums", data.albums}};
}

void from_json(const json &j, album_search_result &data) {
  j.at("albums").get_to(data.albums);
}

void to_json(json &j, const track_array &data) {
  j = json{{"tracks", data.tracks}};
}

void from_json(const json &j, track_array &data) {
  j.at("tracks").get_to(data.tracks);
}

void to_json(json &j, const track_search_result &data) {
  j = json{{"tracks", data.tracks}};
}

void from_json(const json &j, track_search_result &data) {
  j.at("tracks").get_to(data.tracks);
}

struct playlisttrack {
  playlisttrack() = default;
  playlisttrack(const playlisttrack &) = default;
  ~playlisttrack() = default;
  playlisttrack &operator=(const playlisttrack &) = default;
  playlisttrack &operator=(playlisttrack &&) noexcept = default;
  playlisttrack(playlisttrack &&) noexcept = default;
  user added_by;
  std::string added_at;
  track track_;
};

void to_json(json &j, const playlisttrack &data) {
  j = json{{"added_by", data.added_by},
           {"added_at", data.added_at},
           {"track", data.track_}};
}

void from_json(const json &j, playlisttrack &data) {
  j.at("added_by").get_to(data.added_by);
  j.at("added_at").get_to(data.added_at);
  j.at("track").get_to(data.track_);
}

struct playlist {
  playlist() = default;
  playlist(const playlist &) = default;
  ~playlist() = default;
  playlist &operator=(const playlist &) = default;
  playlist &operator=(playlist &&) noexcept = default;
  playlist(playlist &&) noexcept = default;
  std::string description;
  std::vector<std::string> external_urls;
  followers followers_;
  std::string name;
  std::string href;
  std::string id;
  std::string type;
  std::string uri;
  std::vector<image> images;
  user owner;
  bool is_public{false};
  bool is_collaborative{false};
  page<playlisttrack> tracks;
};

struct playlist_search_result {
  playlist_search_result() = default;
  playlist_search_result(const playlist_search_result &) = default;
  ~playlist_search_result() = default;
  playlist_search_result &operator=(const playlist_search_result &) = default;
  playlist_search_result &operator=(playlist_search_result &&) noexcept =
      default;
  playlist_search_result(playlist_search_result &&) noexcept = default;
  page<playlist> playlists;
};

struct featured_playlist_search_result {
  featured_playlist_search_result() = default;
  featured_playlist_search_result(const featured_playlist_search_result &) =
      default;
  ~featured_playlist_search_result() = default;
  featured_playlist_search_result &operator=(
      const featured_playlist_search_result &) = default;
  featured_playlist_search_result &operator=(
      featured_playlist_search_result &&) noexcept = default;
  featured_playlist_search_result(featured_playlist_search_result &&) noexcept =
      default;
  std::string message;
  page<playlist> playlists;
};

void to_json(json &j, const playlist &data) {
  j = json{{"tracks", data.tracks},
           {"collaborative", data.is_collaborative},
           {"public", data.is_public},
           {"owner", data.owner},
           {"images", data.images},
           {"uri", data.uri},
           {"type", data.type},
           {"id", data.id},
           {"href", data.href},
           {"name", data.name},
           {"followers", data.followers_},
           {"external_urls", data.external_urls},
           {"description", data.description}};
}

void from_json(const json &j, playlist &data) {
  j.at("tracks").get_to(data.tracks);
  j.at("collaborative").get_to(data.is_collaborative);
  j.at("public").get_to(data.is_public);
  j.at("owner").get_to(data.owner);
  j.at("images").get_to(data.images);
  j.at("uri").get_to(data.uri);
  j.at("type").get_to(data.type);
  j.at("id").get_to(data.id);
  j.at("href").get_to(data.href);
  j.at("name").get_to(data.name);
  j.at("followers").get_to(data.followers_);
  j.at("external_urls").get_to(data.external_urls);
  j.at("description").get_to(data.description);
}

void to_json(json &j, const playlist_search_result &data) {
  j = json{{"playlists", data.playlists}};
}

void from_json(const json &j, playlist_search_result &data) {
  j.at("playlists").get_to(data.playlists);
}

void to_json(json &j, const featured_playlist_search_result &data) {
  j = json{{"message", data.message}, {"playlists", data.playlists}};
}

void from_json(const json &j, featured_playlist_search_result &data) {
  j.at("message").get_to(data.message);
  j.at("playlists").get_to(data.playlists);
}

struct playlistdata {
  playlistdata() = default;
  playlistdata(const playlistdata &) = default;
  ~playlistdata() = default;
  playlistdata &operator=(const playlistdata &) = default;
  playlistdata &operator=(playlistdata &&) noexcept = default;
  playlistdata(playlistdata &&) noexcept = default;
  std::string name;
  bool is_public{};
};

void to_json(json &j, const playlistdata &data) {
  j = json{{"name", data.name}, {"public", data.is_public}};
}

void from_json(const json &j, playlistdata &data) {
  j.at("name").get_to(data.name);
  j.at("public").get_to(data.is_public);
}

struct savedtrack {
  savedtrack() = default;
  savedtrack(const savedtrack &) = default;
  ~savedtrack() = default;
  savedtrack &operator=(const savedtrack &) = default;
  savedtrack &operator=(savedtrack &&) noexcept = default;
  savedtrack(savedtrack &&) noexcept = default;
  std::string added_at;
  track track_;
};

void to_json(json &j, const savedtrack &data) {
  j = json{{"added_at", data.added_at}, {"track", data.track_}};
}

void from_json(const json &j, savedtrack &data) {
  j.at("added_at").get_to(data.added_at);
  j.at("track").get_to(data.track_);
}

}  // namespace model
}  // namespace spotify::inline v1

#endif

//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_TRACK_ALBUM_HPP
#define SPOTIFYWEBAPIADAPTER_TRACK_ALBUM_HPP

#include "artist.hpp"
#include "image.hpp"
#include "page.hpp"
#include <nlohmann/json.hpp>
#include <vector>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct track;

struct album {
    std::string album_type;
    std::vector<artist> artists;
    std::vector<std::string> available_markets;
    std::vector<std::string> external_ids;
    std::vector<std::string> external_urls;
    std::vector<std::string> genres;
    std::string href;
    std::string id;
    std::vector<spotify::model::image> images;
    std::string name;
    std::string popularity;
    std::string release_date;
    std::string release_date_precision;
    spotify::model::page<spotify::model::track> tracks;
    std::string type;
    std::string uri;
};

struct track {
    spotify::model::album album_;
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
    std::vector<album> albums;
};

struct album_search_result {
    page<album> albums;
};

struct track_array {
    std::vector<track> tracks;
};

struct track_search_result {
    page<track> tracks;
};

void to_json(json &j, const album &data) {
    j = json{
            {"album_type", data.album_type},
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
    j = json{
            {"album", data.album_},
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
    j = json{
            {"albums", data.albums}};
}

void from_json(const json &j, album_array &data) {
    j.at("albums").get_to(data.albums);
}

void to_json(json &j, const album_search_result &data) {
    j = json{
            {"albums", data.albums}};
}

void from_json(const json &j, album_search_result &data) {
    j.at("albums").get_to(data.albums);
}

void to_json(json &j, const track_array &data) {
    j = json{
            {"tracks", data.tracks}};
}

void from_json(const json &j, track_array &data) {
    j.at("tracks").get_to(data.tracks);
}

void to_json(json &j, const track_search_result &data) {
    j = json{
            {"tracks", data.tracks}};
}

void from_json(const json &j, track_search_result &data) {
    j.at("tracks").get_to(data.tracks);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

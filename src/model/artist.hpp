//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_ARTIST_HPP
#define SPOTIFYWEBAPIADAPTER_ARTIST_HPP

#include "image.hpp"
#include "page.hpp"
#include <nlohmann/json.hpp>
#include <vector>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct artist {
    std::string name;
    std::string href;
    std::string id;
    std::string popularity;
    std::string type;
    std::string uri;
    std::vector<std::string> external_urls;
    std::vector<std::string> genres;
    std::vector<spotify::model::image> images;
};

struct artist_array {
    std::vector<artist> artists;
};

struct artist_search_result {
    spotify::model::page<artist> artists;
};

void to_json(json &j, const artist &data) {
    j = json{
            {"href", data.href},
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
    j = json{
            {"artists", data.artists}};
}

void from_json(const json &j, artist_array &data) {
    j.at("artists").get_to(data.artists);
}

void to_json(json &j, const artist_search_result &data) {
    j = json{
            {"artists", data.artists}};
}

void from_json(const json &j, artist_search_result &data) {
    j.at("artists").get_to(data.artists);
}

}// namespace model
}// namespace v1
}// namespace spotify


#endif

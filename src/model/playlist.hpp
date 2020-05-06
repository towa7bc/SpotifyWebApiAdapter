//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP

#include "followers.hpp"
#include "image.hpp"
#include "playlisttrack.hpp"
#include "user.hpp"
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct playlist {
    std::string description;
    std::vector<std::string> external_urls;
    followers followers_;
    std::string name;
    std::string href;
    std::string id;
    std::string type;
    std::string uri;
    std::vector<spotify::model::image> images;
    user owner;
    bool is_public{false};
    bool is_collaborative{false};
    page<playlisttrack> tracks;
};

struct playlist_search_result {
    page<playlist> playlists;
};

struct featured_playlist_search_result {
    std::string message;
    page<playlist> playlists;
};

void to_json(json &j, const playlist &data) {
    j = json{
            {"tracks", data.tracks},
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
    j = json{
            {"playlists", data.playlists}};
}

void from_json(const json &j, playlist_search_result &data) {
    j.at("playlists").get_to(data.playlists);
}

void to_json(json &j, const featured_playlist_search_result &data) {
    j = json{
            {"message", data.message},
            {"playlists", data.playlists}};
}

void from_json(const json &j, featured_playlist_search_result &data) {
    j.at("message").get_to(data.message);
    j.at("playlists").get_to(data.playlists);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

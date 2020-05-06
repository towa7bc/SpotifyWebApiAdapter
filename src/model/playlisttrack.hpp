//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP

#include "track_album.hpp"
#include "user.hpp"
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {
struct playlisttrack {
    spotify::model::user added_by;
    std::string added_at;
    spotify::model::track track_;
};

void to_json(json &j, const playlisttrack &data) {
    j = json{
            {"added_by", data.added_by},
            {"added_at", data.added_at},
            {"track", data.track_}};
}

void from_json(const json &j, playlisttrack &data) {
    j.at("added_by").get_to(data.added_by);
    j.at("added_at").get_to(data.added_at);
    j.at("track").get_to(data.track_);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

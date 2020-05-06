//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_SAVEDTRACK_HPP
#define SPOTIFYWEBAPIADAPTER_SAVEDTRACK_HPP

#include "track_album.hpp"
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct savedtrack {
    std::string added_at;
    track track_;
};

void to_json(json &j, const savedtrack &data) {
    j = json{
            {"added_at", data.added_at},
            {"track", data.track_}};
}

void from_json(const json &j, savedtrack &data) {
    j.at("added_at").get_to(data.added_at);
    j.at("track").get_to(data.track_);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

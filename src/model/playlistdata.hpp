//
// Created by Michael Wittmann on 05/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLISTDATA_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLISTDATA_HPP

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct playlistdata {
    std::string name;
    bool is_public;
};

void to_json(json &j, const playlistdata &data) {
    j = json{
            {"name", data.name},
            {"public", data.is_public}};
}

void from_json(const json &j, playlistdata &data) {
    j.at("name").get_to(data.name);
    j.at("public").get_to(data.is_public);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

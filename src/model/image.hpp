//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_IMAGE_HPP
#define SPOTIFYWEBAPIADAPTER_IMAGE_HPP

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct image {
    int height{0};
    std::string url;
    int width{0};
};

void to_json(json &j, const image &data) {
    j = json{
            {"height", data.height},
            {"url", data.url},
            {"width", data.width}};
}

void from_json(const json &j, image &data) {
    j.at("height").get_to(data.height);
    j.at("url").get_to(data.url);
    j.at("width").get_to(data.width);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

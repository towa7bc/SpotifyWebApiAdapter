//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP
#define SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP

#include <nlohmann/json.hpp>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct followers {
    std::string href;
    int total{0};
};

void to_json(json &j, const followers &data) {
    j = json{
            {"href", data.href},
            {"total", data.total}};
}

void from_json(const json &j, followers &data) {
    j.at("href").get_to(data.href);
    j.at("total").get_to(data.total);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

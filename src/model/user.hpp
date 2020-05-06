//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_USER_HPP
#define SPOTIFYWEBAPIADAPTER_USER_HPP

#include "image.hpp"
#include <nlohmann/json.hpp>
#include <vector>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

struct user {
    std::string country;
    std::string display_name;
    std::string email;
    std::string href;
    std::string id;
    std::string product;
    std::string type;
    std::string uri;
    std::vector<std::string> external_urls;
    std::vector<spotify::model::image> images;
};

void to_json(json &j, const user &data) {
    j = json{
            {"href", data.href},
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

}// namespace model
}// namespace v1
}// namespace spotify

#endif

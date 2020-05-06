//
// Created by Michael Wittmann on 06/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PAGE_HPP
#define SPOTIFYWEBAPIADAPTER_PAGE_HPP

#include <nlohmann/json.hpp>
#include <vector>

using nlohmann::json;

namespace spotify {

inline namespace v1 {

namespace model {

template<typename>
struct page;

template<typename T>
struct page {
    int limit{0};
    std::string href;
    std::string next;
    std::string previous;
    int offset{0};
    int total{0};
    std::vector<T> items;
};

template<typename T>
void to_json(json &j, const page<T> &data) {
    j = json{
            {"href", data.href},
            {"next", data.next},
            {"previous", data.previous},
            {"offset", data.offset},
            {"total", data.total},
            {"items", data.items},
            {"limit", data.limit}};
}

template<typename T>
void from_json(const json &j, page<T> &data) {
    j.at("href").get_to(data.href);
    j.at("next").get_to(data.next);
    j.at("previous").get_to(data.previous);
    j.at("offset").get_to(data.offset);
    j.at("total").get_to(data.total);
    j.at("items").get_to(data.items);
    j.at("limit").get_to(data.limit);
}

}// namespace model
}// namespace v1
}// namespace spotify

#endif

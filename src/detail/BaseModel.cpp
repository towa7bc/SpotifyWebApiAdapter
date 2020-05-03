//
// Created by Michael Wittmann on 03/05/2020.
//

#include "BaseModel.hpp"

/* static */ auto spotify::BaseModel::create_comma_separated_List(const std::vector<std::string> &v)
        -> std::string {
    if (v.empty()) {
        return "n/a";
    }
    return std::accumulate(std::next(v.begin()), v.end(), v[0], [](std::string a, std::string b) {
        return std::move(a) + ',' + std::move(b);
    });
}
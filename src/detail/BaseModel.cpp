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

std::string spotify::BaseModel::replace_all(std::string str, std::string_view from, std::string_view to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();// Handles case where 'to' is a substring of 'from'
    }
    return str;
}

std::string spotify::BaseModel::str_toupper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return s;
}
//
// Created by Michael Wittmann on 30/04/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_BASEMODEL_HPP
#define SPOTIFYWEBAPIADAPTER_BASEMODEL_HPP

#include <numeric>
#include <string>
#include <vector>

namespace spotify {

inline namespace v1 {

class BaseModel {
public:
    static auto create_comma_separated_List(const std::vector<std::string> &v) -> std::string;
    static std::string replace_all(std::string str, std::string_view from, std::string_view to);
    static std::string str_toupper(std::string s);
};


class PageNotFoundException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "Page not found.";
    }
};

}// namespace v1

}// namespace spotify

#endif

//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_USER_HPP
#define SPOTIFYWEBAPIADAPTER_USER_HPP

#include "detail/BaseModel.hpp"

namespace spotify {

inline namespace v1 {

struct User : public BaseModel {
    User() = default;
    User(const User &) = default;
    ~User() override = default;
    User &operator=(const User &) = default;
    User &operator=(User &&) noexcept = default;
    User(User &&) noexcept = default;
    int _height{0};
    std::string _url;
    int _width{0};
};

}// namespace v1
}// namespace spotify

#endif

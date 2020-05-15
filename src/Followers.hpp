//
// Created by Michael Wittmann on 12/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP
#define SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP

#include "model/modeldata.hpp"
#include <string>

namespace spotify {

inline namespace v1 {

struct Followers {
    explicit Followers(const model::followers &);
    explicit Followers(model::followers &&) noexcept;
    Followers() = default;
    Followers(const Followers &) = default;
    ~Followers() = default;
    Followers &operator=(const Followers &) = default;
    Followers &operator=(Followers &&) noexcept = default;
    Followers(Followers &&) noexcept = default;
    int _total{0};
    std::string _href;
};

}// namespace v1
}// namespace spotify

#endif

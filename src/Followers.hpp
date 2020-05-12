//
// Created by Michael Wittmann on 12/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP
#define SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP

#include <string>

namespace spotify {

inline namespace v1 {

struct Followers {
    int _total{0};
    std::string _href;
};

}// namespace v1
}// namespace spotify

#endif

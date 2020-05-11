//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_IMAGE_HPP
#define SPOTIFYWEBAPIADAPTER_IMAGE_HPP

#include <string>

namespace spotify {

inline namespace v1 {

struct Image {
    Image() = default;
    Image(const Image &) = default;
    ~Image() = default;
    Image &operator=(const Image &) = default;
    Image &operator=(Image &&) = default;
    Image(Image &&) noexcept = default;
    int _height{0};
    std::string _url;
    int width{0};
};

}// namespace v1
}// namespace spotify

#endif

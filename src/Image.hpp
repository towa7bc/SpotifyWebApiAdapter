//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_IMAGE_HPP
#define SPOTIFYWEBAPIADAPTER_IMAGE_HPP

#include "model/modeldata.hpp"
#include <string>

namespace spotify {

inline namespace v1 {

struct Image {
    explicit Image(const spotify::model::image &);
    Image() = default;
    Image(const Image &) = default;
    ~Image() = default;
    Image &operator=(const Image &) = default;
    Image &operator=(Image &&) noexcept = default;
    Image(Image &&) noexcept = default;
    int _height{0};
    std::string _url;
    int _width{0};
};

}// namespace v1
}// namespace spotify

#endif

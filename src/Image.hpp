//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_IMAGE_HPP
#define SPOTIFYWEBAPIADAPTER_IMAGE_HPP

#include <string>

#include "model/modeldata.hpp"

namespace spotify::inline v1 {

struct Image {
  explicit Image(const model::image &);
  explicit Image(model::image &&) noexcept;
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

}  // namespace spotify::inline v1

#endif

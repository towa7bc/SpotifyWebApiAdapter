//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_IMAGE_HPP
#define SPOTIFYWEBAPIADAPTER_IMAGE_HPP

#include <string>  // for string
namespace spotify::inline v1 {
namespace model {
struct image;
}
}  // namespace spotify::inline v1

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
  int height_{0};
  std::string url_;
  int width_{0};
};

}  // namespace spotify::inline v1

#endif

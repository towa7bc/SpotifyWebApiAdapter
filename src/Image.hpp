//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_IMAGE_HPP
#define SPOTIFYWEBAPIADAPTER_IMAGE_HPP

#include <string>  // for string
namespace spotify {
inline namespace v1 {
namespace model {
struct image;
}
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

struct Image {
  explicit Image(const model::image &);
  explicit Image(model::image &&) noexcept;
  Image() = default;
  Image(const Image &) = default;
  ~Image() = default;
  Image &operator=(const Image &) = default;
  Image &operator=(Image &&) noexcept = default;
  Image(Image &&) noexcept = default;

  [[nodiscard]] int getHeight() const { return height_; }
  void setHeight(int height) { height_ = height; }
  [[nodiscard]] const std::string &getUrl() const { return url_; }
  void setUrl(const std::string &url) { url_ = url; }
  [[nodiscard]] int getWidth() const { return width_; }
  void setWidth(int width) { width_ = width; }

 private:
  int height_{0};
  std::string url_;
  int width_{0};
};

}  // namespace v1
}  // namespace spotify

#endif

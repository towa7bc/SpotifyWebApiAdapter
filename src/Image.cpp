//
// Created by Michael Wittmann on 07/05/2020.
//

#include "Image.hpp"

#include <type_traits>  // for move

#include "model/modeldata.hpp"  // for image

namespace spotify {
inline namespace v1 {

Image::Image(const model::image &t_image)
    : height_(t_image.height), url_(t_image.url), width_(t_image.width) {}

Image::Image(model::image &&t_image) noexcept
    : height_(t_image.height),
      url_(std::move(t_image.url)),
      width_(t_image.width) {}

}  // namespace v1
}  // namespace spotify
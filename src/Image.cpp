//
// Created by Michael Wittmann on 07/05/2020.
//

#include "Image.hpp"

namespace spotify::inline v1 {

Image::Image(const model::image &t_image) : _height(t_image.height),
                                            _url(t_image.url),
                                            _width(t_image.width) {
}

Image::Image(model::image &&t_image) noexcept : _height(t_image.height),
                                                _url(std::move(t_image.url)),
                                                _width(t_image.width) {
}

}// namespace v1

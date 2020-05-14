//
// Created by Michael Wittmann on 07/05/2020.
//

#include "Image.hpp"

spotify::Image::Image(const spotify::model::image &t_image) : _height(t_image.height),
                                                              _url(t_image.url),
                                                              _width(t_image.width) {
}

spotify::Image::Image(spotify::model::image &&t_image) noexcept : _height(t_image.height),
                                                                  _url(std::move(t_image.url)),
                                                                  _width(t_image.width) {
}

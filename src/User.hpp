//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_USER_HPP
#define SPOTIFYWEBAPIADAPTER_USER_HPP

#include "Image.hpp"
#include "detail/BaseModel.hpp"
#include "model/modeldata.hpp"

namespace spotify {

inline namespace v1 {

struct User : public BaseModel {
    explicit User(const spotify::model::user &);
    explicit User(spotify::model::user &&) noexcept;
    User() = default;
    User(const User &) = default;
    ~User() override = default;
    User &operator=(const User &) = default;
    User &operator=(User &&) noexcept = default;
    User(User &&) noexcept = default;
    std::string _country;
    std::string _displayName;
    std::string _email_address;
    std::string _external_url;
    std::string _href;
    std::string _id;
    std::vector<spotify::Image> _images;
    std::string _product;
    std::string _type;
    std::string _uri;
};

}// namespace v1
}// namespace spotify

#endif

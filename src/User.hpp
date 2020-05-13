//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_USER_HPP
#define SPOTIFYWEBAPIADAPTER_USER_HPP

#include "AuthentificationToken.hpp"
#include "Image.hpp"
#include "Playlist.hpp"
#include "detail/BaseModel.hpp"
#include "model/modeldata.hpp"

namespace spotify {

inline namespace v1 {

template<typename>
class Page;

class Track;
class Playlist;

class User : public BaseModel {
    using json_t = nlohmann::json;

public:
    explicit User(const spotify::model::user &);
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
    static spotify::User get_user(std::string_view user_id);
    static spotify::User get_current_user_profile(const spotify::AuthentificationToken &token);
    [[nodiscard]] spotify::Page<spotify::Playlist> get_playlists(const spotify::AuthentificationToken &token) const;
    static spotify::Page<spotify::Track> get_user_saved_tracks(const spotify::AuthentificationToken &token, int limit = 20, int offset = 0);
    spotify::Page<spotify::Track> get_saved_tracks(const spotify::AuthentificationToken &token, int limit = 20, int offset = 0);
    void save_tracks(const std::vector<std::string> &ids, const spotify::AuthentificationToken &token);
    void delete_tracks(const std::vector<std::string> &ids, const spotify::AuthentificationToken &token);
    bool are_saved(const std::vector<std::string> &ids, const spotify::AuthentificationToken &token);
    bool is_saved(std::string_view id, const spotify::AuthentificationToken &token);
};

}// namespace v1
}// namespace spotify

#endif

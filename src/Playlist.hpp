//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP

#include "Followers.hpp"
#include "PlaylistTrack.hpp"
#include "User.hpp"
#include "detail/BaseModel.hpp"
#include "model/modeldata.hpp"

namespace spotify {

inline namespace v1 {

struct PlaylistTrack;

template<typename>
class Page;

struct Image;

class Playlist : public BaseModel {
public:
    explicit Playlist(const spotify::model::playlist &);
    Playlist() = default;
    Playlist(const Playlist &) = default;
    ~Playlist() override = default;
    Playlist &operator=(const Playlist &) = default;
    Playlist &operator=(Playlist &&) noexcept = default;
    Playlist(Playlist &&) noexcept = default;
    bool _collaborative{false};
    std::string _description;
    std::string _external_url;
    spotify::Followers _followers;
    std::string _href;
    std::string _id;
    std::vector<spotify::Image> _images;
    std::string _name;
    std::shared_ptr<const spotify::User> _owner;
    bool _public{false};
    std::shared_ptr<const spotify::Page<spotify::PlaylistTrack>> _tracks;
    std::string _type;
    std::string _uri;
};

}// namespace v1
}// namespace spotify

#endif

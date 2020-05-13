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

class AuthentificationToken;

class Track;

class Playlist : public BaseModel {
    using json_t = nlohmann::json;

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
    static spotify::Page<spotify::Playlist> get_users_playlists(std::string_view user_id, const spotify::AuthentificationToken &token);
    static spotify::Page<spotify::Playlist> get_users_playlists(const spotify::User &user, const spotify::AuthentificationToken &token);
    static spotify::Page<spotify::Playlist> get_playlist(std::string_view user_id,
                                                         std::string_view playlist_id,
                                                         const spotify::AuthentificationToken &token);
    static spotify::Page<spotify::Playlist> get_playlist(const spotify::User &user,
                                                         std::string_view playlist_id,
                                                         const spotify::AuthentificationToken &token);
    static spotify::Page<spotify::PlaylistTrack> get_playlist_tracks(std::string_view user_id,
                                                                     std::string_view playlist_id,
                                                                     const spotify::AuthentificationToken &token);
    [[nodiscard]] spotify::Page<spotify::PlaylistTrack> get_playlist_tracks(const spotify::AuthentificationToken &token) const;
    void add_track(const spotify::Track &track, spotify::AuthentificationToken &token) const;
    void add_tracks(const std::vector<spotify::Track> &track_uris, spotify::AuthentificationToken &token) const;
    static spotify::Playlist create_playlist(std::string_view user_id,
                                             std::string_view name,
                                             bool is_public,
                                             const spotify::AuthentificationToken &token);
    static void update_users_playlist(std::string_view user_id, std::string_view playlist_id,
                                      std::string_view name,
                                      bool is_public,
                                      const spotify::AuthentificationToken &token);
    void update_users_playlist(std::string_view name,
                               bool is_public,
                               const spotify::AuthentificationToken &token) const;
    static spotify::Page<spotify::Playlist> get_featured_playlists(const spotify::AuthentificationToken &token,
                                                                   std::string_view locale = "",
                                                                   std::string_view country = "",
                                                                   std::string_view timestamp = "",
                                                                   int limit = 20,
                                                                   int offset = 0);
};

}// namespace v1
}// namespace spotify

#endif

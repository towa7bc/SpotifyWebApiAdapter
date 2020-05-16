//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP

#include <memory>             // for shared_ptr
#include <nlohmann/json.hpp>  // for json
#include <string>             // for string
#include <string_view>        // for string_view
#include <vector>             // for vector

#include "Image.hpp"             // for Image
#include "detail/BaseModel.hpp"  // for BaseModel
#include "detail/Core.hpp"       // for create_ref
#include "model/modeldata.hpp"   // for json
namespace spotify::inline v1 {
class AuthenticationToken;
class Track;
class User;
struct Followers;
struct PlaylistTrack;
template <typename>
class Page;
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

class Playlist : public BaseModel {
  using json_t = nlohmann::json;

 public:
  explicit Playlist(const model::playlist &);
  explicit Playlist(model::playlist &&) noexcept;
  Playlist() = default;
  Playlist(const Playlist &) = default;
  ~Playlist() override = default;
  Playlist &operator=(const Playlist &) = default;
  Playlist &operator=(Playlist &&) noexcept = default;
  Playlist(Playlist &&) noexcept = default;
  bool _collaborative{false};
  std::string _description;
  std::string _external_url;
  Ref<Followers> _followers;
  std::string _href;
  std::string _id;
  std::vector<Image> _images;
  std::string _name;
  Ref<User> _owner;
  bool _public{false};
  Ref<Page<PlaylistTrack>> _tracks;
  std::string _type;
  std::string _uri;
  static Page<Playlist> get_users_playlists(std::string_view user_id,
                                            const AuthenticationToken &token);
  static Page<Playlist> get_users_playlists(const User &user,
                                            const AuthenticationToken &token);
  static Page<Playlist> get_playlist(std::string_view user_id,
                                     std::string_view playlist_id,
                                     const AuthenticationToken &token);
  static Page<Playlist> get_playlist(const User &user,
                                     std::string_view playlist_id,
                                     const AuthenticationToken &token);
  static Page<PlaylistTrack> get_playlist_tracks(
      std::string_view user_id, std::string_view playlist_id,
      const AuthenticationToken &token);
  [[nodiscard]] Page<PlaylistTrack> get_playlist_tracks(
      const AuthenticationToken &token) const;
  void add_track(const Track &track, AuthenticationToken &token) const;
  void add_tracks(const std::vector<Track> &track_uris,
                  AuthenticationToken &token) const;
  static Playlist create_playlist(std::string_view user_id,
                                  std::string_view name, bool is_public,
                                  const AuthenticationToken &token);
  static void update_users_playlist(std::string_view user_id,
                                    std::string_view playlist_id,
                                    std::string_view name, bool is_public,
                                    const AuthenticationToken &token);
  void update_users_playlist(std::string_view name, bool is_public,
                             const AuthenticationToken &token) const;
  static Page<Playlist> get_featured_playlists(const AuthenticationToken &token,
                                               std::string_view locale = "",
                                               std::string_view country = "",
                                               std::string_view timestamp = "",
                                               int limit = 20, int offset = 0);
};

}  // namespace spotify::inline v1

#endif

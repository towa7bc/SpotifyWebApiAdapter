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

#include "Followers.hpp"
#include "Image.hpp"  // for Image
#include "Page.hpp"
#include "PlaylistTrack.hpp"
#include "User.hpp"
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
  bool collaborative_{false};
  std::string description_;
  std::string external_url_;
  Followers followers_;
  std::string href_;
  std::string id_;
  std::vector<Image> images_;
  std::string name_;
  User owner_;
  bool public_{false};
  Page<PlaylistTrack> tracks_;
  std::string type_;
  std::string uri_;
  static Page<Playlist> GetUsersPlaylists(std::string_view user_id,
                                          const AuthenticationToken &token);
  static Page<Playlist> GetUsersPlaylists(const User &user,
                                          const AuthenticationToken &token);
  static Page<Playlist> GetPlaylist(std::string_view user_id,
                                    std::string_view playlist_id,
                                    const AuthenticationToken &token);
  static Page<Playlist> GetPlaylist(const User &user,
                                    std::string_view playlist_id,
                                    const AuthenticationToken &token);
  static Page<PlaylistTrack> GetPlaylistTracks(
      std::string_view user_id, std::string_view playlist_id,
      const AuthenticationToken &token);
  [[nodiscard]] Page<PlaylistTrack> GetPlaylistTracks(
      const AuthenticationToken &token) const;
  void AddTrack(const Track &track, AuthenticationToken &token) const;
  void AddTracks(const std::vector<Track> &track_uris,
                 AuthenticationToken &token) const;
  static Playlist CreatePlaylist(std::string_view user_id,
                                 std::string_view name, bool is_public,
                                 const AuthenticationToken &token);
  static void UpdateUsersPlaylist(std::string_view user_id,
                                  std::string_view playlist_id,
                                  std::string_view name, bool is_public,
                                  const AuthenticationToken &token);
  void UpdateUsersPlaylist(std::string_view name, bool is_public,
                           const AuthenticationToken &token) const;
  static Page<Playlist> GetFeaturedPlaylists(const AuthenticationToken &token,
                                             std::string_view locale = "",
                                             std::string_view country = "",
                                             std::string_view timestamp = "",
                                             int limit = 20, int offset = 0);
};

}  // namespace spotify::inline v1

#endif

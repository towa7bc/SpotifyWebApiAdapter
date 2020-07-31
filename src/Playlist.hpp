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
namespace spotify {
inline namespace v1 {
class AuthenticationToken;
class Track;
class User;
struct Followers;
struct PlaylistTrack;
template <typename>
class Page;
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

class Playlist : public BaseModel {
  using json_t = nlohmann::json;

 public:
  explicit Playlist(model::playlist);
  Playlist() = default;

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

  [[nodiscard]] bool isCollaborative() const { return collaborative_; }
  void setCollaborative(bool collaborative) { collaborative_ = collaborative; }
  [[nodiscard]] const std::string &getDescription() const {
    return description_;
  }
  void setDescription(const std::string &description) {
    description_ = description;
  }
  [[nodiscard]] const std::string &getExternalUrl() const {
    return external_url_;
  }
  void setExternalUrl(const std::string &externalUrl) {
    external_url_ = externalUrl;
  }
  [[nodiscard]] const Followers &getFollowers() const { return followers_; }
  void setFollowers(const Followers &followers) { followers_ = followers; }
  [[nodiscard]] const std::string &getHref() const { return href_; }
  void setHref(const std::string &href) { href_ = href; }
  [[nodiscard]] const std::string &getId() const { return id_; }
  void setId(const std::string &id) { id_ = id; }
  [[nodiscard]] const std::vector<Image> &getImages() const { return images_; }
  void setImages(const std::vector<Image> &images) { images_ = images; }
  [[nodiscard]] const std::string &getName() const { return name_; }
  void setName(const std::string &name) { name_ = name; }
  [[nodiscard]] const User &getOwner() const { return owner_; }
  void setOwner(const User &owner) { owner_ = owner; }
  [[nodiscard]] bool isPublic() const { return public_; }
  void setPublic(bool b_public) { public_ = b_public; }
  [[nodiscard]] const Page<PlaylistTrack> &getTracks() const { return tracks_; }
  void setTracks(const Page<PlaylistTrack> &tracks) { tracks_ = tracks; }
  [[nodiscard]] const std::string &getType() const { return type_; }
  void setType(const std::string &type) { type_ = type; }
  [[nodiscard]] const std::string &getUri() const { return uri_; }
  void setUri(const std::string &uri) { uri_ = uri; }

 private:
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
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

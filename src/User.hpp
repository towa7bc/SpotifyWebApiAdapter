//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_USER_HPP
#define SPOTIFYWEBAPIADAPTER_USER_HPP

#include <nlohmann/json.hpp>  // for json
#include <string>             // for string
#include <string_view>        // for string_view
#include <vector>             // for vector

#include "AuthenticationToken.hpp"
#include "Image.hpp"             // for Image
#include "detail/BaseModel.hpp"  // for BaseModel
#include "model/modeldata.hpp"   // for json

namespace spotify::inline v1 {
class AuthenticationToken;
class Playlist;
class Track;
template <typename>
class Page;
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

class User : public BaseModel {
  using json_t = nlohmann::json;

 public:
  explicit User(const model::user &);
  explicit User(model::user &&) noexcept;
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
  std::vector<Image> _images;
  std::string _product;
  std::string _type;
  std::string _uri;
  static User get_user(std::string_view user_id);
  static User get_current_user_profile(const AuthenticationToken &token);
  [[nodiscard]] Page<Playlist> get_playlists(
      const AuthenticationToken &token) const;
  static Page<Track> get_user_saved_tracks(const AuthenticationToken &token,
                                           int limit = 20, int offset = 0);
  Page<Track> get_saved_tracks(const AuthenticationToken &token, int limit = 20,
                               int offset = 0);
  void save_tracks(const std::vector<std::string> &ids,
                   const AuthenticationToken &token);
  void delete_tracks(const std::vector<std::string> &ids,
                     const AuthenticationToken &token);
  bool are_saved(const std::vector<std::string> &ids,
                 const AuthenticationToken &token);
  bool is_saved(std::string_view id, const AuthenticationToken &token);
};

}  // namespace spotify::inline v1

#endif

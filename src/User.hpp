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

namespace spotify {
inline namespace v1 {
class AuthenticationToken;
class Playlist;
class Track;
template <typename>
class Page;
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

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
  std::string country_;
  std::string displayName_;
  std::string email_address_;
  std::string external_url_;
  std::string href_;
  std::string id_;
  std::vector<Image> images_;
  std::string product_;
  std::string type_;
  std::string uri_;
  static User GetUser(std::string_view user_id);
  static User GetCurrentUserProfile(const AuthenticationToken &token);
  [[nodiscard]] Page<Playlist> GetPlaylists(
      const AuthenticationToken &token) const;
  static Page<Track> GetUserSavedTracks(const AuthenticationToken &token,
                                        int limit = 20, int offset = 0);
  Page<Track> GetSavedTracks(const AuthenticationToken &token, int limit = 20,
                             int offset = 0);
  void SaveTracks(const std::vector<std::string> &ids,
                  const AuthenticationToken &token);
  void DeleteTracks(const std::vector<std::string> &ids,
                    const AuthenticationToken &token);
  bool AreSaved(const std::vector<std::string> &ids,
                const AuthenticationToken &token);
  bool IsSaved(std::string_view id, const AuthenticationToken &token);
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

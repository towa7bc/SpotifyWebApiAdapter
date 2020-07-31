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
  explicit User(model::user);
  User() = default;

  [[nodiscard]] const std::string &getCountry() const { return country_; }
  void setCountry(const std::string &country) { country_ = country; }
  [[nodiscard]] const std::string &getDisplayName() const {
    return displayName_;
  }
  void setDisplayName(const std::string &displayName) {
    displayName_ = displayName;
  }
  [[nodiscard]] const std::string &getEmailAddress() const {
    return email_address_;
  }
  void setEmailAddress(const std::string &emailAddress) {
    email_address_ = emailAddress;
  }
  [[nodiscard]] const std::string &getExternalUrl() const {
    return external_url_;
  }
  void setExternalUrl(const std::string &externalUrl) {
    external_url_ = externalUrl;
  }
  [[nodiscard]] const std::string &getHref() const { return href_; }
  void setHref(const std::string &href) { href_ = href; }
  [[nodiscard]] const std::string &getId() const { return id_; }
  void setId(const std::string &id) { id_ = id; }
  [[nodiscard]] const std::vector<Image> &getImages() const { return images_; }
  void setImages(const std::vector<Image> &images) { images_ = images; }
  [[nodiscard]] const std::string &getProduct() const { return product_; }
  void setProduct(const std::string &product) { product_ = product; }
  [[nodiscard]] const std::string &getType() const { return type_; }
  void setType(const std::string &type) { type_ = type; }
  [[nodiscard]] const std::string &getUri() const { return uri_; }
  void setUri(const std::string &uri) { uri_ = uri; }

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

 private:
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
};

}  // namespace v1
}  // namespace spotify

#endif

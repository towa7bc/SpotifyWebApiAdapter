//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_TRACK_HPP
#define SPOTIFYWEBAPIADAPTER_TRACK_HPP

#include <memory>             // for shared_ptr
#include <nlohmann/json.hpp>  // for json
#include <string>             // for string
#include <vector>             // for vector

#include "Album.hpp"
#include "Artist.hpp"
#include "detail/BaseModel.hpp"  // for BaseModel
#include "detail/Core.hpp"       // for create_ref
#include "model/modeldata.hpp"   // for json
namespace spotify {
inline namespace v1 {
class Album;
class Artist;
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

class Track : public BaseModel {
  using json_t = nlohmann::json;

 public:
  explicit Track(const model::track &);
  explicit Track(model::track &&) noexcept;
  explicit Track(const model::savedtrack &);
  explicit Track(model::savedtrack &&t_track) noexcept;
  Track() = default;
  Track(const Track &) = default;
  ~Track() override = default;
  Track &operator=(const Track &) = default;
  Track &operator=(Track &&) noexcept = default;
  Track(Track &&) noexcept = default;

  [[nodiscard]] const std::vector<Artist> &getArtists() const {
    return artists_;
  }
  void setArtists(const std::vector<Artist> &artists) { artists_ = artists; }
  [[nodiscard]] const std::vector<std::string> &getAvailableMarkets() const {
    return available_markets_;
  }
  void setAvailableMarkets(const std::vector<std::string> &availableMarkets) {
    available_markets_ = availableMarkets;
  }
  [[nodiscard]] const std::vector<std::string> &getExternalId() const {
    return external_id_;
  }
  void setExternalId(const std::vector<std::string> &externalId) {
    external_id_ = externalId;
  }
  [[nodiscard]] const std::vector<std::string> &getExternalUrl() const {
    return external_url_;
  }
  void setExternalUrl(const std::vector<std::string> &externalUrl) {
    external_url_ = externalUrl;
  }
  [[nodiscard]] const std::vector<std::string> &getGenres() const {
    return genres_;
  }
  void setGenres(const std::vector<std::string> &genres) { genres_ = genres; }
  [[nodiscard]] const std::string &getHref() const { return href_; }
  void setHref(const std::string &href) { href_ = href; }
  [[nodiscard]] const std::string &getId() const { return id_; }
  void setId(const std::string &id) { id_ = id; }
  [[nodiscard]] const std::string &getName() const { return name_; }
  void setName(const std::string &name) { name_ = name; }
  [[nodiscard]] const std::string &getPopularity() const { return popularity_; }
  void setPopularity(const std::string &popularity) {
    popularity_ = popularity;
  }
  [[nodiscard]] const std::string &getPreviewUrl() const {
    return preview_url_;
  }
  void setPreviewUrl(const std::string &previewUrl) {
    preview_url_ = previewUrl;
  }
  [[nodiscard]] const std::string &getType() const { return type_; }
  void setType(const std::string &type) { type_ = type; }
  [[nodiscard]] const std::string &getUri() const { return uri_; }
  void setUri(const std::string &uri) { uri_ = uri; }
  [[nodiscard]] int getDiscNumber() const { return disc_number_; }
  void setDiscNumber(int discNumber) { disc_number_ = discNumber; }
  [[nodiscard]] int getDuration() const { return duration_; }
  void setDuration(int duration) { duration_ = duration; }
  [[nodiscard]] bool isExplicit() const { return explicit_; }
  void setExplicit(bool b_explicit) { explicit_ = b_explicit; }
  [[nodiscard]] int getTrackNumber() const { return track_number_; }
  void setTrackNumber(int trackNumber) { track_number_ = trackNumber; }
  [[nodiscard]] const Album &getAlbum() const { return album_; }
  void setAlbum(const Album &album) { album_ = album; }

 private:
  std::vector<Artist> artists_;
  std::vector<std::string> available_markets_;
  std::vector<std::string> external_id_;
  std::vector<std::string> external_url_;
  std::vector<std::string> genres_;
  std::string href_;
  std::string id_;
  std::string name_;
  std::string popularity_;
  std::string preview_url_;
  std::string type_;
  std::string uri_;
  int disc_number_{};
  int duration_{};
  bool explicit_{};
  int track_number_{};
  Album album_;
};

}  // namespace v1
}  // namespace spotify

#endif

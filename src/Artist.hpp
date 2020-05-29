//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_ARTIST_HPP
#define SPOTIFYWEBAPIADAPTER_ARTIST_HPP

#include <nlohmann/json.hpp>  // for json
#include <string>             // for string
#include <vector>             // for vector

#include "Image.hpp"             // for Image
#include "detail/BaseModel.hpp"  // for BaseModel
#include "model/modeldata.hpp"   // for json
namespace spotify {
inline namespace v1 {
class Album;
class Track;
template <typename>
class Page;
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

class Artist : public BaseModel {
  using json_t = nlohmann::json;

 public:
  explicit Artist(const model::artist &);
  explicit Artist(model::artist &&t_artist) noexcept;
  Artist() = default;
  Artist(const Artist &) = default;
  ~Artist() override = default;
  Artist &operator=(const Artist &) = default;
  Artist &operator=(Artist &&) noexcept = default;
  Artist(Artist &&) noexcept = default;
  static Artist GetArtist(const std::string &artist_id);
  static std::vector<Artist> GetArtists(
      const std::vector<std::string> &artist_ids);
  static Page<Artist> Search(std::string &artistName, std::string &year,
                             std::string &genre, std::string &upc,
                             std::string &isrc, int limit = 20, int offset = 0);
  Page<Album> GetAlbums();
  static std::vector<Track> GetTopTracks(
      const std::string &artist_id, const std::string &country_code = "US");
  [[nodiscard]] std::vector<Track> GetTopTracks(
      const std::string &country_code = "US") const;
  static std::vector<Artist> GetRelatedArtists(
      const std::string &artist_id, const std::string &country_code = "US");
  [[nodiscard]] std::vector<Artist> GetRelatedArtists(
      const std::string &country_code = "US") const;

  [[nodiscard]] const std::vector<std::string> &getGenres() const {
    return genres_;
  }
  void setGenres(const std::vector<std::string> &genres) { genres_ = genres; }
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
  [[nodiscard]] const std::string &getName() const { return name_; }
  void setName(const std::string &name) { name_ = name; }
  [[nodiscard]] int getPopularity() const { return popularity_; }
  void setPopularity(int popularity) { popularity_ = popularity; }
  [[nodiscard]] const std::string &getType() const { return type_; }
  void setType(const std::string &type) { type_ = type; }
  [[nodiscard]] const std::string &getUri() const { return uri_; }
  void setUri(const std::string &uri) { uri_ = uri; }

 private:
  std::vector<std::string> genres_;
  std::string external_url_;
  std::string href_;
  std::string id_;
  std::vector<Image> images_;
  std::string name_;
  int popularity_{};
  std::string type_;
  std::string uri_;
};

}  // namespace v1
}  // namespace spotify

#endif

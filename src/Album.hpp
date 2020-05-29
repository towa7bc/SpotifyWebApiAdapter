//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_ALBUM_HPP
#define SPOTIFYWEBAPIADAPTER_ALBUM_HPP

#include <boost/date_time/posix_time/ptime.hpp>  // for ptime
#include <memory>                                // for shared_ptr
#include <nlohmann/json.hpp>                     // for json
#include <string>                                // for string
#include <string_view>                           // for string_view
#include <vector>                                // for vector

#include "Artist.hpp"
#include "Image.hpp"  // for Image
#include "Page.hpp"
#include "detail/BaseModel.hpp"  // for BaseModel
#include "detail/Core.hpp"       // for create_ref
#include "model/modeldata.hpp"   // for json
namespace spotify {
inline namespace v1 {
class Artist;
class AuthenticationToken;
class Track;
template <typename>
class Page;
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

class Album : public BaseModel {
  using json_t = nlohmann::json;

 public:
  explicit Album(const model::album &);
  explicit Album(model::album &&) noexcept;
  Album() = default;
  Album(const Album &) = default;
  ~Album() override = default;
  Album &operator=(const Album &) = default;
  Album &operator=(Album &&) noexcept = default;
  Album(Album &&) noexcept = default;
  static Page<Album> GetArtistAlbums(std::string_view artist_id);
  static Page<Album> Search(std::string &albumName, std::string &artistName,
                            std::string &year, std::string &genre,
                            std::string &upc, std::string &isrc, int limit,
                            int offset);
  static Album GetAlbum(std::string_view album_id);
  static std::vector<Album> GetAlbums(
      const std::vector<std::string> &album_ids);
  static Page<Track> GetAlbumTracks(std::string_view album_id, int limit = 20,
                                    int offset = 0);
  [[nodiscard]] Page<Track> GetAlbumTracks(int limit, int offset) const;
  Page<Album> GetNewReleases(const AuthenticationToken &token,
                             std::string_view country, int limit, int offset);

  enum class AlbumType { Album, Single, Compilation };

  [[nodiscard]] AlbumType getAlbumType() const { return album_type_; }
  void setAlbumType(AlbumType albumType) { album_type_ = albumType; }
  [[nodiscard]] const std::vector<Artist> &getArtists() const {
    return artists_;
  }
  void setArtists(const std::vector<Artist> &artists) { artists_ = artists; }
  [[nodiscard]] const std::vector<std::string> &getAvailableMarkets() const {
    return availableMarkets_;
  }
  void setAvailableMarkets(const std::vector<std::string> &availableMarkets) {
    availableMarkets_ = availableMarkets;
  }
  [[nodiscard]] const std::string &getExternalId() const {
    return external_id_;
  }
  void setExternalId(const std::string &externalId) {
    external_id_ = externalId;
  }
  [[nodiscard]] const std::string &getExternalUrl() const {
    return external_url_;
  }
  void setExternalUrl(const std::string &externalUrl) {
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
  [[nodiscard]] const std::vector<Image> &getImages() const { return images_; }
  void setImages(const std::vector<Image> &images) { images_ = images; }
  [[nodiscard]] const std::string &getName() const { return name_; }
  void setName(const std::string &name) { name_ = name; }
  [[nodiscard]] int getPopularity() const { return popularity_; }
  void setPopularity(int popularity) { popularity_ = popularity; }
  [[nodiscard]] const boost::posix_time::ptime &getReleaseDate() const {
    return release_date_;
  }
  void setReleaseDate(const boost::posix_time::ptime &releaseDate) {
    release_date_ = releaseDate;
  }
  [[nodiscard]] const std::string &getReleaseDatePrecision() const {
    return release_date_precision_;
  }
  void setReleaseDatePrecision(const std::string &releaseDatePrecision) {
    release_date_precision_ = releaseDatePrecision;
  }
  [[nodiscard]] const std::string &getType() const { return type_; }
  void setType(const std::string &type) { type_ = type; }
  [[nodiscard]] const std::string &getUri() const { return uri_; }
  void setUri(const std::string &uri) { uri_ = uri; }
  [[nodiscard]] const Page<Track> &getTracks() const { return tracks_; }
  void setTracks(const Page<Track> &tracks) { tracks_ = tracks; }

 private:
  AlbumType album_type_{};
  std::vector<Artist> artists_;
  std::vector<std::string> availableMarkets_;
  std::string external_id_;
  std::string external_url_;
  std::vector<std::string> genres_;
  std::string href_;
  std::string id_;
  std::vector<Image> images_;
  std::string name_;
  int popularity_{0};
  boost::posix_time::ptime release_date_;
  std::string release_date_precision_;
  std::string type_;
  std::string uri_;
  Page<Track> tracks_;
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

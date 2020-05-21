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
  std::vector<std::string> genres_;
  std::string external_url_;
  std::string href_;
  std::string id_;
  std::vector<Image> images_;
  std::string name_;
  int popularity_{};
  std::string type_;
  std::string uri_;
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
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

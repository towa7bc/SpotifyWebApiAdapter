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
namespace spotify::inline v1 {
class Album;
class Track;
template <typename>
class Page;
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

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
  std::vector<std::string> _genres;
  std::string _external_url;
  std::string _href;
  std::string _id;
  std::vector<Image> _images;
  std::string _name;
  int _popularity{};
  std::string _type;
  std::string _uri;
  static Artist get_artist(const std::string &artist_id);
  static std::vector<Artist> get_artists(
      const std::vector<std::string> &artist_ids);
  static Page<Artist> search(std::string &artistName, std::string &year,
                             std::string &genre, std::string &upc,
                             std::string &isrc, int limit = 20, int offset = 0);
  Page<Album> get_albums();
  static std::vector<Track> get_top_tracks(
      const std::string &artist_id, const std::string &country_code = "US");
  [[nodiscard]] std::vector<Track> get_top_tracks(
      const std::string &country_code = "US") const;
  static std::vector<Artist> get_related_artists(
      const std::string &artist_id, const std::string &country_code = "US");
  [[nodiscard]] std::vector<Artist> get_related_artists(
      const std::string &country_code = "US") const;
};

}  // namespace spotify::inline v1

#endif

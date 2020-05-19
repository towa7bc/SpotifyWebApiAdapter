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
namespace spotify::inline v1 {
class Artist;
class AuthenticationToken;
class Track;
template <typename>
class Page;
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

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
  enum class AlbumType { Album, Single, Compilation };
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
};

}  // namespace spotify::inline v1

#endif

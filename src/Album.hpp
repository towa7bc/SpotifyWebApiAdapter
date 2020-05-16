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
#include "Image.hpp"             // for Image
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
  AlbumType _album_type{};
  std::vector<Artist> _artists;
  std::vector<std::string> _availableMarkets;
  std::string _external_id;
  std::string _external_url;
  std::vector<std::string> _genres;
  std::string _href;
  std::string _id;
  std::vector<Image> _images;
  std::string _name;
  int _popularity{0};
  boost::posix_time::ptime _release_date;
  std::string _release_date_precision;
  std::string _type;
  std::string _uri;
  Ref<Page<Track>> _ptracks;
  static Page<Album> get_artist_albums(std::string_view artist_id);
  static Page<Album> search(std::string &albumName, std::string &artistName,
                            std::string &year, std::string &genre,
                            std::string &upc, std::string &isrc, int limit,
                            int offset);
  static Album get_album(std::string_view album_id);
  static std::vector<Album> get_albums(
      const std::vector<std::string> &album_ids);
  static Page<Track> get_album_tracks(std::string_view album_id, int limit = 20,
                                      int offset = 0);
  [[nodiscard]] Page<Track> get_album_tracks(int limit, int offset) const;
  Page<Album> get_new_releases(const AuthenticationToken &token,
                               std::string_view country, int limit, int offset);
};

}  // namespace spotify::inline v1

#endif

//
// Created by Michael Wittmann on 12/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_BROWSE_HPP
#define SPOTIFYWEBAPIADAPTER_BROWSE_HPP

#include <nlohmann/json.hpp>  // for json
#include <string_view>        // for string_view

#include "AuthenticationToken.hpp"
#include "Page.hpp"             // for Page
#include "model/modeldata.hpp"  // for json
namespace spotify::inline v1 {
class Album;
class AuthenticationToken;
class Playlist;
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

class Browse {
  using json_t = nlohmann::json;

 public:
  static Page<Playlist> get_featured_playlists(const AuthenticationToken &token,
                                               std::string_view locale = "",
                                               std::string_view country = "",
                                               std::string_view timestamp = "",
                                               int limit = 20, int offset = 0);
  static Page<Album> get_new_releases(const AuthenticationToken &token,
                                      std::string_view country = "",
                                      int limit = 20, int offset = 0);
};

}  // namespace spotify::inline v1

#endif

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
namespace spotify {
inline namespace v1 {
class Album;
class AuthenticationToken;
class Playlist;
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

class Browse {
  using json_t = nlohmann::json;

 public:
  static Page<Playlist> GetFeaturedPlaylists(const AuthenticationToken &token,
                                             std::string_view locale = "",
                                             std::string_view country = "",
                                             std::string_view timestamp = "",
                                             int limit = 20, int offset = 0);
  static Page<Album> GetNewReleases(const AuthenticationToken &token,
                                    std::string_view country = "",
                                    int limit = 20, int offset = 0);
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

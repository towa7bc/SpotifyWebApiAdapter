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

namespace spotify::inline v1 {

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

}  // namespace spotify::inline v1

#endif

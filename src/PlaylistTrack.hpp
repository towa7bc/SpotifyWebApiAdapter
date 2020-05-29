//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP

#include <boost/date_time/gregorian/gregorian_types.hpp>    // for day_clock
#include <boost/date_time/posix_time/posix_time_types.hpp>  // for second_clock
#include <boost/date_time/posix_time/ptime.hpp>             // for ptime
#include <memory>                                           // for shared_ptr

#include "Track.hpp"
#include "User.hpp"
#include "detail/Core.hpp"  // for Ref
namespace spotify {
inline namespace v1 {
class Track;
class User;
}  // namespace v1
}  // namespace spotify
namespace spotify {
inline namespace v1 {
namespace model {
struct playlisttrack;
}
}  // namespace v1
}  // namespace spotify

namespace spotify {
inline namespace v1 {

struct PlaylistTrack {
  explicit PlaylistTrack(const model::playlisttrack &);
  explicit PlaylistTrack(model::playlisttrack &&) noexcept;
  PlaylistTrack() = default;
  PlaylistTrack(const PlaylistTrack &) = default;
  ~PlaylistTrack() = default;
  PlaylistTrack &operator=(const PlaylistTrack &) = default;
  PlaylistTrack &operator=(PlaylistTrack &&) noexcept = default;
  PlaylistTrack(PlaylistTrack &&) noexcept = default;

  [[nodiscard]] const User &getAddedBy() const { return added_by_; }
  void setAddedBy(const User &addedBy) { added_by_ = addedBy; }
  [[nodiscard]] const boost::posix_time::ptime &getAddedAt() const {
    return added_at_;
  }
  void setAddedAt(const boost::posix_time::ptime &addedAt) {
    added_at_ = addedAt;
  }
  [[nodiscard]] const Track &getTrack() const { return track_; }
  void setTrack(const Track &track) { track_ = track; }

 private:
  User added_by_;
  boost::posix_time::ptime added_at_{
      boost::gregorian::day_clock::universal_day(),
      boost::posix_time::second_clock::universal_time().time_of_day()};
  Track track_;
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP

#include <boost/date_time/gregorian/gregorian_types.hpp>    // for day_clock
#include <boost/date_time/posix_time/posix_time_types.hpp>  // for second_clock
#include <boost/date_time/posix_time/ptime.hpp>             // for ptime
#include <memory>                                           // for shared_ptr

#include "detail/Core.hpp"  // for Ref
namespace spotify::inline v1 {
class Track;
class User;
}  // namespace spotify::inline v1
namespace spotify::inline v1 {
namespace model {
struct playlisttrack;
}
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

struct PlaylistTrack {
  explicit PlaylistTrack(const model::playlisttrack &);
  explicit PlaylistTrack(model::playlisttrack &&) noexcept;
  PlaylistTrack() = default;
  PlaylistTrack(const PlaylistTrack &) = default;
  ~PlaylistTrack() = default;
  PlaylistTrack &operator=(const PlaylistTrack &) = default;
  PlaylistTrack &operator=(PlaylistTrack &&) noexcept = default;
  PlaylistTrack(PlaylistTrack &&) noexcept = default;
  Ref<User> _added_by;
  boost::posix_time::ptime _added_at{
      boost::gregorian::day_clock::universal_day(),
      boost::posix_time::second_clock::universal_time().time_of_day()};
  Ref<Track> _track;
};

}  // namespace spotify::inline v1

#endif

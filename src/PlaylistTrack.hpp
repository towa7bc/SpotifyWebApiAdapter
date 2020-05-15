//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLISTTRACK_HPP

#include "Track.hpp"
#include "User.hpp"
#include "detail/Core.hpp"
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace spotify::inline v1 {

class Track;
class User;

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
    boost::posix_time::ptime _added_at{boost::gregorian::day_clock::universal_day(),
                                       boost::posix_time::second_clock::universal_time().time_of_day()};
    Ref<Track> _track;
};

}// namespace v1

#endif

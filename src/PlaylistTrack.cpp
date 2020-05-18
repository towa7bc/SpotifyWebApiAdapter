//
// Created by Michael Wittmann on 07/05/2020.
//

#include "PlaylistTrack.hpp"

#include <boost/date_time/posix_time/time_parsers.hpp>  // for time_from_string

#include "model/modeldata.hpp"  // for playlisttrack

namespace spotify::inline v1 {

PlaylistTrack::PlaylistTrack(const model::playlisttrack &t_plt)
    : _added_by(t_plt.added_by),
      _added_at(boost::posix_time::time_from_string(t_plt.added_at)),
      _track(t_plt.track_) {}

PlaylistTrack::PlaylistTrack(model::playlisttrack &&t_plt) noexcept
    : _added_by(t_plt.added_by),
      _added_at(boost::posix_time::time_from_string(t_plt.added_at)),
      _track(t_plt.track_) {}

}  // namespace spotify::inline v1

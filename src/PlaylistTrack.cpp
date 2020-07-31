//
// Created by Michael Wittmann on 07/05/2020.
//

#include "PlaylistTrack.hpp"

#include <boost/date_time/posix_time/time_parsers.hpp>  // for time_from_string

#include "model/modeldata.hpp"  // for playlisttrack
#include <type_traits>

namespace spotify {
inline namespace v1 {

PlaylistTrack::PlaylistTrack(model::playlisttrack t_plt)
    : added_by_(std::move(t_plt.added_by)),
      added_at_(boost::posix_time::time_from_string(t_plt.added_at)),
      track_(std::move(t_plt.track_)) {}

}  // namespace v1
}  // namespace spotify
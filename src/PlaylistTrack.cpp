//
// Created by Michael Wittmann on 07/05/2020.
//

#include "PlaylistTrack.hpp"

namespace spotify {

inline namespace v1 {

PlaylistTrack::PlaylistTrack(const model::playlisttrack &t_plt) : _added_by(create_ref<User>(t_plt.added_by)),
                                                                  _added_at(boost::posix_time::time_from_string(t_plt.added_at)),
                                                                  _track(create_ref<Track>(t_plt.track_)) {
}

PlaylistTrack::PlaylistTrack(model::playlisttrack &&t_plt) noexcept : _added_by(create_ref<User>(t_plt.added_by)),
                                                                      _added_at(boost::posix_time::time_from_string(t_plt.added_at)),
                                                                      _track(create_ref<Track>(t_plt.track_)) {
}

}// namespace v1
}// namespace spotify

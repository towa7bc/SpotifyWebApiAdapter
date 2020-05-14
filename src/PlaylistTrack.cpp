//
// Created by Michael Wittmann on 07/05/2020.
//

#include "PlaylistTrack.hpp"

namespace spotify {

inline namespace v1 {

spotify::PlaylistTrack::PlaylistTrack(const spotify::model::playlisttrack &t_plt) : _added_by(std::make_shared<spotify::User>(t_plt.added_by)),
                                                                                    _added_at(boost::posix_time::time_from_string(t_plt.added_at)),
                                                                                    _track(std::make_shared<spotify::Track>(t_plt.track_)) {
}

spotify::PlaylistTrack::PlaylistTrack(spotify::model::playlisttrack &&t_plt) noexcept : _added_by(std::make_shared<spotify::User>(t_plt.added_by)),
                                                                                        _added_at(boost::posix_time::time_from_string(t_plt.added_at)),
                                                                                        _track(std::make_shared<spotify::Track>(t_plt.track_)) {
}

}// namespace v1
}// namespace spotify

//
// Created by Michael Wittmann on 07/05/2020.
//

#include "PlaylistTrack.hpp"

namespace spotify {

inline namespace v1 {

spotify::PlaylistTrack::PlaylistTrack(const spotify::model::playlisttrack &) {
}

spotify::PlaylistTrack::PlaylistTrack(spotify::model::playlisttrack &&) noexcept {
}

}// namespace v1
}// namespace spotify
//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Track.hpp"
#include "Album.hpp"

namespace spotify {

inline namespace v1 {

spotify::Track::Track(const spotify::model::track &) {
}

spotify::Track::Track(spotify::model::track &&) noexcept {
}

}// namespace v1
}// namespace spotify
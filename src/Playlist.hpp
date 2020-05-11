//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP
#define SPOTIFYWEBAPIADAPTER_PLAYLIST_HPP

#include "detail/BaseModel.hpp"

namespace spotify {

inline namespace v1 {

class Playlist : public BaseModel {
public:
    Playlist() = default;
    Playlist(const Playlist &) = default;
    ~Playlist() = default;
    Playlist &operator=(const Playlist &) = default;
    Playlist &operator=(Playlist &&) = default;
    Playlist(Playlist &&) noexcept = default;
};

}// namespace v1
}// namespace spotify

#endif

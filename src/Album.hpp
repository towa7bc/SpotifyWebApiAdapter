//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_ALBUM_HPP
#define SPOTIFYWEBAPIADAPTER_ALBUM_HPP

#include "Page.hpp"
#include "detail/BaseModel.hpp"
#include "model/modeldata.hpp"

namespace spotify {

inline namespace v1 {

template<typename>
class Page;

class Album : public BaseModel {
    using json_t = nlohmann::json;

public:
    Album() = default;
    Album(const Album &) = default;
    ~Album() override = default;
    Album &operator=(const Album &) = default;
    Album &operator=(Album &&) noexcept = default;
    Album(Album &&) noexcept = default;
    enum class AlbumType {
        Album,
        Single,
        Compilation
    };
    AlbumType _album_type;
    static spotify::Page<spotify::Album> get_artist_albums(std::string_view artist_id);
};

}// namespace v1
}// namespace spotify

#endif

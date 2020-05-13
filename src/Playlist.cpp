//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Playlist.hpp"
namespace spotify {

inline namespace v1 {

spotify::Playlist::Playlist(const spotify::model::playlist &pl) {
    _href = pl.href;
    _id = pl.id;
    _uri = pl.uri;
    _name = pl.name;
    _external_url = pl.external_urls.at(0);
    for (const auto &item : pl.images) {
        spotify::Image image(item);
        _images.push_back(image);
    }
    _type = pl.type;
    _collaborative = pl.is_collaborative;
    _description = pl.description;
    _public = pl.is_public;
    _owner = std::make_shared<const spotify::User>(pl.owner);
    _followers._href = pl.followers_.href;
    _followers._total = pl.followers_.total;
    spotify::Page<spotify::PlaylistTrack> plt(pl.tracks);
    _tracks = std::make_shared<const spotify::Page<spotify::PlaylistTrack>>(plt);
}

}// namespace v1
}// namespace spotify
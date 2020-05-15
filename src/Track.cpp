//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Track.hpp"
#include "Album.hpp"

namespace spotify {

inline namespace v1 {

Track::Track(const model::track &t_track) : available_markets(t_track.available_markets),
                                            external_id(t_track.external_ids),
                                            external_url(t_track.external_urls),
                                            genres(t_track.genres),
                                            href(t_track.href),
                                            id(t_track.id),
                                            name(t_track.name),
                                            popularity(t_track.popularity),
                                            preview_url(t_track.preview_url),
                                            type(t_track.type),
                                            uri(t_track.uri),
                                            disc_number(t_track.disc_number),
                                            duration(t_track.duration_ms),
                                            explicit_(t_track.is_explicit),
                                            track_number(t_track.track_number),
                                            album(create_ref<Album>(t_track.album_)) {
    artists.reserve(t_track.artists.capacity());
    for (const auto &item : t_track.artists) {
        Artist artist(item);
        artists.push_back(std::move(artist));
    }
}

Track::Track(model::track &&t_track) noexcept : available_markets(std::move(t_track.available_markets)),
                                                external_id(std::move(t_track.external_ids)),
                                                external_url(std::move(t_track.external_urls)),
                                                genres(std::move(t_track.genres)),
                                                href(std::move(t_track.href)),
                                                id(std::move(t_track.id)),
                                                name(std::move(t_track.name)),
                                                popularity(std::move(t_track.popularity)),
                                                preview_url(std::move(t_track.preview_url)),
                                                type(std::move(t_track.type)),
                                                uri(std::move(t_track.uri)),
                                                disc_number(t_track.disc_number),
                                                duration(t_track.duration_ms),
                                                explicit_(t_track.is_explicit),
                                                track_number(t_track.track_number),
                                                album(create_ref<Album>(t_track.album_)) {
    artists.reserve(t_track.artists.capacity());
    for (auto &item : t_track.artists) {
        Artist artist(std::move(item));
        artists.push_back(std::move(artist));
    }
}

Track::Track(const model::savedtrack &t_track) : available_markets(t_track.track_.available_markets),
                                                 external_id(t_track.track_.external_ids),
                                                 external_url(t_track.track_.external_urls),
                                                 genres(t_track.track_.genres),
                                                 href(t_track.track_.href),
                                                 id(t_track.track_.id),
                                                 name(t_track.track_.name),
                                                 popularity(t_track.track_.popularity),
                                                 preview_url(t_track.track_.preview_url),
                                                 type(t_track.track_.type),
                                                 uri(t_track.track_.uri),
                                                 disc_number(t_track.track_.disc_number),
                                                 duration(t_track.track_.duration_ms),
                                                 explicit_(t_track.track_.is_explicit),
                                                 track_number(t_track.track_.track_number),
                                                 album(create_ref<Album>(t_track.track_.album_)) {
    artists.reserve(t_track.track_.artists.capacity());
    for (const auto &item : t_track.track_.artists) {
        Artist artist(item);
        artists.push_back(std::move(artist));
    }
}

Track::Track(model::savedtrack &&t_track) noexcept : available_markets(std::move(t_track.track_.available_markets)),
                                                     external_id(std::move(t_track.track_.external_ids)),
                                                     external_url(std::move(t_track.track_.external_urls)),
                                                     genres(std::move(t_track.track_.genres)),
                                                     href(std::move(t_track.track_.href)),
                                                     id(std::move(t_track.track_.id)),
                                                     name(std::move(t_track.track_.name)),
                                                     popularity(std::move(t_track.track_.popularity)),
                                                     preview_url(std::move(t_track.track_.preview_url)),
                                                     type(std::move(t_track.track_.type)),
                                                     uri(std::move(t_track.track_.uri)),
                                                     disc_number(t_track.track_.disc_number),
                                                     duration(t_track.track_.duration_ms),
                                                     explicit_(t_track.track_.is_explicit),
                                                     track_number(t_track.track_.track_number),
                                                     album(create_ref<Album>(t_track.track_.album_)) {
    artists.reserve(t_track.track_.artists.capacity());
    for (auto &item : t_track.track_.artists) {
        Artist artist(std::move(item));
        artists.push_back(std::move(artist));
    }
}

}// namespace v1
}// namespace spotify

//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Track.hpp"
#include "Album.hpp"

namespace spotify {

inline namespace v1 {

spotify::Track::Track(const spotify::model::track &t_track) : available_markets(t_track.available_markets),
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
                                                              album(std::make_shared<spotify::Album>(t_track.album_)) {
    for (const auto &item : t_track.artists) {
        Artist artist(item);
        artists.push_back(artist);
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
                                                 album(std::make_shared<spotify::Album>(t_track.track_.album_)) {
    for (const auto &item : t_track.track_.artists) {
        Artist artist(item);
        artists.push_back(artist);
    }
}

}// namespace v1
}// namespace spotify

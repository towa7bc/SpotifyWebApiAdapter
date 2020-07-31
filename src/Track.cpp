//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Track.hpp"

#include <type_traits>  // for move

#include "Artist.hpp"  // for Artist

namespace spotify {
inline namespace v1 {

Track::Track(model::track t_track)
    : available_markets_(std::move(t_track.available_markets)),
      external_id_(std::move(t_track.external_ids)),
      external_url_(std::move(t_track.external_urls)),
      genres_(std::move(t_track.genres)),
      href_(std::move(t_track.href)),
      id_(std::move(t_track.id)),
      name_(std::move(t_track.name)),
      popularity_(std::move(t_track.popularity)),
      preview_url_(std::move(t_track.preview_url)),
      type_(std::move(t_track.type)),
      uri_(std::move(t_track.uri)),
      disc_number_(t_track.disc_number),
      duration_(t_track.duration_ms),
      explicit_(t_track.is_explicit),
      track_number_(t_track.track_number),
      album_(t_track.album_) {
  artists_.reserve(t_track.artists.size());
  for (auto &item : t_track.artists) {
    Artist artist(std::move(item));
    artists_.push_back(std::move(artist));
  }
}

Track::Track(model::savedtrack t_track)
    : available_markets_(std::move(t_track.track_.available_markets)),
      external_id_(std::move(t_track.track_.external_ids)),
      external_url_(std::move(t_track.track_.external_urls)),
      genres_(std::move(t_track.track_.genres)),
      href_(std::move(t_track.track_.href)),
      id_(std::move(t_track.track_.id)),
      name_(std::move(t_track.track_.name)),
      popularity_(std::move(t_track.track_.popularity)),
      preview_url_(std::move(t_track.track_.preview_url)),
      type_(std::move(t_track.track_.type)),
      uri_(std::move(t_track.track_.uri)),
      disc_number_(t_track.track_.disc_number),
      duration_(t_track.track_.duration_ms),
      explicit_(t_track.track_.is_explicit),
      track_number_(t_track.track_.track_number),
      album_(t_track.track_.album_) {
  artists_.reserve(t_track.track_.artists.size());
  for (auto &item : t_track.track_.artists) {
    Artist artist(std::move(item));
    artists_.push_back(std::move(artist));
  }
}

}  // namespace spotify::inline v1
}  // namespace spotify
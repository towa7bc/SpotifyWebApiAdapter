//
// Created by Michael Wittmann on 08/05/2020.
//

#if !defined(STLAB_CPP_VERSION_PRIVATE)
#define STLAB_CPP_VERSION_PRIVATE() 17
#endif

#include "Page.hpp"

#include <stlab/concurrency/default_executor.hpp>  // for default_executor
#include <stlab/concurrency/future.hpp>            // for async
#include <stlab/concurrency/utility.hpp>           // for blocking_get
#include <type_traits>                             // for move

#include "Album.hpp"              // for Album
#include "Artist.hpp"             // for Artist
#include "Playlist.hpp"           // for Playlist
#include "PlaylistTrack.hpp"      // for PlaylistTrack
#include "Track.hpp"              // for Track
#include "detail/BaseModel.hpp"   // for PageNotFoundException
#include "detail/HttpHelper.hpp"  // for HttpHelper
#include "model/modeldata.hpp"    // for page

namespace spotify {
inline namespace v1 {

template <typename T>
bool Page<T>::HasNextPage() const {
  return !next_.empty();
}

template <typename T>
void Page<T>::setHasNextPage(bool hasNextPage) {
  has_next_page_ = hasNextPage;
}

template <typename T>
bool Page<T>::HasPreviousPage() const {
  return !previous_.empty();
}

template <typename T>
void Page<T>::setHasPreviousPage(bool hasPreviousPage) {
  has_previous_page_ = hasPreviousPage;
}

template <typename T>
Page<T> Page<T>::getNextPage() {
  if (!HasNextPage()) {
    throw PageNotFoundException();
  }
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::Get1, next_);
  json_t j_obj = json_t::parse(stlab::blocking_get(local_future));

  if constexpr (std::is_same_v<T, Album>) {
    auto p = j_obj.get<model::page<model::album>>();
    Page<Album> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, Artist>) {
    auto p = j_obj.get<model::page<model::artist>>();
    Page<Artist> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, Track>) {
    auto p = j_obj.get<model::page<model::track>>();
    Page<Track> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, Playlist>) {
    auto p = j_obj.get<model::page<model::playlist>>();
    Page<Playlist> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, PlaylistTrack>) {
    auto p = j_obj.get<model::page<model::playlisttrack>>();
    Page<PlaylistTrack> page(p);
    return page;
  }
  return nullptr;
}

template <typename T>
Page<T> Page<T>::getPreviousPage() {
  if (!HasPreviousPage()) {
    throw PageNotFoundException();
  }
  auto local_future = stlab::async(stlab::default_executor,
                                   detail::HttpHelper::Get1, previous_);
  json_t j_obj = json_t::parse(stlab::blocking_get(local_future));

  if constexpr (std::is_same_v<T, Album>) {
    auto p = j_obj.get<model::page<model::album>>();
    Page<Album> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, Artist>) {
    auto p = j_obj.get<model::page<model::artist>>();
    Page<Artist> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, Track>) {
    auto p = j_obj.get<model::page<model::track>>();
    Page<Track> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, Playlist>) {
    auto p = j_obj.get<model::page<model::playlist>>();
    Page<Playlist> page(p);
    return page;
  }

  if constexpr (std::is_same_v<T, PlaylistTrack>) {
    auto p = j_obj.get<model::page<model::playlisttrack>>();
    Page<PlaylistTrack> page(p);
    return page;
  }
  return nullptr;
}

template <typename T>
Page<T>::Page(model::page<model::track> t_page)
    : href_(std::move(t_page.href)),
      limit_(t_page.limit),
      next_(std::move(t_page.next)),
      offset_(t_page.offset),
      previous_(std::move(t_page.previous)),
      total_(t_page.total) {
  items_.reserve(t_page.items.size());
  for (const auto &item : t_page.items) {
    Track track_(item);
    items_.push_back(std::move(track_));
  }
}

template <typename T>
Page<T>::Page(model::page<model::savedtrack> t_page)
    : href_(std::move(t_page.href)),
      limit_(t_page.limit),
      next_(std::move(t_page.next)),
      offset_(t_page.offset),
      previous_(std::move(t_page.previous)),
      total_(t_page.total) {
  items_.reserve(t_page.items.size());
  for (const auto &item : t_page.items) {
    Track track_(item.track_);
    items_.push_back(std::move(track_));
  }
}

template <typename T>
Page<T>::Page(model::page<model::album> t_page)
    : href_(std::move(t_page.href)),
      limit_(t_page.limit),
      next_(std::move(t_page.next)),
      offset_(t_page.offset),
      previous_(std::move(t_page.previous)),
      total_(t_page.total) {
  items_.reserve(t_page.items.size());
  for (const auto &item : t_page.items) {
    Album album_(item);
    items_.push_back(std::move(album_));
  }
}

template <typename T>
Page<T>::Page(model::page<model::playlisttrack> t_page)
    : href_(std::move(t_page.href)),
      limit_(t_page.limit),
      next_(std::move(t_page.next)),
      offset_(t_page.offset),
      previous_(std::move(t_page.previous)),
      total_(t_page.total) {
  items_.reserve(t_page.items.size());
  for (const auto &item : t_page.items) {
    Track track_(item.track_);
    items_.push_back(std::move(track_));
  }
}

template <typename T>
Page<T>::Page(model::page<model::playlist> t_page)
    : href_(std::move(t_page.href)),
      limit_(t_page.limit),
      next_(std::move(t_page.next)),
      offset_(t_page.offset),
      previous_(std::move(t_page.previous)),
      total_(t_page.total) {
  items_.reserve(t_page.items.size());
  for (const auto &item : t_page.items) {
    Playlist pl_(item);
    items_.push_back(std::move(pl_));
  }
}

template <typename T>
Page<T>::Page(model::page<model::artist> t_page)
    : href_(std::move(t_page.href)),
      limit_(t_page.limit),
      next_(std::move(t_page.next)),
      offset_(t_page.offset),
      previous_(std::move(t_page.previous)),
      total_(t_page.total) {
  items_.reserve(t_page.items.size());
  for (const auto &item : t_page.items) {
    Artist art_(item);
    items_.push_back(std::move(art_));
  }
}

}  // namespace v1
}  // namespace spotify
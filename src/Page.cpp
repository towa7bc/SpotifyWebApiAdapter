//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Page.hpp"

#include <type_traits>

#include "Album.hpp"
#include "Artist.hpp"
#include "Playlist.hpp"
#include "PlaylistTrack.hpp"
#include "detail/BaseModel.hpp"
#include "detail/HttpHelper.hpp"
#include "model/modeldata.hpp"

namespace spotify::inline v1 {

template <typename T>
bool Page<T>::isHasNextPage() const {
  return !_next.empty();
}

template <typename T>
void Page<T>::setHasNextPage(bool hasNextPage) {
  HasNextPage = hasNextPage;
}

template <typename T>
bool Page<T>::isHasPreviousPage() const {
  return !_previous.empty();
}

template <typename T>
void Page<T>::setHasPreviousPage(bool hasPreviousPage) {
  HasPreviousPage = hasPreviousPage;
}

template <typename T>
Page<T> Page<T>::get_next_page() {
  if (!isHasNextPage()) {
    throw PageNotFoundException();
  }
  auto local_future =
      stlab::async(stlab::default_executor, detail::HttpHelper::get1, _next);
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
Page<T> Page<T>::get_previous_page() {
  if (!isHasPreviousPage()) {
    throw PageNotFoundException();
  }
  auto local_future = stlab::async(stlab::default_executor,
                                   detail::HttpHelper::get1, _previous);
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
Page<T>::Page(const model::page<model::track> &t_page) {
  _href = t_page.href;
  _limit = t_page.limit;
  _offset = t_page.offset;
  _total = t_page.total;
  _previous = t_page.previous;
  _next = t_page.next;
  _items.reserve(t_page.items.capacity());
  for (const auto &item : t_page.items) {
    Track track_(item);
    _items.push_back(std::move(track_));
  }
}

template <typename T>
Page<T>::Page(const model::page<model::album> &t_page) {
  _href = t_page.href;
  _limit = t_page.limit;
  _offset = t_page.offset;
  _total = t_page.total;
  _previous = t_page.previous;
  _next = t_page.next;
  _items.reserve(t_page.items.capacity());
  for (const auto &item : t_page.items) {
    Album album_(item);
    _items.push_back(std::move(album_));
  }
}

template <typename T>
Page<T>::Page(const model::page<model::playlisttrack> &t_page) {
  _href = t_page.href;
  _limit = t_page.limit;
  _offset = t_page.offset;
  _total = t_page.total;
  _previous = t_page.previous;
  _next = t_page.next;
  _items.reserve(t_page.items.capacity());
  for (const auto &item : t_page.items) {
    PlaylistTrack plt_(item);
    _items.push_back(std::move(plt_));
  }
}

template <typename T>
Page<T>::Page(const model::page<model::playlist> &t_page) {
  _href = t_page.href;
  _limit = t_page.limit;
  _offset = t_page.offset;
  _total = t_page.total;
  _previous = t_page.previous;
  _next = t_page.next;
  _items.reserve(t_page.items.capacity());
  for (const auto &item : t_page.items) {
    Playlist plt_(item);
    _items.push_back(std::move(plt_));
  }
}

template <typename T>
Page<T>::Page(const model::page<model::artist> &t_page) {
  _href = t_page.href;
  _limit = t_page.limit;
  _offset = t_page.offset;
  _total = t_page.total;
  _previous = t_page.previous;
  _next = t_page.next;
  _items.reserve(t_page.items.capacity());
  for (const auto &item : t_page.items) {
    Artist plt_(item);
    _items.push_back(std::move(plt_));
  }
}

template <typename T>
Page<T>::Page(const model::page<model::savedtrack> &t_page) {
  _href = t_page.href;
  _limit = t_page.limit;
  _offset = t_page.offset;
  _total = t_page.total;
  _previous = t_page.previous;
  _next = t_page.next;
  _items.reserve(t_page.items.capacity());
  for (const auto &item : t_page.items) {
    Track plt_(item);
    _items.push_back(std::move(plt_));
  }
}

}  // namespace spotify::inline v1

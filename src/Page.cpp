//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Page.hpp"
#include "Album.hpp"
#include "Artist.hpp"
#include "Playlist.hpp"
#include "PlaylistTrack.hpp"
#include "detail/BaseModel.hpp"
#include "detail/HttpHelper.hpp"
#include "model/modeldata.hpp"
#include <type_traits>

namespace spotify {

inline namespace v1 {

template<typename T>
bool spotify::Page<T>::isHasNextPage() const {
    return !_next.empty();
}

template<typename T>
void spotify::Page<T>::setHasNextPage(bool hasNextPage) {
    HasNextPage = hasNextPage;
}

template<typename T>
bool spotify::Page<T>::isHasPreviousPage() const {
    return !_previous.empty();
}

template<typename T>
void spotify::Page<T>::setHasPreviousPage(bool hasPreviousPage) {
    HasPreviousPage = hasPreviousPage;
}

template<typename T>
spotify::Page<T> spotify::Page<T>::get_next_page() {
    if (!isHasNextPage()) {
        throw PageNotFoundException();
    }
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1, _next);
    json_t j_obj = json_t::parse(stlab::blocking_get(local_future));

    if constexpr (std::is_same_v<T, spotify::Album>) {
        Page<spotify::Album> page;
        auto p = j_obj.get<spotify::model::page<spotify::model::album>>();
        page._next = p.next;
        page._previous = p.previous;
        page._href = p.href;
        page._total = p.total;
        page._offset = p.offset;
        page._limit = p.limit;
        for (spotify::model::album &item : p.items) {
            spotify::Album album_(item);
            page._items.push_back(album_);
        }
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Artist>) {
        Page<spotify::Artist> page;
        auto p = j_obj.get<spotify::model::page<spotify::model::artist>>();
        page._next = p.next;
        page._previous = p.previous;
        page._href = p.href;
        page._total = p.total;
        page._offset = p.offset;
        page._limit = p.limit;
        for (const spotify::model::artist &item : p.items) {
            spotify::Artist artist_(item);
            page._items.push_back(artist_);
        }
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Track>) {
        Page<spotify::Track> page;
        auto p = j_obj.get<spotify::model::page<spotify::model::track>>();
        page._next = p.next;
        page._previous = p.previous;
        page._href = p.href;
        page._total = p.total;
        page._offset = p.offset;
        page._limit = p.limit;
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Playlist>) {
        Page<spotify::Playlist> page;
        auto p = j_obj.get<spotify::model::page<spotify::model::playlist>>();
        page._next = p.next;
        page._previous = p.previous;
        page._href = p.href;
        page._total = p.total;
        page._offset = p.offset;
        page._limit = p.limit;
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::PlaylistTrack>) {
        Page<spotify::PlaylistTrack> page;
        auto p = j_obj.get<spotify::model::page<spotify::model::playlisttrack>>();
        page._next = p.next;
        page._previous = p.previous;
        page._href = p.href;
        page._total = p.total;
        page._offset = p.offset;
        page._limit = p.limit;
        return page;
    }
    return nullptr;
}

template<typename T>
spotify::Page<T>::Page(const model::page<spotify::model::track> &t_page) {
    _href = t_page.href;
    _limit = t_page.limit;
    _offset = t_page.offset;
    _total = t_page.total;
    _previous = t_page.previous;
    _next = t_page.next;
    for (const auto &item : t_page.items) {
        spotify::Track track_(item);
        _items.push_back(track_);
    }
}

template<typename T>
spotify::Page<T>::Page(const model::page<spotify::model::album> &t_page) {
    _href = t_page.href;
    _limit = t_page.limit;
    _offset = t_page.offset;
    _total = t_page.total;
    _previous = t_page.previous;
    _next = t_page.next;
    for (const auto &item : t_page.items) {
        spotify::Album album_(item);
        _items.push_back(album_);
    }
}

template<typename T>
Page<T>::Page(const model::page<spotify::model::playlisttrack> &t_page) {
    _href = t_page.href;
    _limit = t_page.limit;
    _offset = t_page.offset;
    _total = t_page.total;
    _previous = t_page.previous;
    _next = t_page.next;
    for (const auto &item : t_page.items) {
        spotify::PlaylistTrack plt_(item);
        _items.push_back(plt_);
    }
}

}// namespace v1
}// namespace spotify
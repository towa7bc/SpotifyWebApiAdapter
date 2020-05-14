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
        auto p = j_obj.get<spotify::model::page<spotify::model::album>>();
        Page<spotify::Album> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Artist>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::artist>>();
        Page<spotify::Artist> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Track>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::track>>();
        Page<spotify::Track> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Playlist>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::playlist>>();
        Page<spotify::Playlist> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::PlaylistTrack>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::playlisttrack>>();
        Page<spotify::PlaylistTrack> page(p);
        return page;
    }
    return nullptr;
}

template<typename T>
spotify::Page<T> spotify::Page<T>::get_previous_page() {
    if (!isHasPreviousPage()) {
        throw PageNotFoundException();
    }
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1, _previous);
    json_t j_obj = json_t::parse(stlab::blocking_get(local_future));

    if constexpr (std::is_same_v<T, spotify::Album>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::album>>();
        Page<spotify::Album> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Artist>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::artist>>();
        Page<spotify::Artist> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Track>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::track>>();
        Page<spotify::Track> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::Playlist>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::playlist>>();
        Page<spotify::Playlist> page(p);
        return page;
    }

    if constexpr (std::is_same_v<T, spotify::PlaylistTrack>) {
        auto p = j_obj.get<spotify::model::page<spotify::model::playlisttrack>>();
        Page<spotify::PlaylistTrack> page(p);
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
    _items.reserve(t_page.items.capacity());
    for (const auto &item : t_page.items) {
        spotify::Track track_(item);
        _items.push_back(std::move(track_));
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
    _items.reserve(t_page.items.capacity());
    for (const auto &item : t_page.items) {
        spotify::Album album_(item);
        _items.push_back(std::move(album_));
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
    _items.reserve(t_page.items.capacity());
    for (const auto &item : t_page.items) {
        spotify::PlaylistTrack plt_(item);
        _items.push_back(std::move(plt_));
    }
}

template<typename T>
Page<T>::Page(const model::page<spotify::model::playlist> &t_page) {
    _href = t_page.href;
    _limit = t_page.limit;
    _offset = t_page.offset;
    _total = t_page.total;
    _previous = t_page.previous;
    _next = t_page.next;
    _items.reserve(t_page.items.capacity());
    for (const auto &item : t_page.items) {
        spotify::Playlist plt_(item);
        _items.push_back(std::move(plt_));
    }
}

template<typename T>
Page<T>::Page(const spotify::model::page<spotify::model::artist> &t_page) {
    _href = t_page.href;
    _limit = t_page.limit;
    _offset = t_page.offset;
    _total = t_page.total;
    _previous = t_page.previous;
    _next = t_page.next;
    _items.reserve(t_page.items.capacity());
    for (const auto &item : t_page.items) {
        spotify::Artist plt_(item);
        _items.push_back(std::move(plt_));
    }
}

template<typename T>
Page<T>::Page(const model::page<spotify::model::savedtrack> &t_page) {
    _href = t_page.href;
    _limit = t_page.limit;
    _offset = t_page.offset;
    _total = t_page.total;
    _previous = t_page.previous;
    _next = t_page.next;
    _items.reserve(t_page.items.capacity());
    for (const auto &item : t_page.items) {
        spotify::Track plt_(item);
        _items.push_back(std::move(plt_));
    }
}

}// namespace v1
}// namespace spotify
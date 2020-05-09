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
            spotify::Album album_{};
            item.album_type = str_toupper(item.album_type);
            if (item.album_type == "ALBUM") {
                album_._album_type = spotify::Album::AlbumType::Album;
            } else if (item.album_type == "SINGLE") {
                album_._album_type = spotify::Album::AlbumType::Single;
            } else if (item.album_type == "COMPILATION") {
                album_._album_type = spotify::Album::AlbumType::Compilation;
            }
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
            spotify::Artist artist_{};
            artist_._href = item.href;
            artist_._id = item.id;
            artist_._uri = item.uri;
            artist_._type = item.type;
            const int base{10};
            artist_._popularity = std::stoi(item.popularity, nullptr, base);
            artist_._name = item.name;
            artist_._genres = item.genres;
            artist_._external_url = item.external_urls.at(0);
            for (const spotify::model::image &image : item.images) {
                Image elem;
                elem.width = image.width;
                elem._height = image.height;
                elem._url = image.url;
                artist_._images.push_back(elem);
            }
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

}// namespace v1
}// namespace spotify
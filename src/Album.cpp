//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Album.hpp"
#include "Browse.hpp"

namespace spotify {

inline namespace v1 {

spotify::Page<spotify::Album> spotify::v1::Album::get_artist_albums(std::string_view artist_id) {
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/artists/" + std::string(artist_id) + "/albums")
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::page<spotify::model::album>>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Page<spotify::Album> album_page(local_obj);
    return album_page;
}

spotify::Page<spotify::Album> spotify::Album::search(std::string &albumName,
                                                     std::string &artistName,
                                                     std::string &year,
                                                     std::string &genre,
                                                     std::string &upc,
                                                     std::string &isrc,
                                                     int limit,
                                                     int offset) {
    replace_all(albumName, " ", "%20");
    std::string queryString = "https://api.spotify.com/v1/search?q=album:" + albumName;
    if (!artistName.empty()) {
        replace_all(artistName, " ", "%20");
        queryString += "%20:artist:" + artistName;
    }
    if (!year.empty()) {
        replace_all(year, " ", "%20");
        queryString += "%20:year:" + year;
    }
    if (!genre.empty()) {
        replace_all(genre, " ", "%20");
        queryString += "%20:genre:" + genre;
    }
    if (!upc.empty()) {
        replace_all(upc, " ", "%20");
        queryString += "%20:upc:" + upc;
    }
    if (!isrc.empty()) {
        replace_all(isrc, " ", "%20");
        queryString += "%20:isrc:" + isrc;
    }
    queryString += "&limit=" + std::to_string(limit);
    queryString += "&offset=" + std::to_string(offset);
    queryString += "&type=album";
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1, queryString)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::album_search_result>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Page<spotify::Album> page;
    page._next = local_obj.albums.next;
    page._previous = local_obj.albums.previous;
    page._href = local_obj.albums.href;
    page._total = local_obj.albums.total;
    page._offset = local_obj.albums.offset;
    page._limit = local_obj.albums.limit;
    for (const spotify::model::album &item : local_obj.albums.items) {
        spotify::Album album_(item);
        page._items.push_back(album_);
    }
    return page;
}

spotify::Album::Album(const spotify::model::album &t_album) {
    if (str_toupper(t_album.album_type) == "ALBUM") {
        this->_album_type = spotify::Album::AlbumType::Album;
    } else if (str_toupper(t_album.album_type) == "SINGLE") {
        this->_album_type = spotify::Album::AlbumType::Single;
    } else if (str_toupper(t_album.album_type) == "COMPILATION") {
        this->_album_type = spotify::Album::AlbumType::Compilation;
    }
    _type = t_album.type;
    _href = t_album.href;
    for (const spotify::model::image &image : t_album.images) {
        Image elem(image);
        this->_images.push_back(elem);
    }
    _external_url = t_album.external_urls.at(0);
    _external_id = t_album.external_ids.at(0);
    _genres = t_album.genres;
    _name = t_album.name;
    const int base{10};
    _popularity = std::stoi(t_album.popularity, nullptr, base);
    _uri = t_album.uri;
    _id = t_album.id;
    _availableMarkets = t_album.available_markets;
    _release_date = boost::posix_time::time_from_string(t_album.release_date);
    _release_date_precision = t_album.release_date_precision;
    _ptracks = std::make_shared<spotify::Page<spotify::Track>>(t_album.tracks);
}

spotify::Album::Album(spotify::model::album &&t_album) noexcept {
    if (str_toupper(std::move(t_album.album_type)) == "ALBUM") {
        this->_album_type = spotify::Album::AlbumType::Album;
    } else if (str_toupper(t_album.album_type) == "SINGLE") {
        this->_album_type = spotify::Album::AlbumType::Single;
    } else if (str_toupper(t_album.album_type) == "COMPILATION") {
        this->_album_type = spotify::Album::AlbumType::Compilation;
        _type = t_album.type;
        _href = t_album.href;
        for (const spotify::model::image &image : t_album.images) {
            Image elem(image);
            this->_images.push_back(elem);
        }
        _external_url = t_album.external_urls.at(0);
        _external_id = t_album.external_ids.at(0);
        _genres = t_album.genres;
        _name = t_album.name;
        const int base{10};
        _popularity = std::stoi(t_album.popularity, nullptr, base);
        _uri = t_album.uri;
        _id = t_album.id;
        _availableMarkets = t_album.available_markets;
        _release_date = boost::posix_time::time_from_string(t_album.release_date);
        _release_date_precision = t_album.release_date_precision;
        _ptracks = std::make_shared<spotify::Page<spotify::Track>>(t_album.tracks);
    }
}

spotify::Album spotify::Album::get_album(std::string_view album_id) {
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/albums/" + std::string(album_id))
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::album>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Album album_(local_obj);
    return album_;
}

spotify::Page<spotify::Track> spotify::v1::Album::get_album_tracks(std::string_view album_id, int limit, int offset) {
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/albums/" + std::string(album_id)
                                             + "/tracks?limit=" + std::to_string(limit) + "&offset=" + std::to_string(offset))
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::page<spotify::model::track>>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Page<spotify::Track> album_page(local_obj);
    return album_page;
}

std::vector<spotify::Album> spotify::Album::get_albums(const std::vector<std::string> &album_ids) {
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/albums/?ids=" + create_comma_separated_List(album_ids))
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::album_array>(); });
    auto local_obj = stlab::blocking_get(local_future);
    std::vector<spotify::Album> album_array;
    for (const auto &item : local_obj.albums) {
        Album a(item);
        album_array.push_back(a);
    }
    return album_array;
}

spotify::Page<spotify::Track> spotify::v1::Album::get_album_tracks(int limit, int offset) const {
    return get_album_tracks(this->_id, limit, offset);
}

spotify::Page<spotify::Album> spotify::v1::Album::get_new_releases(const spotify::AuthentificationToken &token,
                                                                   std::string_view country,
                                                                   int limit,
                                                                   int offset) {
    return spotify::Browse::get_new_releases(token, country, limit, offset);
}

}// namespace v1
}// namespace spotify

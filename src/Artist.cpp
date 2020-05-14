//
// Created by Michael Wittmann on 07/05/2020.
//

#include "Artist.hpp"

namespace spotify {

inline namespace v1 {

spotify::Artist spotify::Artist::get_artist(const std::string &artist_id) {
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/artists/" + artist_id)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::artist>(); });
    auto local_obj = stlab::blocking_get(local_future);
    Artist artist_(local_obj);
    return artist_;
}

std::vector<spotify::Artist> spotify::Artist::get_artists(const std::vector<std::string> &artist_ids) {
    std::vector<spotify::Artist> artists_list;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/artists/?ids=" + create_comma_separated_List(artist_ids))
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::artist_array>(); });
    auto local_obj = stlab::blocking_get(local_future);
    for (const auto &item : local_obj.artists) {
        Artist artist_(item);
        artists_list.push_back(artist_);
    }
    return artists_list;
}

spotify::Page<spotify::Artist> spotify::Artist::search(std::string &artistName,
                                                       std::string &year,
                                                       std::string &genre,
                                                       std::string &upc,
                                                       std::string &isrc,
                                                       int limit,
                                                       int offset) {
    artistName = replace_all(artistName, " ", "%20");
    std::string queryString = "https://api.spotify.com/v1/search?q=artist:" + artistName;
    if (!year.empty()) {
        year = replace_all(year, " ", "%20");
        queryString += "%20:year:" + year;
    }
    if (!genre.empty()) {
        genre = replace_all(genre, " ", "%20");
        queryString += "%20:genre:" + genre;
    }
    if (!upc.empty()) {
        upc = replace_all(upc, " ", "%20");
        queryString += "%20:upc:" + upc;
    }
    if (!isrc.empty()) {
        isrc = replace_all(isrc, " ", "%20");
        queryString += "%20:isrc:" + isrc;
    }
    queryString += "&limit=" + std::to_string(limit);
    queryString += "&offset=" + std::to_string(offset);
    queryString += "&type=artist";
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1, queryString)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::artist_search_result>(); });
    auto local_obj = stlab::blocking_get(local_future);
    spotify::Page<spotify::Artist> page;
    page._next = local_obj.artists.next;
    page._previous = local_obj.artists.previous;
    page._href = local_obj.artists.href;
    page._total = local_obj.artists.total;
    page._offset = local_obj.artists.offset;
    page._limit = local_obj.artists.limit;
    for (const spotify::model::artist &item : local_obj.artists.items) {
        spotify::Artist artist_(item);
        page._items.push_back(artist_);
    }
    return page;
}

spotify::Page<spotify::Album> spotify::Artist::get_albums() {
    auto local_future = stlab::async(stlab::default_executor, spotify::Album::get_artist_albums, this->_id);
    return stlab::blocking_get(local_future);
}

std::vector<spotify::Track> spotify::Artist::get_top_tracks(const std::string &artist_id, const std::string &country_code) {
    std::vector<spotify::Track> tracks_list;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/artists/" + artist_id + "/top-tracks?country=" + country_code)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::track_array>(); });
    auto local_obj = stlab::blocking_get(local_future);
    for (const auto &item : local_obj.tracks) {
        spotify::Track track_;
        track_.track_number = item.track_number;

        tracks_list.push_back(track_);
    }
    return tracks_list;
}

std::vector<spotify::Track> spotify::Artist::get_top_tracks(const std::string &country_code) const {
    return get_top_tracks(this->_id, country_code);
}

std::vector<spotify::Artist> spotify::Artist::get_related_artists(const std::string &artist_id, const std::string &country_code) {
    std::vector<spotify::Artist> artists_list;
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/artists/" + artist_id + "/top-tracks?country=" + country_code)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::artist_array>(); });
    auto local_obj = stlab::blocking_get(local_future);
    for (const auto &item : local_obj.artists) {
        Artist artist_(item);
        artists_list.push_back(artist_);
    }
    return artists_list;
}

std::vector<spotify::Artist> spotify::Artist::get_related_artists(const std::string &country_code) const {
    return get_related_artists(this->_id, country_code);
}

spotify::Artist::Artist(const spotify::model::artist &t_artist) : _genres(t_artist.genres),
                                                                  _external_url(t_artist.external_urls.at(0)),
                                                                  _href(t_artist.href),
                                                                  _id(t_artist.id),
                                                                  _name(t_artist.name),
                                                                  _type(t_artist.type),
                                                                  _uri(t_artist.uri) {
    this->_images.reserve(t_artist.images.capacity());
    for (const spotify::model::image &image : t_artist.images) {
        Image elem(image);
        this->_images.push_back(std::move(elem));
    }
    const int base{10};
    this->_popularity = std::stoi(t_artist.popularity, nullptr, base);
}

}// namespace v1
}// namespace spotify
//
// Created by Michael Wittmann on 07/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_ARTIST_HPP
#define SPOTIFYWEBAPIADAPTER_ARTIST_HPP

#include "Album.hpp"
#include "Image.hpp"
#include "Page.hpp"
#include "Track.hpp"
#include "detail/BaseModel.hpp"
#include "detail/HttpHelper.hpp"
#include <algorithm>
#include <vector>

namespace spotify::inline v1 {

class Track;
class Album;
template<typename>
class Page;

class Artist : public BaseModel {
    using json_t = nlohmann::json;

public:
    explicit Artist(const model::artist &);
    explicit Artist(model::artist &&t_artist) noexcept;
    Artist() = default;
    Artist(const Artist &) = default;
    ~Artist() override = default;
    Artist &operator=(const Artist &) = default;
    Artist &operator=(Artist &&) noexcept = default;
    Artist(Artist &&) noexcept = default;
    std::vector<std::string> _genres;
    std::string _external_url;
    std::string _href;
    std::string _id;
    std::vector<Image> _images;
    std::string _name;
    int _popularity{};
    std::string _type;
    std::string _uri;
    static Artist get_artist(const std::string &artist_id);
    static std::vector<Artist> get_artists(const std::vector<std::string> &artist_ids);
    static Page<Artist> search(std::string &artistName,
                               std::string &year,
                               std::string &genre,
                               std::string &upc,
                               std::string &isrc,
                               int limit = 20,
                               int offset = 0);
    Page<Album> get_albums();
    static std::vector<Track> get_top_tracks(const std::string &artist_id, const std::string &country_code = "US");
    [[nodiscard]] std::vector<Track> get_top_tracks(const std::string &country_code = "US") const;
    static std::vector<Artist> get_related_artists(const std::string &artist_id, const std::string &country_code = "US");
    [[nodiscard]] std::vector<Artist> get_related_artists(const std::string &country_code = "US") const;
};

}// namespace v1

#endif

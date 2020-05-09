//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_TRACK_HPP
#define SPOTIFYWEBAPIADAPTER_TRACK_HPP

#include "Album.hpp"
#include "Artist.hpp"
#include "detail/BaseModel.hpp"
#include "detail/HttpHelper.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace spotify {

inline namespace v1 {

class Album;
class Artist;

class Track : public BaseModel {
    using json_t = nlohmann::json;

public:
    Track() = default;
    Track(const Track &) = default;
    ~Track() = default;
    Track &operator=(const Track &) = default;
    std::vector<spotify::Artist> artists;
    std::vector<std::string> available_markets;
    std::vector<std::string> external_id;
    std::vector<std::string> external_url;
    std::vector<std::string> genres;
    std::string href;
    std::string id;
    std::vector<spotify::Image> images;
    std::string name;
    std::string popularity;
    std::string preview_url;
    spotify::model::page<spotify::Track> tracks;
    std::string type;
    std::string uri;
    int disc_number;
    int duration;
    bool explicit_;
    int track_number;
    std::shared_ptr<const spotify::Album> album;
};

}// namespace v1
}// namespace spotify

#endif

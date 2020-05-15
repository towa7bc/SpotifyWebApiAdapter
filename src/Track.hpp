//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_TRACK_HPP
#define SPOTIFYWEBAPIADAPTER_TRACK_HPP

#include "Album.hpp"
#include "Artist.hpp"
#include "detail/BaseModel.hpp"
#include "detail/Core.hpp"
#include "detail/HttpHelper.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace spotify::inline v1 {

class Album;
class Artist;

class Track : public BaseModel {
    using json_t = nlohmann::json;

public:
    explicit Track(const model::track &);
    explicit Track(model::track &&) noexcept;
    explicit Track(const model::savedtrack &);
    explicit Track(model::savedtrack &&t_track) noexcept;
    Track() = default;
    Track(const Track &) = default;
    ~Track() override = default;
    Track &operator=(const Track &) = default;
    Track &operator=(Track &&) noexcept = default;
    Track(Track &&) noexcept = default;
    std::vector<Artist> artists;
    std::vector<std::string> available_markets;
    std::vector<std::string> external_id;
    std::vector<std::string> external_url;
    std::vector<std::string> genres;
    std::string href;
    std::string id;
    std::string name;
    std::string popularity;
    std::string preview_url;
    std::string type;
    std::string uri;
    int disc_number{};
    int duration{};
    bool explicit_{};
    int track_number{};
    Ref<Album> album;
};

}// namespace v1

#endif

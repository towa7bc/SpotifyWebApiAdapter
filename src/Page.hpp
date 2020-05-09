//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PAGE_HPP
#define SPOTIFYWEBAPIADAPTER_PAGE_HPP

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

template<typename>
class Page;

template<typename T>
class Page : public BaseModel {
    using json_t = nlohmann::json;

public:
    Page() = default;
    Page(const Page &) = default;
    ~Page() = default;
    Page &operator=(const Page &) = default;
    std::string _href;
    std::vector<T> _items;
    int _limit{0};
    std::string _next;
    int _offset{0};
    std::string _previous;
    int _total{0};
    [[nodiscard]] bool isHasNextPage() const;
    void setHasNextPage(bool hasNextPage);
    [[nodiscard]] bool isHasPreviousPage() const;
    void setHasPreviousPage(bool hasPreviousPage);
    Page<T> get_next_page();

private:
    bool HasPreviousPage{false};
    bool HasNextPage{false};
};

}// namespace v1
}// namespace spotify

#endif

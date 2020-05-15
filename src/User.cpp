//
// Created by Michael Wittmann on 07/05/2020.
//

#include "User.hpp"
#include "Page.hpp"
#include "detail/HttpHelper.hpp"

namespace spotify::inline v1 {

User::User(const model::user &t_user) : _country(t_user.country),
                                        _displayName(t_user.display_name),
                                        _external_url(t_user.external_urls.at(0)),
                                        _href(t_user.href),
                                        _id(t_user.id),
                                        _product(t_user.product),
                                        _type(t_user.type),
                                        _uri(t_user.uri) {
    _images.reserve(t_user.images.capacity());
    for (const auto &imag : t_user.images) {
        Image image(imag);
        _images.push_back(std::move(image));
    }
}

User::User(model::user &&t_user) noexcept : _country(std::move(t_user.country)),
                                            _displayName(std::move(t_user.display_name)),
                                            _external_url(std::move(t_user.external_urls.at(0))),
                                            _href(std::move(t_user.href)),
                                            _id(std::move(t_user.id)),
                                            _product(std::move(t_user.product)),
                                            _type(std::move(t_user.type)),
                                            _uri(std::move(t_user.uri)) {
    _images.reserve(t_user.images.capacity());
    for (auto &imag : t_user.images) {
        Image image(std::move(imag));
        _images.push_back(std::move(image));
    }
}

User User::get_user(std::string_view user_id) {
    auto local_future = stlab::async(stlab::default_executor, detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/users/" + std::string(user_id))
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<model::user>(); });
    auto local_obj = stlab::blocking_get(local_future);
    User user(local_obj);
    return user;
}

User User::get_current_user_profile(const AuthenticationToken &token) {
    bool include_bearer{true};
    auto local_future = stlab::async(stlab::default_executor, detail::HttpHelper::get2,
                                     "https://api.spotify.com/v1/me", token, include_bearer)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<model::user>(); });
    auto local_obj = stlab::blocking_get(local_future);
    User user(local_obj);
    return user;
}

Page<Playlist> User::get_playlists(const AuthenticationToken &token) const {
    return Playlist::get_users_playlists(_id, token);
}

Page<Track> User::get_user_saved_tracks(const AuthenticationToken &token, int limit, int offset) {
    bool include_bearer{true};
    auto local_future = stlab::async(stlab::default_executor, detail::HttpHelper::get2,
                                     "https://api.spotify.com/v1/me/tracks?limit=" + std::to_string(limit) + "&offset=" + std::to_string(offset),
                                     token, include_bearer)
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<model::page<model::savedtrack>>(); });
    auto local_obj = stlab::blocking_get(local_future);
    Page<Track> track(local_obj);
    return track;
}

Page<Track> User::get_saved_tracks(const AuthenticationToken &token, int limit, int offset) {
    return get_user_saved_tracks(token, limit, offset);
}

void User::save_tracks(const std::vector<std::string> &ids, const AuthenticationToken &token) {
    auto uri = create_comma_separated_List(ids);
    bool include_bearer{true};
    model::playlistdata pd;
    auto local_future = stlab::async(stlab::default_executor, detail::HttpHelper::put2,
                                     "https://api.spotify.com/v1/me/tracks?ids=" + uri,
                                     token, pd, include_bearer);
    auto local_obj = stlab::blocking_get(local_future);
}

void User::delete_tracks(const std::vector<std::string> &ids, const AuthenticationToken &token) {
    auto uri = create_comma_separated_List(ids);
    bool include_bearer{true};
    auto local_future = stlab::async(stlab::default_executor, detail::HttpHelper::delete_,
                                     "https://api.spotify.com/v1/me/tracks?ids=" + uri,
                                     token, include_bearer);
    auto local_obj = stlab::blocking_get(local_future);
}

bool User::are_saved(const std::vector<std::string> &ids, const AuthenticationToken &token) {
    auto uri = create_comma_separated_List(ids);
    bool include_bearer{true};
    auto local_future = stlab::async(stlab::default_executor, detail::HttpHelper::get2,
                                     "https://api.spotify.com/v1/me/tracks/contains?ids=" + uri,
                                     token, include_bearer)
                        | ([](std::string_view s) { return json_t::parse(s); });
    auto local_obj = stlab::blocking_get(local_future);
    auto bool_string = local_obj.dump();
    bool_string = str_toupper(bool_string);
    return bool_string.find("TRUE") != std::string::npos;
}

bool User::is_saved(std::string_view id, const AuthenticationToken &token) {
    std::vector<std::string> ids{std::string(id)};
    return are_saved(ids, token);
}

}// namespace v1

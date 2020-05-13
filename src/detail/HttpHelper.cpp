//
// Created by Michael Wittmann on 03/05/2020.
//

#include "HttpHelper.hpp"

namespace spotify {

inline namespace v1 {

namespace detail {

/* static */ auto spotify::detail::HttpHelper::get1(std::string_view url) -> std::string {
    _manager.perform_get_request(url);
    return _manager.get_reply();
}

/* static */ auto spotify::detail::HttpHelper::get2(
        std::string_view url, const spotify::AuthentificationToken &token, bool include_bearer) -> std::string {
    _manager.perform_get_request(url, token, include_bearer);
    return _manager.get_reply();
}

/* static */ auto spotify::detail::HttpHelper::post1(
        std::string_view url, const std::map<std::string, std::string> &postData) -> std::string {
    _manager.perform_post_request(url, postData);
    return _manager.get_reply();
}

/* static */ auto spotify::detail::HttpHelper::post2(
        std::string_view url, const spotify::AuthentificationToken &token,
        const std::map<std::string, std::string> &postData, bool include_bearer) -> std::string {
    _manager.perform_post_request(url, token, postData, include_bearer);
    return _manager.get_reply();
}

/* static */ auto spotify::detail::HttpHelper::post3(
        std::string_view url, const spotify::AuthentificationToken &token,
        const spotify::model::playlistdata &pD, bool include_bearer) -> std::string {
    nlohmann::json j = pD;
    _manager.perform_post_request(url, token, j.dump(), include_bearer);
    return _manager.get_reply();
}

/* static */ auto spotify::detail::HttpHelper::put1(
        std::string_view url, const spotify::AuthentificationToken &token,
        const std::map<std::string, std::string> &postData, bool include_bearer) -> std::string {
    _manager.perform_put_request(url, token, postData, include_bearer);
    return _manager.get_reply();
}

/* static */ auto spotify::detail::HttpHelper::put2(
        std::string_view url, const spotify::AuthentificationToken &token,
        const spotify::model::playlistdata &pD, bool include_bearer) -> std::string {
    nlohmann::json j = pD;
    _manager.perform_put_request(url, token, j.dump(), include_bearer);
    return _manager.get_reply();
}

/* static */ auto spotify::detail::HttpHelper::delete_(
        std::string_view url, const spotify::AuthentificationToken &token, bool include_bearer) -> std::string {
    _manager.perform_delete_request(url, token, include_bearer);
    return _manager.get_reply();
}

}// namespace detail
}// namespace v1
}// namespace spotify
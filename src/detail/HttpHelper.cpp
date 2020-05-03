//
// Created by Michael Wittmann on 03/05/2020.
//

#include "HttpHelper.hpp"

/* static */ auto spotify::detail::HttpHelper::post(std::string_view url, const std::map<std::string, std::string> &postData) -> std::string {
    _manager.perform_post_request(url, postData);
    return _manager.getReply();
}
//
// Created by Michael Wittmann on 14/05/2020.
//

#include "Followers.hpp"

namespace spotify::inline v1 {

Followers::Followers(const model::followers &t_followers)
    : _total(t_followers.total), _href(t_followers.href) {}

Followers::Followers(model::followers &&t_followers) noexcept
    : _total(t_followers.total), _href(std::move(t_followers.href)) {}

}  // namespace spotify::inline v1
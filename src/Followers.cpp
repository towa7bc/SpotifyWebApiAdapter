//
// Created by Michael Wittmann on 14/05/2020.
//

#include "Followers.hpp"

#include <type_traits>  // for move

#include "model/modeldata.hpp"  // for followers

namespace spotify {
inline namespace v1 {

Followers::Followers(const model::followers &t_followers)
    : total_(t_followers.total), href_(t_followers.href) {}

Followers::Followers(model::followers &&t_followers) noexcept
    : total_(t_followers.total), href_(std::move(t_followers.href)) {}

}  // namespace v1
}  // namespace spotify
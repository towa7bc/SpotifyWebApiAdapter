//
// Created by Michael Wittmann on 14/05/2020.
//

#include "Followers.hpp"

namespace spotify {

inline namespace v1 {

Followers::Followers(const spotify::model::followers &t_followers) : _total(t_followers.total),
                                                                     _href(t_followers.href) {
}

}// namespace v1
}// namespace spotify
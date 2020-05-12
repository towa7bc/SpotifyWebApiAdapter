//
// Created by Michael Wittmann on 07/05/2020.
//

#include "User.hpp"

namespace spotify {

inline namespace v1 {

spotify::User::User(const spotify::model::user &) {
}

spotify::User::User(spotify::model::user &&) noexcept {
}

}// namespace v1
}// namespace spotify
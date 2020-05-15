//
// Created by Michael Wittmann on 15/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_CORE_HPP
#define SPOTIFYWEBAPIADAPTER_CORE_HPP

#include <memory>

namespace spotify::inline v1 {

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename... Args>
constexpr Scope<T> create_scope(Args &&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename... Args>
constexpr Ref<T> create_ref(Args &&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

}// namespace spotify::inline v1

#endif

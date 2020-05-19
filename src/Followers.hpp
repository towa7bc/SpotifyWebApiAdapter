//
// Created by Michael Wittmann on 12/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP
#define SPOTIFYWEBAPIADAPTER_FOLLOWERS_HPP

#include <string>  // for string
namespace spotify::inline v1 {
namespace model {
struct followers;
}
}  // namespace spotify::inline v1

namespace spotify::inline v1 {

struct Followers {
  explicit Followers(const model::followers &);
  explicit Followers(model::followers &&) noexcept;
  Followers() = default;
  Followers(const Followers &) = default;
  ~Followers() = default;
  Followers &operator=(const Followers &) = default;
  Followers &operator=(Followers &&) noexcept = default;
  Followers(Followers &&) noexcept = default;
  int total_{0};
  std::string href_;
};

}  // namespace spotify::inline v1

#endif

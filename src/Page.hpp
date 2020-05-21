//
// Created by Michael Wittmann on 08/05/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_PAGE_HPP
#define SPOTIFYWEBAPIADAPTER_PAGE_HPP

#include <nlohmann/json.hpp>  // for json
#include <string>             // for string
#include <vector>             // for vector

#include "detail/BaseModel.hpp"  // for BaseModel
#include "model/modeldata.hpp"   // for json

namespace spotify {
inline namespace v1 {

template <typename>
class Page;

template <typename T>
class Page : public BaseModel {
  using json_t = nlohmann::json;

 public:
  explicit Page(const model::page<model::track> &);
  explicit Page(const model::page<model::savedtrack> &);
  explicit Page(const model::page<model::album> &);
  explicit Page(const model::page<model::playlisttrack> &);
  explicit Page(const model::page<model::playlist> &);
  explicit Page(const model::page<model::artist> &);
  Page() = default;
  Page(const Page &) = default;
  ~Page() override = default;
  Page &operator=(const Page &) = default;
  Page &operator=(Page &&) noexcept = default;
  Page(Page &&) noexcept = default;
  std::string href_;
  std::vector<T> items_;
  int limit_{0};
  std::string next_;
  int offset_{0};
  std::string previous_;
  int total_{0};
  [[nodiscard]] bool HasNextPage() const;
  void SetHasNextPage(bool hasNextPage);
  [[nodiscard]] bool HasPreviousPage() const;
  void SetHasPreviousPage(bool hasPreviousPage);
  Page<T> GetNextPage();
  Page<T> GetPreviousPage();

 private:
  bool has_previous_page_{false};
  bool has_next_page_{false};
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

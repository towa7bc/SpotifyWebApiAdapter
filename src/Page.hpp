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

namespace spotify::inline v1 {

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
  std::string _href;
  std::vector<T> _items;
  int _limit{0};
  std::string _next;
  int _offset{0};
  std::string _previous;
  int _total{0};
  [[nodiscard]] bool isHasNextPage() const;
  void setHasNextPage(bool hasNextPage);
  [[nodiscard]] bool isHasPreviousPage() const;
  void setHasPreviousPage(bool hasPreviousPage);
  Page<T> get_next_page();
  Page<T> get_previous_page();

 private:
  bool HasPreviousPage{false};
  bool HasNextPage{false};
};

}  // namespace spotify::inline v1

#endif

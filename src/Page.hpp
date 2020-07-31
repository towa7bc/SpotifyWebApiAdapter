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
  explicit Page(model::page<model::track>);
  explicit Page(model::page<model::savedtrack>);
  explicit Page(model::page<model::album>);
  explicit Page(model::page<model::playlisttrack>);
  explicit Page(model::page<model::playlist>);
  explicit Page(model::page<model::artist>);
  Page() = default;
  [[nodiscard]] const std::string &getHref() const { return href_; }
  void setHref(const std::string &href) { href_ = href; }
  const std::vector<T> &getItems() const { return items_; }
  void setItems(const std::vector<T> &items) { items_ = items; }
  [[nodiscard]] int getLimit() const { return limit_; }
  void setLimit(int limit) { limit_ = limit; }
  [[nodiscard]] const std::string &getNext() const { return next_; }
  void setNext(const std::string &next) { next_ = next; }
  [[nodiscard]] int getOffset() const { return offset_; }
  void setOffset(int offset) { offset_ = offset; }
  [[nodiscard]] const std::string &getPrevious() const { return previous_; }
  void setPrevious(const std::string &previous) { previous_ = previous; }
  [[nodiscard]] int getTotal() const { return total_; }
  void setTotal(int total) { total_ = total; }
  [[nodiscard]] bool HasNextPage() const;
  void setHasNextPage(bool hasNextPage);
  [[nodiscard]] bool HasPreviousPage() const;
  void setHasPreviousPage(bool hasPreviousPage);
  Page<T> getNextPage();
  Page<T> getPreviousPage();

 private:
  std::string href_;
  std::vector<T> items_;
  int limit_{0};
  std::string next_;
  int offset_{0};
  std::string previous_;
  int total_{0};
  bool has_previous_page_{false};
  bool has_next_page_{false};
};

}  // namespace spotify::inline v1
}  // namespace spotify

#endif

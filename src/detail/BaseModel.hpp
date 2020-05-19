//
// Created by Michael Wittmann on 30/04/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_BASEMODEL_HPP
#define SPOTIFYWEBAPIADAPTER_BASEMODEL_HPP

#include <exception>    // for exception
#include <string>       // for string
#include <string_view>  // for string_view
#include <vector>       // for vector

namespace spotify::inline v1 {

class BaseModel {
 public:
  BaseModel() = default;
  virtual ~BaseModel() = default;
  BaseModel(const BaseModel &) = default;
  BaseModel(BaseModel &&) noexcept = default;
  BaseModel &operator=(const BaseModel &) = default;
  BaseModel &operator=(BaseModel &&) noexcept = default;
  static auto CreateCommaSeparatedList(const std::vector<std::string> &v)
      -> std::string;
  static std::string ReplaceAll(std::string str, std::string_view from,
                                std::string_view to);
  static std::string StrToUpper(std::string s);
};

class PageNotFoundException : public std::exception {
  [[nodiscard]] const char *what() const noexcept override {
    return "Page not found.";
  }
};

}  // namespace spotify::inline v1

#endif

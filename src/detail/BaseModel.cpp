//
// Created by Michael Wittmann on 03/05/2020.
//

#include "BaseModel.hpp"

#include <_ctype.h>  // for toupper

#include <algorithm>    // for transform
#include <cstddef>      // for size_t
#include <iterator>     // for next
#include <numeric>      // for accumulate
#include <string>       // for basic_string, basic_string<>::iterator, alloc...
#include <type_traits>  // for enable_if<>::type, move

namespace spotify::inline v1 {

/* static */ auto BaseModel::create_comma_separated_List(
    const std::vector<std::string> &v) -> std::string {
  if (v.empty()) {
    return "n/a";
  }
  return std::accumulate(std::next(v.begin()), v.end(), v[0],
                         [](std::string a, std::string b) {
                           return std::move(a) + ',' + std::move(b);
                         });
}

std::string BaseModel::replace_all(std::string str, std::string_view from,
                                   std::string_view to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos +=
        to.length();  // Handles case where 'to' is a substring of 'from'
  }
  return str;
}

std::string BaseModel::str_toupper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return s;
}

}  // namespace spotify::inline v1
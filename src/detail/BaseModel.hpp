//
// Created by Michael Wittmann on 30/04/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_BASEMODEL_HPP
#define SPOTIFYWEBAPIADAPTER_BASEMODEL_HPP

#include <numeric>
#include <string>
#include <vector>

namespace spotify {

inline namespace v1 {

class BaseModel {
public:
    static auto create_comma_separated_List(const std::vector<std::string> &v) -> std::string;
};

}// namespace v1

}// namespace spotify

#endif

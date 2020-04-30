//
// Created by Michael Wittmann on 30/04/2020.
//

#ifndef SPOTIFYWEBAPIADAPTER_ACCESSTOKEN_H
#define SPOTIFYWEBAPIADAPTER_ACCESSTOKEN_H

#include "../AuthentificationToken.h"
#include <string>

namespace spotify {

    inline namespace v1 {

        namespace model {

            class accesstoken {
                using date_time_t = boost::posix_time::ptime;

            private:
                std::string _token_type;
                std::string _access_token;
                int _expires_in{0};
                std::string _refresh_token;

            public:
                accesstoken() = default;
                [[nodiscard]] std::string_view getTokenType() const;
                void setTokenType(std::string_view tokenType);
                [[nodiscard]] std::string_view getAccessToken() const;
                void setAccessToken(std::string_view accessToken);
                [[nodiscard]] int getExpiresIn() const;
                void setExpiresIn(int expiresIn);
                [[nodiscard]] std::string_view getRefreshToken() const;
                void setRefreshToken(std::string_view refreshToken);
                [[nodiscard]] auto to_poco() const -> AuthentificationToken;
            };

        }// namespace model

    }// namespace v1

}// namespace spotify

#endif

//
// Created by Michael Wittmann on 12/04/2020.
//

#ifndef SPOTIFYWEBAPI_SPOTIFYNETWORKMANAGER_H
#define SPOTIFYWEBAPI_SPOTIFYNETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
#include <QUrlQuery>
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include "../AuthenticationToken.hpp"

namespace spotify {

inline namespace v1 {

class AuthenticationToken;

class SpotifyNetworkManager : public QObject {
    Q_OBJECT
public:
    struct HeaderInfo {
        QByteArray _header1;
        QByteArray _header2;
    };

    SpotifyNetworkManager();
    SpotifyNetworkManager(SpotifyNetworkManager &manager) = delete;
    SpotifyNetworkManager(SpotifyNetworkManager &&manager) = delete;
    ~SpotifyNetworkManager() override = default;
    SpotifyNetworkManager &operator=(SpotifyNetworkManager const &manager) = delete;
    SpotifyNetworkManager &operator=(SpotifyNetworkManager const &&manager) = delete;
    auto perform_post_request(std::string_view url,
                              const std::map<std::string, std::string> &postData) -> void;
    [[nodiscard]] auto get_reply() const -> std::string;
    void perform_get_request(std::string_view view);
    void perform_get_request(std::string_view url, const spotify::AuthenticationToken &token, bool include_bearer = true);
    [[maybe_unused]] void perform_post_request(std::string_view url, const spotify::AuthenticationToken &token,
                                               const std::map<std::string, std::string> &postData, bool include_bearer = true);
    void perform_post_request(std::string_view url, const AuthenticationToken &token,
                              std::string_view json_string, bool include_bearer = true);
    void perform_put_request(std::string_view url, const AuthenticationToken &token, const std::map<std::string, std::string> &postData, bool include_bearer);
    void perform_put_request(std::string_view url, const AuthenticationToken &token, std::string_view json_string, bool include_bearer);
    void perform_delete_request(std::string_view url, const AuthenticationToken &token, bool include_bearer);

private:
    static constexpr int dim = 33;
    const std::string clientId = "636b0c0e79f34ce39855f58337583f84";
    const std::string clientSecret = "6c3d3d78017347bfaacf451a3789811e";
    static constexpr std::array<char, dim> clientSecretEncrypted{
            "{.~)~)zu}|z~yz/+,,.+yx|,~zutu||("};
    std::unique_ptr<QNetworkAccessManager> _manager{};
    std::string _reply{};
    static constexpr int max_file_size = 1048576 * 5;
    static constexpr int max_files = 1048576 * 5;
    std::shared_ptr<spdlog::logger> _asyncLogger;
    static auto createRequest(const QUrl &url, HeaderInfo const &info) -> QNetworkRequest;
    auto performGetRequest(QNetworkRequest const &request) -> void;
    auto performPostRequest(const QNetworkRequest &request, const QByteArray &data) -> void;
    auto performPutRequest(const QNetworkRequest &request, const QByteArray &data) -> void;
    auto performGetRequest(std::string_view surl, std::string_view h1, std::string_view h2) -> void;
    void performDeleteRequest(const QNetworkRequest &request);

signals:

private slots:
    auto replyFinished(QNetworkReply *reply) -> void;
    auto slotSslErrors(const QList<QSslError> &errors) -> void;
    auto slotReadyRead() -> void;
    auto slotError() -> void;
    static auto createRequest(std::string_view surl, std::string_view h1, std::string_view h2)
            -> QNetworkRequest;
};

}// namespace v1

}// namespace spotify

#endif

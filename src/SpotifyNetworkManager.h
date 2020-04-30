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
#include <spdlog/async.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace spotify {

    inline namespace v1 {

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
            auto performGetRequest(std::string_view url, std::string_view h1, std::string_view h2) -> void;
            auto performPostRequest(const QNetworkRequest &request, const QByteArray &data) -> void;
            auto performPutRequest(const QNetworkRequest &request, const QByteArray &data) -> void;
            [[nodiscard]] auto getReply() const -> std::string;

        private:
            std::unique_ptr<QNetworkAccessManager> _manager{};
            std::string _reply{};
            static constexpr int max_file_size = 1048576 * 5;
            static constexpr int max_files = 1048576 * 5;
            std::shared_ptr<spdlog::logger> _asyncLogger;
            static auto createRequest(const QUrl &url, HeaderInfo const &info) -> QNetworkRequest;
            auto performGetRequest(QNetworkRequest const &request) -> void;

        signals:

        private slots:
            auto replyFinished(QNetworkReply *reply) -> void;
            auto slotSslErrors(const QList<QSslError> &errors) -> void;
            auto slotReadyRead() -> void;
            auto slotError() -> void;
            static auto createRequest(std::string_view surl, std::string_view h1, std::string_view h2) -> QNetworkRequest;
        };

    }// namespace v1

}// namespace spotify

#endif

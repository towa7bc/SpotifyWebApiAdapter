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

    SpotifyNetworkManager() : _manager(std::make_unique<QNetworkAccessManager>(this)) {
        connect(_manager.get(), &QNetworkAccessManager::finished, this, &SpotifyNetworkManager::replyFinished);

        try {
            _asyncLogger = spdlog::rotating_logger_mt<spdlog::async_factory>("async_file_logger_qt",
                                                                             "logs/async_log_qt.txt",
                                                                             max_file_size, max_files);

            _asyncLogger->set_level(spdlog::level::debug);
            _asyncLogger->debug("Initialize called.");
        } catch (const spdlog::spdlog_ex &ex) {
            spdlog::logger("Log initialization failed: " + std::string(ex.what()));
        }
    }

    SpotifyNetworkManager(SpotifyNetworkManager &manager) = delete;
    SpotifyNetworkManager(SpotifyNetworkManager &&manager) = delete;
    ~SpotifyNetworkManager() override = default;
    SpotifyNetworkManager &operator=(SpotifyNetworkManager const &manager) = delete;
    SpotifyNetworkManager &operator=(SpotifyNetworkManager const &&manager) = delete;

    auto performGetRequest(std::string_view surl, std::string_view h1, std::string_view h2) -> void {
        auto request = createRequest(surl, h1, h2);
        performGetRequest(request);
    }

    auto performPostRequest(const QNetworkRequest &request, const QByteArray &data) -> void {
        auto *reply = _manager->post(request, data);
        connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
        connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
        connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
    }

    auto performPutRequest(const QNetworkRequest &request, const QByteArray &data) -> void {
        auto *reply = _manager->put(request, data);
        connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
        connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
        connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
    }

    [[nodiscard]] auto getReply() const -> std::string {
        return _reply;
    }

private:
    std::unique_ptr<QNetworkAccessManager> _manager{};
    std::string _reply{};
    static constexpr int max_file_size = 1048576 * 5;
    static constexpr int max_files = 1048576 * 5;
    std::shared_ptr<spdlog::logger> _asyncLogger;

    static auto createRequest(const QUrl &url, HeaderInfo const &info) -> QNetworkRequest {
        QNetworkRequest request;
        request.setUrl(url);
        request.setRawHeader(info._header1, info._header2);
        return request;
    }

    auto performGetRequest(QNetworkRequest const &request) -> void {
        auto *reply = _manager->get(request);
        connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
        connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
        connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
    }

signals:

private slots:
    auto replyFinished(QNetworkReply *reply) -> void {
        if (reply->error() == QNetworkReply::NoError) {
            _reply = reply->readAll().data();
        }
        reply->deleteLater();
    }

    auto slotSslErrors(const QList<QSslError> &errors) -> void {
        std::string error = errors[0].errorString().toStdString();
        _asyncLogger->debug(error);
    }

    auto slotReadyRead() -> void {
    }

    auto slotError() -> void {
    }

    static auto createRequest(std::string_view surl, std::string_view h1, std::string_view h2) -> QNetworkRequest {
        QUrl url = QUrl(surl.data());
        QByteArray header1 = h1.data();
        QByteArray header2 = h2.data();
        HeaderInfo info;
        info._header1 = header1;
        info._header2 = header2;

        return createRequest(url, info);
    }
};

}// namespace v1

}// namespace spotify

#endif

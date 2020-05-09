//
// Created by Michael Wittmann on 03/05/2020.
//

#include "SpotifyNetworkManager.hpp"

namespace spotify {

inline namespace v1 {

spotify::SpotifyNetworkManager::SpotifyNetworkManager() : _manager(std::make_unique<QNetworkAccessManager>(this)) {
    connect(_manager.get(), &QNetworkAccessManager::finished, this,
            &SpotifyNetworkManager::replyFinished);

    try {
        _asyncLogger = spdlog::rotating_logger_mt<spdlog::async_factory>(
                "async_file_logger_qt", "logs/async_log_qt.txt", max_file_size, max_files);

        _asyncLogger->set_level(spdlog::level::debug);
        _asyncLogger->debug("Initialize called.");
    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::logger("Log initialization failed: " + std::string(ex.what()));
    }
}

auto spotify::SpotifyNetworkManager::performGetRequest(std::string_view surl,
                                                       std::string_view h1,
                                                       std::string_view h2) -> void {
    auto request = createRequest(surl, h1, h2);
    performGetRequest(request);
}

auto spotify::SpotifyNetworkManager::perform_post_request(
        std::string_view url, const std::map<std::string, std::string> &postData) -> void {
    auto request = createRequest(url, "application/x-www-form-urlencoded", "");
    _asyncLogger->debug("perform_post_request called.");
    QByteArray data;
    QUrlQuery query;
    for (const auto &field : postData) {
        query.addQueryItem(field.first.data(), field.second.data());
    }
    data = query.toString(QUrl::FullyEncoded).toUtf8();
    performPostRequest(request, data);
}

auto spotify::SpotifyNetworkManager::performPostRequest(const QNetworkRequest &request,
                                                        const QByteArray &data) -> void {
    auto *reply = _manager->post(request, data);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this,
            &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

auto spotify::SpotifyNetworkManager::performPutRequest(const QNetworkRequest &request,
                                                       const QByteArray &data) -> void {
    auto *reply = _manager->put(request, data);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this,
            &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

auto spotify::SpotifyNetworkManager::get_reply() const -> std::string { return _reply; }

/* static */ auto spotify::SpotifyNetworkManager::createRequest(const QUrl &url,
                                                                HeaderInfo const &info)
        -> QNetworkRequest {
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader(info._header1, info._header2);
    return request;
}

auto spotify::SpotifyNetworkManager::performGetRequest(const QNetworkRequest &request) -> void {
    auto *reply = _manager->get(request);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this,
            &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

auto spotify::SpotifyNetworkManager::performDeleteRequest(const QNetworkRequest &request) -> void {
    auto *reply = _manager->deleteResource(request);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this,
            &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

auto spotify::SpotifyNetworkManager::slotReadyRead() -> void {}

auto spotify::SpotifyNetworkManager::slotError() -> void {}

auto spotify::SpotifyNetworkManager::replyFinished(QNetworkReply *reply) -> void {
    if (reply->error() == QNetworkReply::NoError) {
        _reply = reply->readAll().data();
    }
    reply->deleteLater();
}

auto spotify::SpotifyNetworkManager::slotSslErrors(const QList<QSslError> &errors) -> void {
    std::string error = errors[0].errorString().toStdString();
    _asyncLogger->debug(error);
}

/* static */ auto spotify::SpotifyNetworkManager::createRequest(std::string_view surl,
                                                                std::string_view h1,
                                                                std::string_view h2)
        -> QNetworkRequest {
    QUrl url = QUrl(surl.data());
    QByteArray header1 = h1.data();
    QByteArray header2 = h2.data();
    HeaderInfo info;
    info._header1 = header1;
    info._header2 = header2;

    return createRequest(url, info);
}

void spotify::SpotifyNetworkManager::perform_get_request(std::string_view url) {
    _asyncLogger->debug("perform_get_request called.");
    auto request = createRequest(url, "application/x-www-form-urlencoded", "");
    performGetRequest(request);
}

void spotify::SpotifyNetworkManager::perform_get_request(std::string_view url, spotify::AuthentificationToken &token, bool include_bearer) {
    _asyncLogger->debug("perform_get_request called.");
    QNetworkRequest request;
    if (include_bearer) {
        request = createRequest(url, "Authorization: Bearer " + token.getMAccessToken(), "");
    } else {
        request = createRequest(url, "application/x-www-form-urlencoded", "");
    }
    performGetRequest(request);
}

auto spotify::SpotifyNetworkManager::perform_post_request(
        std::string_view url, spotify::AuthentificationToken &token,
        const std::map<std::string, std::string> &postData, bool include_bearer) -> void {
    _asyncLogger->debug("perform_post_request called.");
    QNetworkRequest request;
    if (include_bearer) {
        request = createRequest(url, "Authorization: Bearer " + token.getMAccessToken(), "");
    } else {
        request = createRequest(url, "application/x-www-form-urlencoded", "");
    }
    QByteArray data;
    QUrlQuery query;
    for (const auto &field : postData) {
        query.addQueryItem(field.first.data(), field.second.data());
    }
    data = query.toString(QUrl::FullyEncoded).toUtf8();
    performPostRequest(request, data);
}

auto spotify::SpotifyNetworkManager::perform_post_request(
        std::string_view url, spotify::AuthentificationToken &token,
        std::string_view json_string, bool include_bearer) -> void {
    _asyncLogger->debug("perform_post_request called.");
    QNetworkRequest request;
    if (include_bearer) {
        request = createRequest(url, "Authorization: Bearer " + token.getMAccessToken(), "application/json");
    } else {
        request = createRequest(url, "application/json", "");
    }
    performPostRequest(request, json_string.data());
}

auto spotify::SpotifyNetworkManager::perform_put_request(
        std::string_view url, spotify::AuthentificationToken &token,
        const std::map<std::string, std::string> &postData, bool include_bearer) -> void {
    _asyncLogger->debug("perform_put_request called.");
    QNetworkRequest request;
    if (include_bearer) {
        request = createRequest(url, "Authorization: Bearer " + token.getMAccessToken(), "");
    } else {
        request = createRequest(url, "application/x-www-form-urlencoded", "");
    }
    QByteArray data;
    QUrlQuery query;
    for (const auto &field : postData) {
        query.addQueryItem(field.first.data(), field.second.data());
    }
    data = query.toString(QUrl::FullyEncoded).toUtf8();
    performPutRequest(request, data);
}

auto spotify::SpotifyNetworkManager::perform_put_request(
        std::string_view url, spotify::AuthentificationToken &token,
        std::string_view json_string, bool include_bearer) -> void {
    _asyncLogger->debug("perform_put_request called.");
    QNetworkRequest request;
    if (include_bearer) {
        request = createRequest(url, "Authorization: Bearer " + token.getMAccessToken(), "application/json");
    } else {
        request = createRequest(url, "application/json", "");
    }
    performPutRequest(request, json_string.data());
}

auto spotify::SpotifyNetworkManager::perform_delete_request(
        std::string_view url, spotify::AuthentificationToken &token, bool include_bearer) -> void {
    _asyncLogger->debug("perform_delete_request called.");
    QNetworkRequest request;
    if (include_bearer) {
        request = createRequest(url, "Authorization: Bearer " + token.getMAccessToken(), "");
    } else {
        request = createRequest(url, "application/x-www-form-urlencoded", "");
    }
    performDeleteRequest(request);
}

}// namespace v1
}// namespace spotify
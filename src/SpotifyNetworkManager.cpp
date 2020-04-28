//
// Created by Michael Wittmann on 12/04/2020.
//

#include "SpotifyNetworkManager.h"

SpotifyNetworkManager::SpotifyNetworkManager() {
    m_manager = std::make_unique<QNetworkAccessManager>(this);
    connect(m_manager.get(), &QNetworkAccessManager::finished, this, &SpotifyNetworkManager::replyFinished);

    try {
        m_asyncLogger = spdlog::rotating_logger_mt<spdlog::async_factory>("async_file_logger_qt",
                                                                          "logs/async_log_qt.txt",
                                                                          max_file_size, max_files);

        m_asyncLogger->set_level(spdlog::level::debug);
        m_asyncLogger->debug("Initialize called.");
    } catch (const spdlog::spdlog_ex &ex) {
        spdlog::logger("Log initialization failed: " + std::string(ex.what()));
    }
}

void SpotifyNetworkManager::replyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        m_reply = reply->readAll().data();
    }
    reply->deleteLater();
}

QNetworkRequest SpotifyNetworkManager::createRequest(const QUrl &url, HeaderInfo const &info) {
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader(info.header1, info.header2);
    return request;
}

QNetworkRequest SpotifyNetworkManager::createRequest(std::string_view surl, std::string_view h1, std::string_view h2) {
    QUrl url = QUrl(surl.data());
    QByteArray header1 = h1.data();
    QByteArray header2 = h2.data();
    HeaderInfo info;
    info.header1 = header1;
    info.header2 = header2;

    return createRequest(url, info);
}


void SpotifyNetworkManager::performGetRequest(std::string_view surl, std::string_view h1, std::string_view h2) {
    auto request = createRequest(surl, h1, h2);
    performGetRequest(request);
}

void SpotifyNetworkManager::performGetRequest(const QNetworkRequest &request) {
    auto *reply = m_manager->get(request);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

void SpotifyNetworkManager::performPostRequest(const QNetworkRequest &request, const QByteArray &data) {
    auto *reply = m_manager->post(request, data);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

void SpotifyNetworkManager::performPutRequest(const QNetworkRequest &request, const QByteArray &data) {
    auto *reply = m_manager->put(request, data);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

void SpotifyNetworkManager::slotReadyRead() {
}

void SpotifyNetworkManager::slotError() {
}

void SpotifyNetworkManager::slotSslErrors(const QList<QSslError> &errors) {
    std::string error = errors[0].errorString().toStdString();
    m_asyncLogger->debug(error);
}

std::string SpotifyNetworkManager::getReply() const {
    return m_reply;
}

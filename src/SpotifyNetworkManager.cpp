//
// Created by Michael Wittmann on 12/04/2020.
//

#include "SpotifyNetworkManager.h"

SpotifyNetworkManager::SpotifyNetworkManager() {
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished, this, &SpotifyNetworkManager::replyFinished);
}

void SpotifyNetworkManager::replyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        m_reply = reply->readAll().data();
    }
}

QNetworkRequest SpotifyNetworkManager::createRequest(QUrl url, HeaderInfo const &info) {
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader(info.header1, info.header2);
    return request;
}

SpotifyNetworkManager::~SpotifyNetworkManager() {
    delete m_manager;
}

void SpotifyNetworkManager::performGetRequest(std::string sUrl, std::string sHeader1, std::string sHeader2) {
    QUrl url = QUrl(sUrl.data());
    QByteArray header1 = sHeader1.data();
    QByteArray header2 = sHeader2.data();
    HeaderInfo info;
    info.header1 = header1;
    info.header2 = header2;

    auto request = createRequest(url, info);

    performGetRequest(request);
}

void SpotifyNetworkManager::performGetRequest(const QNetworkRequest &request) {
    auto reply = m_manager->get(request);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

void SpotifyNetworkManager::performPostRequest(const QNetworkRequest &request, QByteArray data) {
    auto reply = m_manager->post(request, data);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

void SpotifyNetworkManager::performPutRequest(const QNetworkRequest &request, QByteArray data) {
    auto reply = m_manager->put(request, data);
    connect(reply, &QIODevice::readyRead, this, &SpotifyNetworkManager::slotReadyRead);
    connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &SpotifyNetworkManager::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &SpotifyNetworkManager::slotSslErrors);
}

void SpotifyNetworkManager::slotReadyRead() {
}

void SpotifyNetworkManager::slotError() {
}

void SpotifyNetworkManager::slotSslErrors(const QList<QSslError> &errors) {
    std::string d = errors[0].errorString().toStdString();
}

std::string SpotifyNetworkManager::getReply() const {
    return m_reply;
}

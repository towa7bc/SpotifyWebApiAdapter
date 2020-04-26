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

class SpotifyNetworkManager : public QObject {

    Q_OBJECT
public:
    struct HeaderInfo {
        QByteArray header1;
        QByteArray header2;
    };

    SpotifyNetworkManager();
    SpotifyNetworkManager(SpotifyNetworkManager &manager) = delete;
    SpotifyNetworkManager(SpotifyNetworkManager &&manager) = delete;
    ~SpotifyNetworkManager() override = default;
    SpotifyNetworkManager &operator=(SpotifyNetworkManager const &manager) = delete;
    SpotifyNetworkManager &operator=(SpotifyNetworkManager const &&manager) = delete;
    void performGetRequest(std::string url, std::string h1, std::string h2);
    void performPostRequest(const QNetworkRequest &request, const QByteArray &data);
    void performPutRequest(const QNetworkRequest &request, const QByteArray &data);
    [[nodiscard]] std::string getReply() const;

private:
    std::unique_ptr<QNetworkAccessManager> m_manager{};
    std::string m_reply{};
    static QNetworkRequest createRequest(const QUrl &url, HeaderInfo const &info);
    void performGetRequest(QNetworkRequest const &request);
    std::shared_ptr<spdlog::logger> m_asyncLogger;

signals:

private slots:
    void replyFinished(QNetworkReply *reply);
    void slotSslErrors(const QList<QSslError> &errors);
    void slotReadyRead();
    void slotError();
    static QNetworkRequest createRequest(std::string surl, std::string h1, std::string h2);
};

#endif//SPOTIFYWEBAPI_SPOTIFYNETWORKMANAGER_H

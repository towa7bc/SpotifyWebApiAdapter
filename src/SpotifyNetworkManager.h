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

class SpotifyNetworkManager : public QObject {

    Q_OBJECT
public:
    struct HeaderInfo {
        QByteArray header1;
        QByteArray header2;
    };

    SpotifyNetworkManager();
    SpotifyNetworkManager(SpotifyNetworkManager &manager) = delete;
    ~SpotifyNetworkManager() override;
    SpotifyNetworkManager &operator=(SpotifyNetworkManager const &manager) = delete;
    void performGetRequest(std::string url, std::string h1, std::string h2);
    void performPostRequest(const QNetworkRequest &request, QByteArray data);
    void performPutRequest(const QNetworkRequest &request, QByteArray data);
    std::string getReply() const;

private:
    QNetworkAccessManager *m_manager{};
    std::string m_reply{};
    static QNetworkRequest createRequest(QUrl url, HeaderInfo const &info);
    void performGetRequest(QNetworkRequest const &request);

signals:

private slots:
    void replyFinished(QNetworkReply *reply);
    void slotSslErrors(const QList<QSslError> &errors);
    void slotReadyRead();
    void slotError();
};

#endif//SPOTIFYWEBAPI_SPOTIFYNETWORKMANAGER_H

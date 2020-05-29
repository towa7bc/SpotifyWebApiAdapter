//
// Created by Michael Wittmann on 03/05/2020.
//

#include "SpotifyNetworkManager.hpp"

#include <qglobal.h>
#include <qiodevice.h>
#include <qnetworkreply.h>
#include <qsslerror.h>
#include <qurl.h>
#include <qurlquery.h>
#include <spdlog/logger.h>

#include <string>
#include <utility>

#include "../AuthenticationToken.hpp"
#include "Log.hpp"

namespace spotify {
inline namespace v1 {

SpotifyNetworkManager::SpotifyNetworkManager()
    : _manager(std::make_unique<QNetworkAccessManager>(this)) {
  connect(_manager.get(), &QNetworkAccessManager::finished, this,
          &SpotifyNetworkManager::replyFinished);
  Log::logger()->trace("SpotifyNetworkManager Constructor called.");
}

auto SpotifyNetworkManager::performGetRequest(std::string_view surl,
                                              std::string_view h1,
                                              std::string_view h2) -> void {
  auto request = createRequest(surl, h1, h2);
  performGetRequest(request);
}

auto SpotifyNetworkManager::perform_post_request(
    std::string_view url, const std::map<std::string, std::string> &postData)
    -> void {
  auto request = createRequest(url, "application/x-www-form-urlencoded", "");
  Log::logger()->trace("perform_post_request called.");
  QByteArray data;
  QUrlQuery query;
  for (const auto &field : postData) {
    query.addQueryItem(field.first.data(), field.second.data());
  }
  data = query.toString(QUrl::FullyEncoded).toUtf8();
  performPostRequest(request, data);
}

auto SpotifyNetworkManager::performPostRequest(const QNetworkRequest &request,
                                               const QByteArray &data) -> void {
  auto *reply = _manager->post(request, data);
  connect(reply, &QIODevice::readyRead, this,
          &SpotifyNetworkManager::slotReadyRead);
  connect(reply, &QNetworkReply::sslErrors, this,
          &SpotifyNetworkManager::slotSslErrors);
}

auto SpotifyNetworkManager::performPutRequest(const QNetworkRequest &request,
                                              const QByteArray &data) -> void {
  auto *reply = _manager->put(request, data);
  connect(reply, &QIODevice::readyRead, this,
          &SpotifyNetworkManager::slotReadyRead);
  connect(reply, &QNetworkReply::sslErrors, this,
          &SpotifyNetworkManager::slotSslErrors);
}

auto SpotifyNetworkManager::get_reply() const -> std::string { return _reply; }

/* static */ auto SpotifyNetworkManager::createRequest(const QUrl &url,
                                                       HeaderInfo const &info)
    -> QNetworkRequest {
  QNetworkRequest request;
  request.setUrl(url);
  request.setRawHeader(info._header1, info._header2);
  return request;
}

auto SpotifyNetworkManager::performGetRequest(const QNetworkRequest &request)
    -> void {
  auto *reply = _manager->get(request);
  connect(reply, &QIODevice::readyRead, this,
          &SpotifyNetworkManager::slotReadyRead);
  connect(reply, &QNetworkReply::sslErrors, this,
          &SpotifyNetworkManager::slotSslErrors);
}

auto SpotifyNetworkManager::performDeleteRequest(const QNetworkRequest &request)
    -> void {
  auto *reply = _manager->deleteResource(request);
  connect(reply, &QIODevice::readyRead, this,
          &SpotifyNetworkManager::slotReadyRead);
  connect(reply, &QNetworkReply::sslErrors, this,
          &SpotifyNetworkManager::slotSslErrors);
}

auto SpotifyNetworkManager::slotReadyRead() -> void {}

auto SpotifyNetworkManager::replyFinished(QNetworkReply *reply) -> void {
  if (reply->error() == QNetworkReply::NoError) {
    _reply = reply->readAll().data();
  }
  reply->deleteLater();
}

auto SpotifyNetworkManager::slotSslErrors(const QList<QSslError> &errors)
    -> void {
  std::string error = errors[0].errorString().toStdString();
  Log::logger()->trace(error);
}

/* static */ auto SpotifyNetworkManager::createRequest(std::string_view surl,
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

void SpotifyNetworkManager::perform_get_request(std::string_view url) {
  Log::logger()->trace("perform_get_request called.");
  auto request = createRequest(url, "application/x-www-form-urlencoded", "");
  performGetRequest(request);
}

void SpotifyNetworkManager::perform_get_request(
    std::string_view url, const AuthenticationToken &token,
    bool include_bearer) {
  Log::logger()->trace("perform_get_request called.");
  QNetworkRequest request;
  if (include_bearer) {
    request = createRequest(
        url, "Authorization: Bearer " + token.getAccessToken(), "");
  } else {
    request = createRequest(url, "application/x-www-form-urlencoded", "");
  }
  performGetRequest(request);
}

auto SpotifyNetworkManager::perform_post_request(
    std::string_view url, const AuthenticationToken &token,
    const std::map<std::string, std::string> &postData, bool include_bearer)
    -> void {
  Log::logger()->trace("perform_post_request called.");
  QNetworkRequest request;
  if (include_bearer) {
    request = createRequest(
        url, "Authorization: Bearer " + token.getAccessToken(), "");
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

auto SpotifyNetworkManager::perform_post_request(
    std::string_view url, const AuthenticationToken &token,
    std::string_view json_string, bool include_bearer) -> void {
  Log::logger()->trace("perform_post_request called.");
  QNetworkRequest request;
  if (include_bearer) {
    request =
        createRequest(url, "Authorization: Bearer " + token.getAccessToken(),
                      "application/json");
  } else {
    request = createRequest(url, "application/json", "");
  }
  performPostRequest(request, json_string.data());
}

auto SpotifyNetworkManager::perform_put_request(
    std::string_view url, const AuthenticationToken &token,
    const std::map<std::string, std::string> &postData, bool include_bearer)
    -> void {
  Log::logger()->trace("perform_put_request called.");
  QNetworkRequest request;
  if (include_bearer) {
    request = createRequest(
        url, "Authorization: Bearer " + token.getAccessToken(), "");
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

auto SpotifyNetworkManager::perform_put_request(
    std::string_view url, const AuthenticationToken &token,
    std::string_view json_string, bool include_bearer) -> void {
  Log::logger()->trace("perform_put_request called.");
  QNetworkRequest request;
  if (include_bearer) {
    request =
        createRequest(url, "Authorization: Bearer " + token.getAccessToken(),
                      "application/json");
  } else {
    request = createRequest(url, "application/json", "");
  }
  performPutRequest(request, json_string.data());
}

auto SpotifyNetworkManager::perform_delete_request(
    std::string_view url, const AuthenticationToken &token, bool include_bearer)
    -> void {
  Log::logger()->trace("perform_delete_request called.");
  QNetworkRequest request;
  if (include_bearer) {
    request = createRequest(
        url, "Authorization: Bearer " + token.getAccessToken(), "");
  } else {
    request = createRequest(url, "application/x-www-form-urlencoded", "");
  }
  performDeleteRequest(request);
}

}  // namespace spotify::inline v1
}  // namespace spotify
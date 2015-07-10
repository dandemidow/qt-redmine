// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef NETWORK_H_
#define NETWORK_H_

#include "authenticator.h"

#include <QSharedPointer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Network
{
  QNetworkAccessManager nam;
  Authenticator auth;

public:
  enum RequestType {
    GET,
    POST,
    PUT,
    DELETE
  };

  Network(const QByteArray &key);
  Network(const QString &login, const QString &password);
  ~Network();

  QNetworkReply *send(QNetworkRequest &request,
                      RequestType t,
                      const QByteArray &data = QByteArray());
};

#endif // NETWORK_H_

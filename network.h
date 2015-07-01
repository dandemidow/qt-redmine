// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

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
  Network(const QByteArray &key);
  Network(const QString &login, const QString &password);
  ~Network();

  QNetworkReply* sendGet(QNetworkRequest &request);
};

#endif // NETWORK_H_

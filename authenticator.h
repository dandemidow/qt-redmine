// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef AUTHENTICATOR_H_
#define AUTHENTICATOR_H_

#include "redmine_global.h"

#include <QString>
#include <QPair>
#include <QtNetwork/QNetworkRequest>

class REDMINEQTSHARED_EXPORT Authenticator {
  QPair<QByteArray, QByteArray> _header;
public:

  Authenticator(const QString &login, const QString &password);

  Authenticator(const QByteArray &apiKey);

  virtual ~Authenticator() {}

  virtual void addAuthentication(QNetworkRequest& request);
};

#endif  // AUTHENTICATOR_H_

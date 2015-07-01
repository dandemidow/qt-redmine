// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project


#include "authenticator.h"


Authenticator::Authenticator(const QString &login, const QString &password) {
  QString auth = QString("%1:%2").arg(login).arg(password);
  QByteArray headData = "Basic " + auth.toLocal8Bit().toBase64();
  _header = qMakePair(QByteArray("Authorization"),  headData);
}

Authenticator::Authenticator(const QByteArray &apiKey) : _header("X-Redmine-API-Key", apiKey) {
}

void Authenticator::addAuthentication(QNetworkRequest &request) {
  request.setRawHeader(_header.first, _header.second);
}

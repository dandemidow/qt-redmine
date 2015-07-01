// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#include "network.h"

Network::Network(const QString &login, const QString &password):
  auth(login, password) {
}

Network::Network(const QByteArray &key):
  auth(key) {
}

Network::~Network()
{

}

QNetworkReply* Network::sendGet(QNetworkRequest &request)
{
  auth.addAuthentication(request);
  QNetworkReply* _reply = nam.get(request);
  return _reply;
}


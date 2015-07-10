// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

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

QNetworkReply* Network::send(QNetworkRequest &request,
                             RequestType t,
                             const QByteArray &data)
{
  auth.addAuthentication(request);
  QNetworkReply* _reply = 0;
  switch(t) {
    case GET:
      request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
      _reply = nam.get(request);
      break;
    case POST:
      request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml");
      _reply = nam.post(request, data);
      qDebug()<<"post: "<<data;
      break;
    case PUT:
      request.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml");
      _reply = nam.put(request, data);
      qDebug()<<"put: "<<data;
      break;
    case DELETE:
      request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");
      _reply = nam.deleteResource(request);
      break;
  }
  return _reply;
}


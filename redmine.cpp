// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#include "redmine.h"

#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

RedmineClient::RedmineClient(const QUrl &url, QString apiKey, QObject* parent) :
  QObject(parent),
  net(apiKey.toLocal8Bit()),
  _url(url) {
}

RedmineClient::RedmineClient(const QUrl &url, const QString &login, const QString &password, QObject* parent) :
  QObject(parent),
  net(login, password),
  _url(url) {
}

RedmineClient::RedmineClient(const QUrl &url, const char *login, const char *password, QObject *parent) :
  QObject(parent),
  net(QString::fromLatin1(login), QString::fromLatin1(password)),
  _url(url)
{
}

RedmineClient::~RedmineClient() {
  qDeleteAll(_reg);
}

Sender RedmineClient::getSender()
{
  Sender snd(_url, net);
  return snd;
}

void RedmineClient::onFinish() {
  delete sender();
}

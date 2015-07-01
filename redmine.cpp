#include "redmine.h"

#include <QDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

RedmineClient::RedmineClient(const QUrl &url, QString apiKey, QObject* parent) :
  QObject(parent),
  net(apiKey.toLocal8Bit()),
  _url(url),
  _ua("redmine-qt") {
}

RedmineClient::RedmineClient(const QUrl &url, const QString &login, const QString &password, QObject* parent) :
  QObject(parent),
  net(login, password),
  _url(url),
  _ua("redmine-qt") {
}

RedmineClient::~RedmineClient() {
}
void RedmineClient::getUsers()
{
  _send = new UsersSender(_url, net);
  connect(_send, SIGNAL(readyUsers(QList<User>)), this, SLOT(onReadyUsers(QList<User>)));
  _send->start();
}

void RedmineClient::onReadyUsers(QList<User> list)
{
//  delete _send;
  emit readyUsers(list);
}

void RedmineClient::setUserAgent(QByteArray ua) {
  _ua = ua;
}

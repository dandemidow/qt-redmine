// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#include "sender.h"

#include <QDebug>
#include <QtXml>
#include <QDomDocument>

Sender::Sender(const QUrl &url, Network &net) :
  _net(net),
  _ua("redmine-client"),
  _url(url) {
}


Sender::~Sender() { }

void Sender::sendRequest(QUrl url, const QByteArray &requestData) {

  QByteArray dataSizeAsByteArray = QByteArray::number(requestData.size());

  qDebug()<<url;
  QNetworkRequest request(url);
  request.setRawHeader("User-Agent", _ua);
  request.setRawHeader("X-Custom-User-Agent", _ua);
  request.setRawHeader("Content-Type", "text/xml");
  request.setRawHeader("Content-Length", dataSizeAsByteArray);

  QNetworkReply* _reply = _net.sendGet(request);
  connect(_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

//  connect(_reply, SIGNAL(finished()), this, SIGNAL
}

void Sender::onReadyRead()
{
  QNetworkReply *_reply = (QNetworkReply*)sender();
  if ( _reply ) {
    if ( _reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200 ) {
      process(_reply->readAll());
    } else qDebug()<<"reply "<<_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  }
}

QList<User> UsersSender::ans2User(QByteArray arr)
{
  QDomDocument doc;
  doc.setContent(arr);
  QDomNodeList users = doc.elementsByTagName("user");
  QList<User> list;

  for (int i = 0; i<users.size(); ++i) {
    User u;
    QDomNode node = users.item(i);
    QDomElement id = node.firstChildElement("id");
    u.id = id.text().toUInt();
    QDomElement login = node.firstChildElement("login");
    u.login = login.text();
    QDomElement firstname = node.firstChildElement("firstname");
    u.firstname = firstname.text();
    QDomElement lastname = node.firstChildElement("lastname");
    u.lastname = lastname.text();
    QDomElement mail = node.firstChildElement("mail");
    u.mail = mail.text();
    list.append(u);
  }
  return list;
}

void UsersSender::process(const QByteArray &ans)
{
  qDebug()<<"ans "<<ans.size();
  QList<User> list = ans2User(ans);
  emit readyUsers(list);
}

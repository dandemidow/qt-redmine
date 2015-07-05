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

Sender::Sender(const QUrl &url, Network &net) :
  _net(net),
  _ua("redmine-client"),
  _url(url) {
}

Sender::Sender(const Sender &s):
  QObject(s.parent()),
  _net(s._net),
  _ua("redmine-client"),
  _url(s._url) {}

Sender::~Sender() { qDebug()<<"sender dtor()"; }

void Sender::sendRequest(const QByteArray &requestData) {

  QByteArray dataSizeAsByteArray = QByteArray::number(requestData.size());

  qDebug()<<_url;
  QNetworkRequest request(_url);
  request.setRawHeader("User-Agent", _ua);
  request.setRawHeader("X-Custom-User-Agent", _ua);
  request.setRawHeader("Content-Type", "text/xml");
  request.setRawHeader("Content-Length", dataSizeAsByteArray);

  QNetworkReply* _reply = _net.sendGet(request);
  connect(_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

  connect(_reply, SIGNAL(finished()), this, SLOT(onFinished()));
}

void Sender::onReadyRead()
{
  QNetworkReply *_reply = (QNetworkReply*)sender();
  if ( _reply ) {
    if ( _reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 200 ) {
      _buffer.append(_reply->readAll());
    } else qDebug()<<"reply "<<_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  }
}

void Sender::onFinished()
{
  QDomDocument doc;
  qDebug()<<"ans "<<_buffer;//.size();
  bool ok = doc.setContent(_buffer);
  Q_ASSERT(ok);
  result(doc);
}

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

void Sender::sendRequest(Network::RequestType t,
                         const QUrl &url,
                         const QByteArray &requestData) {

  _buffer.clear();
  QByteArray dataSizeAsByteArray = QByteArray::number(requestData.size());

  qDebug()<<url;
  QNetworkRequest request(url);
//  request.setRawHeader("User-Agent", _ua);
//  request.setRawHeader("X-Custom-User-Agent", _ua);
  request.setRawHeader("Content-Length", dataSizeAsByteArray);

  QNetworkReply* _reply = _net.send(request, t, requestData);
  if ( _reply ) {
    _buffer[_reply].clear();
    connect(_reply, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(_reply, SIGNAL(finished()), this, SLOT(onFinished()));
  }
}

void Sender::onReadyRead()
{
  QNetworkReply *_reply = (QNetworkReply*)sender();
  if ( _reply ) {
    u_int32_t code = _reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
    if ( code >= 200 && code < 300 ) {
      _buffer[_reply].append(_reply->readAll());
    } else {
      qDebug()<<"reply "<<_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
      qDebug()<<_reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
      qDebug()<<_reply->readAll();
    }
  }
}

void Sender::onFinished()
{
  QNetworkReply *_reply = (QNetworkReply*)sender();
  QDomDocument doc;
  qDebug()<<"ans "<<_buffer[_reply];//.size();
  bool ok = doc.setContent(_buffer[_reply]);
  if ( !ok ) qWarning()<<"set content error";
  result(doc);
}

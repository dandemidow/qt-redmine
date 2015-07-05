// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QtXml/QDomDocument>

#include "network.h"

class Sender: public QObject {
  Q_OBJECT
  Network &_net;
  QByteArray _ua;
protected:
  QUrl _url;
  QByteArray _buffer;

  void sendRequest(const QByteArray& requestData);
public:
  explicit Sender(const QUrl &url, Network &net);
  Sender(const Sender &s);
  virtual ~Sender();

public slots:
  void onReadyRead();
  void onFinished();
public:
  template <class Cmd>
  void start(const Cmd &cmd) {
    cmd.setPath(_url);
    sendRequest(QByteArray());
  }

signals:
  void result(QDomDocument);
};

#endif // SENDER_H

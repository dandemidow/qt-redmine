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
#include "user.h"
#include "network.h"

class Sender: public QObject {
  Q_OBJECT
public:

  Network &_net;

  QByteArray _ua;
  QUrl _url;

  Sender(const QUrl &url, Network &net);
  virtual ~Sender();

  void sendRequest(QUrl url, const QByteArray& requestData);

  virtual void process(const QByteArray &ans) = 0;

public slots:
  void onReadyRead();
public:
  void start() {
    sendRequest(_url, QByteArray());
  }
};

class UsersSender: public Sender {
  Q_OBJECT
  QList<User> ans2User(QByteArray ans);
public:
  UsersSender(const QUrl &url, Network &net) : Sender(QUrl(url.toString()+"/users.xml"), net){}
  void process(const QByteArray &ans);
signals:
  void readyUsers(QList<User>);
};

#endif // SENDER_H

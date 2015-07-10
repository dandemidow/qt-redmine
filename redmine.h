// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef REDMINE_H_
#define REDMINE_H_

class Authenticator;
class QNetworkAccessManager;

#include "redmine_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QFuture>
#include <QThread>

#include "sender.h"

class C {
public:
  QObject *_obj;
  const char *_meth;
  virtual ~C(){}
};

template <class T>
class TC : public C {
public:
  TC(QObject* obj, const char *meth){ _obj = obj; _meth = meth; }
  static bool check(C *c) {
    TC<T>* t = dynamic_cast<TC<T>* >(c);
    return t!=0;
  }
};

class REDMINEQTSHARED_EXPORT RedmineClient : public QObject {

	Q_OBJECT

  Network net;
  QUrl _url;
  QList<C*> _reg;

  template <class T>
  C *findReg() {
    for( QList<C*>::iterator i=_reg.begin(); i<_reg.end(); ++i ) {
      if ( TC<T>::check(*i) ) return *i;
    }
    return 0;
  }

public:

  RedmineClient(const QUrl &url, QString apiKey, QObject* parent = NULL);
  RedmineClient(const QUrl &url, const QString &login, const QString &password, QObject* parent = NULL);
  RedmineClient(const QUrl &url, const char *login, const char *password, QObject* parent = NULL);
	virtual ~RedmineClient();

  template <class T>
  void reg(QObject *obj, const char *meth) {
    C *info = findReg<T>();
    if ( info ){
      info->_obj = obj;
      info->_meth = meth;
    } else {
      _reg.append(new TC<T>(obj, meth));
    }
  }

  template <class T>
  bool run(const T &cmd) {
    C *info = findReg<T>();
    if (!info) return false;
    return run(cmd, info->_obj, info->_meth);
  }

  template <class T>
  bool run(const T &cmd, QObject *obj, const char *meth) {
    Sender *send = new Sender(_url, net);
    QObject::connect(send, SIGNAL(result(QDomDocument)), obj, meth);
    QObject::connect(send, SIGNAL(finish()), this, SLOT(onFinish()));
    send->start(cmd);
    return true;
  }

  Sender getSender();

private slots:
  void onFinish();
};

#endif  // REDMINE_H_

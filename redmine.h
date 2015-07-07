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

class REDMINEQTSHARED_EXPORT RedmineClient : public QObject {

	Q_OBJECT

  Network net;
  QUrl _url;

public:

  RedmineClient(const QUrl &url, QString apiKey, QObject* parent = NULL);
  RedmineClient(const QUrl &url, const QString &login, const QString &password, QObject* parent = NULL);
	virtual ~RedmineClient();

  Sender get()
  {
    Sender snd(_url, net);
    return snd;
  }
};

#endif  // REDMINE_H_

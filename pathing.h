// Copyright 2015, Promtehaero.
// All rights reserved.
//
// Software license
//
// Author: dandemidow@gmail.com (Danila Demidow)
//
// Promtehaero VoIP Project

#ifndef PATHING
#define PATHING

#include <QString>
#include <QUrl>

class Format {
  QString _format;
public:
  explicit Format() : _format("xml") {}
  void setFormat(const QString &format){
    _format = format;
  }
  void addFormat(QString &path) const {
    path.append(".");
    path.append(_format);
  }
};

class Path :
    public Format {
  QString _path;
protected:
  static QString addId(const QString path, unsigned int id) {
    return path+"/"+QString::number(id);
  }

public:
  explicit Path(const QString &path) : _path(path) {}
  explicit Path(const QString &path, unsigned int id) : _path(addId(path, id)) {}
  QString path() const {
    QString p("/");
    p.append(_path);
    this->addFormat(p);
    return p;
  }
  virtual void setPath(QUrl &url) const {
    url.setPath(path());
  }
};

#endif // PATHING


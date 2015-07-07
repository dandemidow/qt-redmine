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

template <class T>
class PathSetter {
public:
  virtual void setPath(QUrl &url) const {
    T *t = static_cast<T*>(const_cast<PathSetter<T> *>(this));
    url.setPath(t->path());
  }
};

template <class Self>
class Concretible :
    public Format,
    public PathSetter<Concretible<Self> > {
  unsigned int _id;
  bool _concreted;
  QString _path;
public:
  explicit Concretible(const QString &path):
    _concreted(false),
    _path(path) {}
  Self &concret(unsigned int id) {
    _id = id;
    _concreted = true;
    return *(static_cast<Self*>(this));
  }
  Self &all() {
    _concreted = false;
    return *this;
  }
  QString path() const {
    QString p("/");
    p.append(_path);
    if ( _concreted ) {
      p.append("/");
      p.append(QString::number(_id));
    }
    this->addFormat(p);
    return p;
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
    url.setPath(_path);
  }
};

#endif // PATHING


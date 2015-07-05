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

template <class Self>
class Path : public Format {
  unsigned int _id;
  bool _concreted;
  QString _path;
public:
  explicit Path(const QString &path):
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

#endif // PATHING


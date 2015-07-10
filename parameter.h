// qt-redmine client
// Copyright (C) 2015, Danila Demidow
// Author: dandemidow@gmail.com (Danila Demidow)

#ifndef PARAMETER
#define PARAMETER

#include <QUrl>
#include <QString>
#include <QSharedPointer>
#include <QDebug>

class Filter {
  QSharedPointer<Filter> _next;
protected:
  QString _key;
  QString _value;

  template <typename T>
  void add(const T& t){
    QSharedPointer<Filter> *next_ptr = &_next;
    while(*next_ptr) next_ptr = &(next_ptr->data()->_next);
    next_ptr->reset(new T(t));
  }

public:
  explicit Filter(const char *key) : _key(QString::fromLatin1(key)) {}
  explicit Filter(const char *key, const QString &value) :
    _key(QString::fromLatin1(key)),
    _value(value) {}
  explicit Filter(const char *key, const char *value) :
    _key(QString::fromLatin1(key)),
    _value(QString::fromLatin1(value)) {}
  QString getFilter() const {
    QString arg ( _key + QString::fromLatin1("=") + _value );
    if ( _next ) arg.append(QString::fromLatin1("&")+_next->getFilter());
    return arg;
  }

  template <typename T1>
  friend T1 operator + (const T1 &l, const Filter &r) {
    T1 t(l);
    t.add(r);
    return t;
  }
};

class Include {
  QString _value;
  QSharedPointer<Include> _next;
protected:
  QString collect() const {
    QString add;
    if ( _next ) add = QString::fromLatin1(",")+_next->collect();
    return _value+add;
  }
  template <typename T>
  void add(const T& t){
    QSharedPointer<Include> *next_ptr = &_next;
    while(*next_ptr) next_ptr = &(next_ptr->data()->_next);
    next_ptr->reset(new T(t));
  }
public:
  explicit Include(const QString &value) : _value(value) {}
  explicit Include(const Include &i) : _value(i._value) ,_next(i._next) {}
  virtual ~Include(){}

  QString getInclude() const {
    QString add = QString::fromLatin1("include=");
    add.append(collect());
    return add;
  }

  template <typename T1>
  friend T1 operator + (const T1 &l, const Include &r) {
    T1 t(l);
    t.add(r);
    return t;
  }
};

#endif // PARAMETER

